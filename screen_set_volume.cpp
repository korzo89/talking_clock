#include "screen_set_volume.h"
#include "settings.h"
#include "screens.h"
#include "display.h"
#include "audio_player.h"

using namespace ace_button;

//----------------------------------------------------------

void ScreenSetVolume::create()
{
    volume = Settings::get_volume();

    Display::get().clear();
    update();
}

//----------------------------------------------------------

void ScreenSetVolume::destroy()
{
    AudioPlayer::set_volume(Settings::get_volume());
}

//----------------------------------------------------------

void ScreenSetVolume::process()
{
}

//----------------------------------------------------------

void ScreenSetVolume::set_volume(byte value)
{
    volume = value;
    update();

    AudioPlayer::set_volume(volume);
    AudioPlayer::play_track(49);
}

//----------------------------------------------------------

void ScreenSetVolume::button1_event(uint8_t type)
{
    if (type == AceButton::kEventPressed)
    {
        Settings::set_volume(volume);
        ScreenManager::show_screen(Screens::clock());
    }
}

void ScreenSetVolume::button2_event(uint8_t type)
{
    switch (type)
    {
    case AceButton::kEventPressed:
    case AceButton::kEventRepeatPressed:
        if (volume > 0)
            set_volume(volume - 1);
        break;

    default:
        break;
    }
}

void ScreenSetVolume::button3_event(uint8_t type)
{
    switch (type)
    {
    case AceButton::kEventPressed:
    case AceButton::kEventRepeatPressed:
        if (volume < 30)
            set_volume(volume + 1);
        break;

    default:
        break;
    }
}

void ScreenSetVolume::button4_event(uint8_t type)
{
    if (type == AceButton::kEventPressed)
        ScreenManager::show_screen(Screens::clock());
}

//----------------------------------------------------------

void ScreenSetVolume::update()
{
    auto &lcd = Display::get();

    lcd.setCursor(0, 0);
    lcd.print(F("Glosnosc"));

    Display::print_large_number(10, volume / 10);
    Display::print_large_number(13, volume % 10);
}
