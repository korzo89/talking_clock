#include "screen_set_led_red.h"
#include "settings.h"
#include "screens.h"
#include "display.h"

//----------------------------------------------------------

void ScreenSetLedRed::destroy()
{
    Display::set_led_red(Settings::get_led_red());
}

//----------------------------------------------------------

const __FlashStringHelper* ScreenSetLedRed::get_name() const
{
    return F("LED R");
}

//----------------------------------------------------------

byte ScreenSetLedRed::get_minimum() const
{
    return 0;
}

byte ScreenSetLedRed::get_maximum() const
{
    return 255;
}

byte ScreenSetLedRed::get_digits() const
{
    return 3;
}

//----------------------------------------------------------

Screen& ScreenSetLedRed::get_next_screen() const
{
    return Screens::set_led_green();
}

//----------------------------------------------------------

byte ScreenSetLedRed::get_value() const
{
    return Settings::get_led_red();
}

//----------------------------------------------------------

void ScreenSetLedRed::set_value(byte val)
{
    ScreenSetValue::set_value(val);

    Display::set_led_red(val);
}

//----------------------------------------------------------

void ScreenSetLedRed::save_value(byte val)
{
    Settings::set_led_red(val);
}
