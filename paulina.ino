#include <LiquidCrystal.h>
#include <AceButton.h>
#include "pt.h"
#include "large_font.h"
#include "clock.h"
#include "audio_player.h"
#include "screen_clock.h"

#define LCD_RS      12
#define LCD_EN      11
#define LCD_D4      5
#define LCD_D5      4
#define LCD_D6      3
#define LCD_D7      2



#define BUTTON_PIN  A0

using namespace ace_button;

static LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);



static AceButton button(BUTTON_PIN);

static char buffer[32];

ScreenClock screen_clock;

void button_event(AceButton* button, uint8_t eventType, uint8_t buttonState) 
{
  static unsigned long repeat_counter = 0;
  
  switch (eventType)
  {
  case AceButton::kEventPressed:
    //speak_requested = true;
    break;

  case AceButton::kEventReleased:
    repeat_counter = 0;
    break;

  case AceButton::kEventRepeatPressed:
    repeat_counter++;
    if (repeat_counter == 20)
      AudioPlayer::play_track(50);
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

  Clock::init();

  LargeFont::init(lcd);

  AudioPlayer::init();
  AudioPlayer::set_volume(30);

  lcd.begin(16, 2);
  
  screen_clock.create();
}

void loop() 
{
  button.check();
  AudioPlayer::process();
  
  screen_clock.process(lcd);

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
      Clock::set_time(date);
    }
  }
}
