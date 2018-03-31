#ifndef LARGE_FONT_H_
#define LARGE_FONT_H_

#include <LiquidCrystal.h>

//----------------------------------------------------------

namespace LargeFont
{

void init(LiquidCrystal &lcd);
void print_number(LiquidCrystal &lcd, int col, int num);

}

//----------------------------------------------------------

#endif
