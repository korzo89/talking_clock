#include <SoftwareSerial.h>
#include <DFMiniMp3.h>
#include <LiquidCrystal.h>
#include <RTClib.h>
#include <Wire.h>
#include <AceButton.h>
#include "pt.h"
#include "large_font.h"

#define LCD_RS      12
#define LCD_EN      11
#define LCD_D4      5
#define LCD_D5      4
#define LCD_D6      3
#define LCD_D7      2

#define DFP_RX      9
#define DFP_TX      8

#define BUTTON_PIN  A0

using namespace ace_button;

class Mp3Notify;
static SoftwareSerial secondarySerial(DFP_RX, DFP_TX);
static DFMiniMp3<SoftwareSerial, Mp3Notify> mp3(secondarySerial);
static bool clip_finished = false;

static LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

static DS1307 rtc;

static AceButton button(BUTTON_PIN);

static bool speak_requested = false;

static struct pt time_updater_pt;
static struct pt time_speaker_pt;

static char buffer[32];

class Mp3Notify
{
public:
  static void OnError(uint16_t errorCode)
  {
  }

  static void OnPlayFinished(uint16_t globalTrack)
  { 
    clip_finished = true;
  }

  static void OnCardOnline(uint16_t code)
  {  
  }

  static void OnCardInserted(uint16_t code)
  {
  }

  static void OnCardRemoved(uint16_t code)
  {
  }
};

void init_custom_char(int id, const byte *def)
{
  for (int i = 0; i < 8; i++)
    buffer[i] = pgm_read_byte_near(def + i);
    
  lcd.createChar(id, buffer);
}

void init_large_font()
{
  init_custom_char(1, bar1);
  init_custom_char(2, bar2);
  init_custom_char(3, bar3);
  init_custom_char(4, bar4);
  init_custom_char(5, bar5);
  init_custom_char(6, bar6);
  init_custom_char(7, bar7);
  init_custom_char(8, bar8);
}

void print_large_char(const byte *def, int offset)
{
  byte id = pgm_read_byte_near(def + offset);
  lcd.write(id);
}

void print_large_number(int num, int col)
{
  const byte *def = large_font[num];

  lcd.setCursor(col, 0); 
  print_large_char(def, 0);
  print_large_char(def, 1);
  print_large_char(def, 2);
  lcd.setCursor(col, 1); 
  print_large_char(def, 3);
  print_large_char(def, 4);
  print_large_char(def, 5);
}

void update_time(void)
{
  DateTime now = rtc.now();

  int hh = now.hour();
  int mm = now.minute();
  int ss = now.second();
  print_large_number(hh / 10, 0);
  print_large_number(hh % 10, 3);
  print_large_number(mm / 10, 7);
  print_large_number(mm % 10, 10);

  char dot = (ss % 2 == 0) ? ' ' : '\xA5';
  lcd.setCursor(6, 0);
  lcd.print(dot);
  lcd.setCursor(6, 1);
  lcd.print(dot);

  lcd.setCursor(14, 0);
  if (ss < 10)
    lcd.print('0');
  lcd.print(ss);

  static int prev_mm = -1;
  if ((prev_mm != -1) && (prev_mm == 59) && (mm == 0))
    speak_requested = true;
  prev_mm = mm;
}

PT_THREAD(time_updater(struct pt *pt))
{
  static unsigned long last_update = 0;
  
  PT_BEGIN(pt);

  while (1)
  {
    update_time();

    last_update = millis();
    PT_YIELD_UNTIL(pt, millis() - last_update > 500);
  }

  PT_END(pt);
}

int get_hour_clip(int hh)
{
  if (hh == 0)
    return 12;
  else
    return hh;
}

int get_minutes_tens_clip(int mm)
{
  if ((mm >= 10) && (mm < 20))
    return 35 + (mm - 10);
    
  mm /= 10;
  if (mm == 0)
    return 25;
  else
    return 45 + (mm - 2);
}

int get_minutes_ones_clip(int mm)
{
  if (mm == 0)
    return 25;

  if ((mm >= 10) && (mm < 20))
    return -1;
  
  mm %= 10;
  if (mm == 0)
    return -1;
  else
    return 25 + mm;
}

#define PT_DELAY(_pt, _ms)  \
    wait_start = millis();  \
    PT_YIELD_UNTIL(_pt, millis() - wait_start > (_ms));  \

#define PLAY_CLIP(_pt, _clip) \
    clip_finished = false;  \
    mp3.playMp3FolderTrack(_clip); \
    PT_YIELD_UNTIL(_pt, clip_finished);

PT_THREAD(time_speaker(struct pt *pt))
{
  static unsigned long wait_start = 0;
  static DateTime date;
  int clip;
  
  PT_BEGIN(pt);

  while (1)
  {
    PT_YIELD_UNTIL(pt, speak_requested);

    date = rtc.now();

    PLAY_CLIP(pt, 49);
    PT_DELAY(pt, 100);

    clip = get_hour_clip(date.hour());
    PLAY_CLIP(pt, clip);
    PT_DELAY(pt, 100);

    clip = get_minutes_tens_clip(date.minute());
    PLAY_CLIP(pt, clip);
    PT_DELAY(pt, 100);

    clip = get_minutes_ones_clip(date.minute());
    if (clip != -1)
    {
      PLAY_CLIP(pt, clip);
      PT_DELAY(pt, 100);
    }

    speak_requested = false;
  }

  PT_END(pt);
}

void button_event(AceButton* button, uint8_t eventType, uint8_t buttonState) 
{
  static unsigned long repeat_counter = 0;
  
  switch (eventType)
  {
  case AceButton::kEventPressed:
    speak_requested = true;
    break;

  case AceButton::kEventReleased:
    repeat_counter = 0;
    break;

  case AceButton::kEventRepeatPressed:
    repeat_counter++;
    if (repeat_counter == 20)
      mp3.playMp3FolderTrack(50);
    break;

  default:
    break;
  }
}

void setup() 
{
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  ButtonConfig* cfg = button.getButtonConfig();
  cfg->setEventHandler(button_event);
  cfg->setFeature(ButtonConfig::kFeatureRepeatPress);

  Wire.begin();
  rtc.begin();

  if (!rtc.isrunning())
    rtc.adjust(DateTime(__DATE__, __TIME__));

  init_large_font();

  lcd.begin(16, 2);
  
  mp3.begin();
  mp3.setVolume(100);
  
  PT_INIT(&time_updater_pt);
  PT_INIT(&time_speaker_pt);
}

void loop() 
{
  button.check();
  mp3.loop();
  
  time_updater(&time_updater_pt);
  time_speaker(&time_speaker_pt);

  if (Serial.available() > 0)
  {
    int len = Serial.readBytesUntil('\n', buffer, sizeof(buffer));
    buffer[len] = '\0';

    int hh, mm, ss;
    int res = sscanf(buffer, "%d:%d:%d", &hh, &mm, &ss);
    if (res == 3)
    {
      DateTime date;
      date.sethour(hh);
      date.setminute(mm);
      date.setsecond(ss);
      rtc.adjust(date);
    }
  }
}
