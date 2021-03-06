#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <Arduino.h>
#include <LiquidCrystal.h>

//----------------------------------------------------------

namespace Display
{

void init();
LiquidCrystal& get();

void print_large_number(int col, int num);

}

//----------------------------------------------------------

#endif
