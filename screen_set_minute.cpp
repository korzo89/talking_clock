#include "screen_set_minute.h"
#include "clock.h"
#include "screens.h"

//----------------------------------------------------------

const __FlashStringHelper* ScreenSetMinute::get_name() const
{
    return F("Minuta");
}

//----------------------------------------------------------

byte ScreenSetMinute::get_minimum() const
{
    return 0;
}

byte ScreenSetMinute::get_maximum() const
{
    return 59;
}

byte ScreenSetMinute::get_digits() const
{
    return 2;
}

//----------------------------------------------------------

Screen& ScreenSetMinute::get_next_screen() const
{
    return Screens::clock();
}

//----------------------------------------------------------

byte ScreenSetMinute::get_value() const
{
    return Clock::get_time().minute();
}

//----------------------------------------------------------

void ScreenSetMinute::save_value(byte val)
{
    auto now = Clock::get_time();
    now.setminute(val);
    Clock::set_time(now);
}
