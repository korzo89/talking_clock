#include "settings.h"
#include "large_font.h"
#include "clock.h"
#include "audio_player.h"
#include "screen_manager.h"
#include "screens.h"

//----------------------------------------------------------

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

//----------------------------------------------------------

void button_event(AceButton* button, uint8_t type, uint8_t state) 
{
    ScreenManager::button_event(lcd, type, state);
}

//----------------------------------------------------------

void setup()
{
    Serial.begin(115200);

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    ButtonConfig *cfg = button.getButtonConfig();
    cfg->setEventHandler(button_event);
    cfg->setFeature(ButtonConfig::kFeatureRepeatPress);

    Settings::init();
    Clock::init();
    LargeFont::init(lcd);

    AudioPlayer::init();
    AudioPlayer::set_volume(Settings::get_volume());

    lcd.begin(16, 2);

    ScreenManager::show_screen(lcd, Screens::clock());
}

//----------------------------------------------------------

void loop()
{
    button.check();
    AudioPlayer::process();
    ScreenManager::process(lcd);
}
