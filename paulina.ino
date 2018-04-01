#include "settings.h"
#include "large_font.h"
#include "clock.h"
#include "audio_player.h"
#include "screen_manager.h"
#include "screens.h"
#include "buttons.h"

//----------------------------------------------------------

#define LCD_RS      12
#define LCD_EN      11
#define LCD_D4      5
#define LCD_D5      4
#define LCD_D6      3
#define LCD_D7      2

static LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

//----------------------------------------------------------

void setup()
{
    Serial.begin(115200);

    Buttons::init();
    Settings::init();
    Clock::init();
    LargeFont::init(lcd);

    AudioPlayer::init();
    AudioPlayer::set_volume(Settings::get_volume());

    lcd.begin(16, 2);

    ScreenManager::init(&lcd);
    ScreenManager::show_screen(Screens::clock());
}

//----------------------------------------------------------

void loop()
{
    Buttons::process();
    AudioPlayer::process();
    ScreenManager::process();
}
