#include "screens.h"
#include "screen_clock.h"
#include "screen_set_volume.h"
#include "screen_set_hour.h"
#include "screen_set_minute.h"
#include "screen_set_led_red.h"
#include "screen_set_led_green.h"
#include "screen_set_led_blue.h"

//----------------------------------------------------------

namespace Screens
{

ScreenClock screen_clock;
ScreenSetVolume screen_set_volume;
ScreenSetHour screen_set_hour;
ScreenSetMinute screen_set_minute;
ScreenSetLedRed screen_set_led_red;
ScreenSetLedGreen screen_set_led_green;
ScreenSetLedBlue screen_set_led_blue;

//----------------------------------------------------------

Screen& clock()
{
    return screen_clock;
}

Screen& set_volume()
{
    return screen_set_volume;
}

Screen& set_hour()
{
    return screen_set_hour;
}

Screen& set_minute()
{
    return screen_set_minute;
}

Screen& set_led_red()
{
    return screen_set_led_red;
}

Screen& set_led_green()
{
    return screen_set_led_green;
}

Screen& set_led_blue()
{
    return screen_set_led_blue;
}

//----------------------------------------------------------

}