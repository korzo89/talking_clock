#include <SoftwareSerial.h>
#include <DFMiniMp3.h>
#include <LiquidCrystal.h>
#include <RTClib.h>
#include <Wire.h>
#include <AceButton.h>
#include "pt.h"

using namespace ace_button;

static bool clip_finished = false;

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

// the 8 arrays that form each segment of the custom numbers
byte bar1[8] = 
{
        B11100,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11100
};
byte bar2[8] =
{
        B00111,
        B01111,
        B01111,
        B01111,
        B01111,
        B01111,
        B01111,
        B00111
};
byte bar3[8] =
{
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111
};
byte bar4[8] =
{
        B11110,
        B11100,
        B00000,
        B00000,
        B00000,
        B00000,
        B11000,
        B11100
};
byte bar5[8] =
{
        B01111,
        B00111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00011,
        B00111
};
byte bar6[8] =
{
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111
};
byte bar7[8] =
{
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00111,
        B01111
};
byte bar8[8] =
{
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000
};

SoftwareSerial secondarySerial(9, 8); // RX, TX
DFMiniMp3<SoftwareSerial, Mp3Notify> mp3(secondarySerial);

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

DS1307 rtc;

char buffer[100];

void custom0(int col)
{ // uses segments to build the number 0
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(8); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(2);  
  lcd.write(6);  
  lcd.write(1);
}

void custom1(int col)
{
  lcd.setCursor(col,0);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
  lcd.setCursor(col,1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom2(int col)
{
  lcd.setCursor(col,0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(6);
}

void custom3(int col)
{
  lcd.setCursor(col,0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1); 
}

void custom4(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom5(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1);
}

void custom6(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
}

void custom7(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(8);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom8(int col)
{
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(3); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(2);  
  lcd.write(6);  
  lcd.write(1);
}

void custom9(int col)
{
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(3); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(7);  
  lcd.write(6);  
  lcd.write(1);
}

void printNumber(int value, int col) {
  if (value == 0) {
    custom0(col);
  } if (value == 1) {
    custom1(col);
  } if (value == 2) {
    custom2(col);
  } if (value == 3) {
    custom3(col);
  } if (value == 4) {
    custom4(col);
  } if (value == 5) {
    custom5(col);
  } if (value == 6) {
    custom6(col);
  } if (value == 7) {
    custom7(col);
  } if (value == 8) {
    custom8(col);
  } if (value == 9) {
    custom9(col);
  }      
} 

void update_time(void)
{
  DateTime now = rtc.now();

  int hh = now.hour();
  int mm = now.minute();
  int ss = now.second();
  printNumber(hh / 10, 0);
  printNumber(hh % 10, 3);
  printNumber(mm / 10, 7);
  printNumber(mm % 10, 10);

  char dot = (ss % 2 == 0) ? ' ' : '\xA5';
  lcd.setCursor(6, 0);
  lcd.print(dot);
  lcd.setCursor(6, 1);
  lcd.print(dot);

  lcd.setCursor(14, 0);
  if (ss < 10)
    lcd.print('0');
  lcd.print(ss);
}

const int BUTTON_PIN = A0;
AceButton button(BUTTON_PIN);

static struct pt time_updater_pt;
static struct pt time_speaker_pt;

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

static bool speak_requested = false;

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

  ButtonConfig* buttonConfig = button.getButtonConfig();
  buttonConfig->setEventHandler(button_event);
  buttonConfig->setFeature(ButtonConfig::kFeatureRepeatPress);

  Wire.begin();
  rtc.begin();

  if (!rtc.isrunning())
    rtc.adjust(DateTime(__DATE__, __TIME__));

  lcd.createChar(1, bar1);
  lcd.createChar(2, bar2);
  lcd.createChar(3, bar3);
  lcd.createChar(4, bar4);
  lcd.createChar(5, bar5);
  lcd.createChar(6, bar6);
  lcd.createChar(7, bar7);
  lcd.createChar(8, bar8);

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
