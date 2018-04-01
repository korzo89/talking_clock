#include "screen_set_volume.h"
#include "settings.h"
#include "screens.h"

using namespace ace_button;

//----------------------------------------------------------

void ScreenSetVolume::create(LiquidCrystal &lcd)
{
    volume = Settings::get_volume();

    lcd.clear();
    update(lcd);
}

//----------------------------------------------------------

void ScreenSetVolume::destroy(LiquidCrystal &lcd)
{
}

//----------------------------------------------------------

void ScreenSetVolume::process(LiquidCrystal &lcd)
{
}

//----------------------------------------------------------

void ScreenSetVolume::button_event(LiquidCrystal &lcd, uint8_t type, uint8_t state)
{
    switch (type)
    {
    case AceButton::kEventPressed:
        ScreenManager::show_screen(lcd, Screens::clock());
        break;

    case AceButton::kEventRepeatPressed:
        break;

    default:
        break;
    }
}

//----------------------------------------------------------

void ScreenSetVolume::update(LiquidCrystal &lcd)
{
    lcd.setCursor(0, 0);
    lcd.print(F("Glosnosc"));

}
