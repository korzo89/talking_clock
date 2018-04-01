#include "screen_set_led_green.h"
#include "settings.h"
#include "screens.h"
#include "display.h"

//----------------------------------------------------------

void ScreenSetLedGreen::destroy()
{
    Display::set_led_green(Settings::get_led_green());
}

//----------------------------------------------------------

const __FlashStringHelper* ScreenSetLedGreen::get_name() const
{
    return F("LED G");
}

//----------------------------------------------------------

byte ScreenSetLedGreen::get_minimum() const
{
    return 0;
}

byte ScreenSetLedGreen::get_maximum() const
{
    return 255;
}

byte ScreenSetLedGreen::get_digits() const
{
    return 3;
}

//----------------------------------------------------------

Screen& ScreenSetLedGreen::get_next_screen() const
{
    return Screens::set_led_blue();
}

//----------------------------------------------------------

byte ScreenSetLedGreen::get_value() const
{
    return Settings::get_led_green();
}

//----------------------------------------------------------

void ScreenSetLedGreen::set_value(byte val)
{
    ScreenSetValue::set_value(val);

    Display::set_led_green(val);
}

//----------------------------------------------------------

void ScreenSetLedGreen::save_value(byte val)
{
    Settings::set_led_green(val);
}
