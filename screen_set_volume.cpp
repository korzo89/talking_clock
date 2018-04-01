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
    AudioPlayer::set_volume(Settings::get_volume());
}

//----------------------------------------------------------

void ScreenSetVolume::process(LiquidCrystal &lcd)
{
}

//----------------------------------------------------------

void ScreenSetVolume::set_volume(LiquidCrystal &lcd, byte value)
{
    volume = value;
    update(lcd);

    AudioPlayer::set_volume(volume);
    AudioPlayer::play_track(49);
}

//----------------------------------------------------------

void ScreenSetVolume::button1_event(LiquidCrystal &lcd, uint8_t type)
{
    if (type == AceButton::kEventPressed)
    {
        Settings::set_volume(volume);
        ScreenManager::show_screen(Screens::clock());
    }
}

void ScreenSetVolume::button2_event(LiquidCrystal &lcd, uint8_t type)
{
    switch (type)
    {
    case AceButton::kEventPressed:
    case AceButton::kEventRepeatPressed:
        if (volume > 0)
            set_volume(lcd, volume - 1);
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
            set_volume(lcd, volume + 1);
        break;

    default:
        break;
    }
}

void ScreenSetVolume::button4_event(LiquidCrystal &lcd, uint8_t type)
{
    if (type == AceButton::kEventPressed)
        ScreenManager::show_screen(Screens::clock());
}

//----------------------------------------------------------

void ScreenSetVolume::update(LiquidCrystal &lcd)
{
    lcd.setCursor(0, 0);
    lcd.print(F("Glosnosc"));

    LargeFont::print_number(lcd, 10, volume / 10);
    LargeFont::print_number(lcd, 13, volume % 10);
}
