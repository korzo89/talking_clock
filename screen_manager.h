#ifndef SCREEN_H_
#define SCREEN_H_

#include <AceButton.h>

//----------------------------------------------------------

class Screen
{
public:
    virtual void create() = 0;
    virtual void destroy() = 0;
    virtual void process() = 0;
    virtual void button1_event(uint8_t type) = 0;
    virtual void button2_event(uint8_t type) = 0;
    virtual void button3_event(uint8_t type) = 0;
    virtual void button4_event(uint8_t type) = 0;
};

//----------------------------------------------------------

namespace ScreenManager
{

void show_screen(Screen &screen);
void process();
void button1_event(uint8_t type);
void button2_event(uint8_t type);
void button3_event(uint8_t type);
void button4_event(uint8_t type);

}

//----------------------------------------------------------

#endif