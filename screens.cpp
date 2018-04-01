#include "screens.h"
#include "screen_clock.h"
#include "screen_set_volume.h"
#include "screen_set_hour.h"
#include "screen_set_minute.h"

//----------------------------------------------------------

namespace Screens
{

ScreenClock screen_clock;
ScreenSetVolume screen_set_volume;
ScreenSetHour screen_set_hour;
ScreenSetMinute screen_set_minute;

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

//----------------------------------------------------------

}