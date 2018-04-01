#include "screen_set_led_blue.h"
#include "settings.h"
#include "screens.h"
#include "display.h"

//----------------------------------------------------------

void ScreenSetLedBlue::destroy()
{
    Display::set_led_blue(Settings::get_led_blue());
}

//----------------------------------------------------------

const __FlashStringHelper* ScreenSetLedBlue::get_name() const
{
    return F("LED B");
}

//----------------------------------------------------------

byte ScreenSetLedBlue::get_minimum() const
{
    return 0;
}

byte ScreenSetLedBlue::get_maximum() const
{
    return 255;
}

byte ScreenSetLedBlue::get_digits() const
{
    return 3;
}

//----------------------------------------------------------

Screen& ScreenSetLedBlue::get_next_screen() const
{
    return Screens::clock();
}

//----------------------------------------------------------

byte ScreenSetLedBlue::get_value() const
{
    return Settings::get_led_blue();
}

//----------------------------------------------------------

void ScreenSetLedBlue::set_value(byte val)
{
    ScreenSetValue::set_value(val);

    Display::set_led_blue(val);
}

//----------------------------------------------------------

void ScreenSetLedBlue::save_value(byte val)
{
    Settings::set_led_blue(val);
}
