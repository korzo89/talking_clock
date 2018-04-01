#ifndef SCREENS_H_
#define SCREENS_H_

#include "screen_manager.h"

//----------------------------------------------------------

namespace Screens
{

Screen& clock();
Screen& set_volume();
Screen& set_hour();
Screen& set_minute();
Screen& set_led_red();

}

//----------------------------------------------------------

#endif