#ifndef CLOCK_H_
#define CLOCK_H_

#include <Arduino.h>
#include <RTClib.h>

//----------------------------------------------------------

namespace Clock
{

void init();
DateTime get_time();
void set_time(const DateTime &t);

}

//----------------------------------------------------------

#endif
