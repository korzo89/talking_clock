#include "clock.h"
#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>

//----------------------------------------------------------

namespace Clock
{

//----------------------------------------------------------

static DS1307 rtc;

//----------------------------------------------------------

void init()
{
    Wire.begin();
    rtc.begin();

    if (!rtc.isrunning())
    {
        DateTime now;
        now.sethour(12);
        rtc.adjust(now);
    }
}

//----------------------------------------------------------

DateTime get_time()
{
    return rtc.now();
}

//----------------------------------------------------------

void set_time(const DateTime &t)
{
    rtc.adjust(t);
}

//----------------------------------------------------------

}
