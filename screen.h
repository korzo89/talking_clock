#ifndef SCREEN_H_
#define SCREEN_H_

#include <LiquidCrystal.h>

//----------------------------------------------------------

class Screen
{
public:
    virtual void create() = 0;
    virtual void destroy() = 0;
    virtual void process(LiquidCrystal &lcd) = 0;
};

//----------------------------------------------------------

#endif