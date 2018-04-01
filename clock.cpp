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
        rtc.adjust(DateTime(__DATE__, "12:00:00"));
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
