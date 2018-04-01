#include "screen_set_volume.h"
#include "settings.h"
#include "screens.h"
#include "large_font.h"
#include "audio_player.h"

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
    AudioPlayer::set_volume(volume);
    Settings::set_volume(volume);
}

//----------------------------------------------------------

void ScreenSetVolume::process(LiquidCrystal &lcd)
{
}

//----------------------------------------------------------

void ScreenSetVolume::button1_event(LiquidCrystal &lcd, uint8_t type)
{
    switch (type)
    {
    case AceButton::kEventPressed:
        ScreenManager::show_screen(Screens::clock());
        break;

    default:
        break;
    }
}

void ScreenSetVolume::button2_event(LiquidCrystal &lcd, uint8_t type)
{
    switch (type)
    {
    case AceButton::kEventPressed:
    case AceButton::kEventRepeatPressed:
        if (volume > 0)
        {
            volume--;
            update(lcd);
        }
        break;

    default:
        break;
    }
}

void ScreenSetVolume::button3_event(LiquidCrystal &lcd, uint8_t type)
{
    switch (type)
    {
    case AceButton::kEventPressed:
    case AceButton::kEventRepeatPressed:
        if (volume < 30)
        {
            volume++;
            update(lcd);
        }
        break;

    default:
        break;
    }
}

void ScreenSetVolume::button4_event(LiquidCrystal &lcd, uint8_t type)
{
}

//----------------------------------------------------------

void ScreenSetVolume::update(LiquidCrystal &lcd)
{
    lcd.setCursor(0, 0);
    lcd.print(F("Glosnosc"));

    LargeFont::print_number(lcd, 10, volume / 10);
    LargeFont::print_number(lcd, 13, volume % 10);
}
