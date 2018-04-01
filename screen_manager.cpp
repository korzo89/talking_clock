#include "screen_manager.h"

//----------------------------------------------------------

namespace ScreenManager
{

LiquidCrystal *display;
Screen *current_screen = nullptr;

//----------------------------------------------------------

void init(LiquidCrystal *lcd)
{
    display = lcd;
}

//----------------------------------------------------------

void show_screen(Screen &screen)
{
    if (current_screen)
        current_screen->destroy(*display);

    screen.create(*display);
    current_screen = &screen;
}

//----------------------------------------------------------

void process()
{
    if (current_screen)
        current_screen->process(*display);
}

//----------------------------------------------------------

void button1_event(uint8_t type)
{
    if (current_screen)
        current_screen->button1_event(*display, type);
}

void button2_event(uint8_t type)
{
    if (current_screen)
        current_screen->button2_event(*display, type);
}

void button3_event(uint8_t type)
{
    if (current_screen)
        current_screen->button3_event(*display, type);
}

void button4_event(uint8_t type)
{
    if (current_screen)
        current_screen->button4_event(*display, type);
}

//----------------------------------------------------------

}