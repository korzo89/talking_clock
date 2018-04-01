#include "screens.h"
#include "screen_clock.h"
#include "screen_set_volume.h"

//----------------------------------------------------------

namespace Screens
{

ScreenClock screen_clock;
ScreenSetVolume screen_set_volume;

//----------------------------------------------------------

Screen& clock()
{
    return screen_clock;
}

Screen& set_volume()
{
    return screen_set_volume;
}

//----------------------------------------------------------

}