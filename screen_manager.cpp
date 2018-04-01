#include "screen_manager.h"

//----------------------------------------------------------

namespace ScreenManager
{

Screen *current_screen = nullptr;

//----------------------------------------------------------

void show_screen(LiquidCrystal &lcd, Screen &screen)
{
    if (current_screen)
        current_screen->destroy(lcd);

    screen.create(lcd);
    current_screen = &screen;
}

//----------------------------------------------------------

void process(LiquidCrystal &lcd)
{
    if (current_screen)
        current_screen->process(lcd);
}

//----------------------------------------------------------

void button_event(LiquidCrystal &lcd, uint8_t type, uint8_t state)
{
    if (current_screen)
        current_screen->button_event(lcd, type, state);
}

//----------------------------------------------------------

}