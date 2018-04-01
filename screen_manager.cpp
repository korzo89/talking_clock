#include "screen_manager.h"

//----------------------------------------------------------

namespace ScreenManager
{

Screen *current_screen = nullptr;

//----------------------------------------------------------

void show_screen(Screen &screen)
{
    if (current_screen)
        current_screen->destroy();

    screen.create();
    current_screen = &screen;
}

//----------------------------------------------------------

void process()
{
    if (current_screen)
        current_screen->process();
}

//----------------------------------------------------------

void button1_event(uint8_t type)
{
    if (current_screen)
        current_screen->button1_event(type);
}

void button2_event(uint8_t type)
{
    if (current_screen)
        current_screen->button2_event(type);
}

void button3_event(uint8_t type)
{
    if (current_screen)
        current_screen->button3_event(type);
}

void button4_event(uint8_t type)
{
    if (current_screen)
        current_screen->button4_event(type);
}

//----------------------------------------------------------

}