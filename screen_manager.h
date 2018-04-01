#ifndef SCREEN_H_
#define SCREEN_H_

#include <LiquidCrystal.h>
#include <AceButton.h>

//----------------------------------------------------------

class Screen
{
public:
    virtual void create(LiquidCrystal &lcd) = 0;
    virtual void destroy(LiquidCrystal &lcd) = 0;
    virtual void process(LiquidCrystal &lcd) = 0;
    virtual void button_event(LiquidCrystal &lcd, uint8_t type, uint8_t state) = 0;
};

//----------------------------------------------------------

namespace ScreenManager
{

void show_screen(LiquidCrystal &lcd, Screen &screen);
void process(LiquidCrystal &lcd);
void button_event(LiquidCrystal &lcd, uint8_t type, uint8_t state);

}

//----------------------------------------------------------

#endif