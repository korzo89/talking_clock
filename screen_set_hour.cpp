#include "screen_set_hour.h"
#include "clock.h"
#include "screens.h"

//----------------------------------------------------------

const __FlashStringHelper* ScreenSetHour::get_name() const
{
    return F("Godzina");
}

//----------------------------------------------------------

byte ScreenSetHour::get_minimum() const
{
    return 0;
}

byte ScreenSetHour::get_maximum() const
{
    return 23;
}

byte ScreenSetHour::get_digits() const
{
    return 2;
}

//----------------------------------------------------------

Screen& ScreenSetHour::get_next_screen() const
{
    return Screens::set_minute();
}

//----------------------------------------------------------

byte ScreenSetHour::get_value() const
{
    return Clock::get_time().hour();
}

//----------------------------------------------------------

void ScreenSetHour::save_value(byte val)
{
    auto now = Clock::get_time();
    now.sethour(val);
    Clock::set_time(now);
}
