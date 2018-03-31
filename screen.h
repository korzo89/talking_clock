#ifndef SCREEN_H_
#define SCREEN_H_

#include <LiquidCrystal.h>
#include <AceButton.h>

//----------------------------------------------------------

class Screen
{
public:
    virtual void create() = 0;
    virtual void destroy() = 0;
    virtual void process(LiquidCrystal &lcd) = 0;
    virtual void button_event(uint8_t type, uint8_t state) = 0;
};

//----------------------------------------------------------

#endif