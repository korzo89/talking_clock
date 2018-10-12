#include "screen_set_value.h"
#include "settings.h"
#include "screens.h"
#include "display.h"

using namespace ace_button;

//----------------------------------------------------------

void ScreenSetValue::create()
{
    value = get_value();

    Display::get().clear();
    update();
}

//----------------------------------------------------------

void ScreenSetValue::destroy()
{
}

//----------------------------------------------------------

void ScreenSetValue::process()
{
}

//----------------------------------------------------------

void ScreenSetValue::set_value(byte val)
{
    value = val;
    update();
}

//----------------------------------------------------------

void ScreenSetValue::button1_event(uint8_t type)
{
    if (type == AceButton::kEventPressed)
    {
        save_value(value);
        ScreenManager::show_screen(get_next_screen());
    }
}

void ScreenSetValue::button2_event(uint8_t type)
{
    if (type == AceButton::kEventPressed)
        ScreenManager::show_screen(get_next_screen());
}

void ScreenSetValue::button3_event(uint8_t type)
{
    switch (type)
    {
    case AceButton::kEventPressed:
    case AceButton::kEventRepeatPressed:
        if (value > get_minimum())
            set_value(value - 1);
        break;

    default:
        break;
    }
}

void ScreenSetValue::button4_event(uint8_t type)
{
    switch (type)
    {
    case AceButton::kEventPressed:
    case AceButton::kEventRepeatPressed:
        if (value < get_maximum())
            set_value(value + 1);
        break;

    default:
        break;
    }
}

//----------------------------------------------------------

void ScreenSetValue::update()
{
    auto &lcd = Display::get();

    byte temp = value;

    if (get_digits() == 3)
    {
        Display::print_large_number(7, temp / 100);
        temp %= 100;
    }

    Display::print_large_number(10, temp / 10);
    Display::print_large_number(13, temp % 10);

    lcd.setCursor(0, 0);
    lcd.print(get_name());
}
