#include "screen_set_volume.h"
#include "settings.h"
#include "screens.h"
#include "display.h"
#include "audio_player.h"

using namespace ace_button;

//----------------------------------------------------------

void ScreenSetVolume::destroy()
{
    AudioPlayer::set_volume(Settings::get_volume());
}

//----------------------------------------------------------

const __FlashStringHelper* ScreenSetVolume::get_name() const
{
    return F("Glosnosc");
}

//----------------------------------------------------------

byte ScreenSetVolume::get_minimum() const
{
    return 0;
}

byte ScreenSetVolume::get_maximum() const
{
    return 30;
}

//----------------------------------------------------------

Screen& ScreenSetVolume::get_next_screen() const
{
    return Screens::clock();
}

//----------------------------------------------------------

byte ScreenSetVolume::get_value() const
{
    return Settings::get_volume();
}

//----------------------------------------------------------

void ScreenSetVolume::set_value(byte val)
{
    ScreenSetValue::set_value(val);

    AudioPlayer::set_volume(val);
    AudioPlayer::play_track(49);
}

//----------------------------------------------------------

void ScreenSetVolume::save_value(byte val)
{
    Settings::set_volume(val);
}
