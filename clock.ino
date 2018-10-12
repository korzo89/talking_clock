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
    
    ScreenManager::show_screen(Screens::clock());
}

//----------------------------------------------------------

void loop()
{
    Buttons::process();
    AudioPlayer::process();
    ScreenManager::process();
}
