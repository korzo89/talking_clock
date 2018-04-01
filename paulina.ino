#include "display.h"
#include "settings.h"
#include "clock.h"
#include "audio_player.h"
#include "screen_manager.h"
#include "screens.h"
#include "buttons.h"

//----------------------------------------------------------

void setup()
{
    Buttons::init();
    Settings::init();
    Clock::init();

    AudioPlayer::init();
    AudioPlayer::set_volume(Settings::get_volume());

    Display::init();
    Display::set_led_red(Settings::get_led_red());
    Display::set_led_green(Settings::get_led_green());
    Display::set_led_blue(Settings::get_led_blue());

    ScreenManager::show_screen(Screens::clock());
}

//----------------------------------------------------------

void loop()
{
    Buttons::process();
    AudioPlayer::process();
    ScreenManager::process();
}
