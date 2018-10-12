#include "display.h"
#include "hal.h"
#include <Arduino.h>

//----------------------------------------------------------

namespace Display
{

//----------------------------------------------------------

const PROGMEM byte bar1[8] = {
    B11100,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11100
};

const PROGMEM byte bar2[8] = {
    B00111,
    B01111,
    B01111,
    B01111,
    B01111,
    B01111,
    B01111,
    B00111
};

const PROGMEM byte bar3[8] = {
    B11111,
    B11111,
    B00000,
    B00000,
    B00000,
    B00000,
    B11111,
    B11111
};

const PROGMEM byte bar4[8] = {
    B11110,
    B11100,
    B00000,
    B00000,
    B00000,
    B00000,
    B11000,
    B11100
};

const PROGMEM byte bar5[8] = {
    B01111,
    B00111,
    B00000,
    B00000,
    B00000,
    B00000,
    B00011,
    B00111
};

const PROGMEM byte bar6[8] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B11111,
    B11111
};

const PROGMEM byte bar7[8] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00111,
    B01111
};

const PROGMEM byte bar8[8] = {
    B11111,
    B11111,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000
};

const PROGMEM byte large_font[][6] = {
    {  2,  8,  1,  2,  6,  1 },
    { 32, 32,  1, 32, 32,  1 },
    {  5,  3,  1,  2,  6,  6 },
    {  5,  3,  1,  7,  6,  1 },
    {  2,  6,  1, 32, 32,  1 },
    {  2,  3,  4,  7,  6,  1 },
    {  2,  3,  4,  2,  6,  1 },
    {  2,  8,  1, 32, 32,  1 },
    {  2,  3,  1,  2,  6,  1 },
    {  2,  3,  1,  7,  6,  1 },
};

//----------------------------------------------------------

LiquidCrystal lcd(
    HAL_LCD_RS_PIN, HAL_LCD_EN_PIN, 
    HAL_LCD_D4_PIN, HAL_LCD_D5_PIN, 
    HAL_LCD_D6_PIN, HAL_LCD_D7_PIN);

//----------------------------------------------------------

void init_custom_char(LiquidCrystal &lcd, int id, const byte *def)
{
    byte temp[8];
    for (int i = 0; i < sizeof(temp); i++)
        temp[i] = pgm_read_byte_near(def + i);

    lcd.createChar(id, temp);
}

//----------------------------------------------------------

void init()
{
    lcd.begin(16, 2);

    init_custom_char(lcd, 1, bar1);
    init_custom_char(lcd, 2, bar2);
    init_custom_char(lcd, 3, bar3);
    init_custom_char(lcd, 4, bar4);
    init_custom_char(lcd, 5, bar5);
    init_custom_char(lcd, 6, bar6);
    init_custom_char(lcd, 7, bar7);
    init_custom_char(lcd, 8, bar8);
}

//----------------------------------------------------------

LiquidCrystal& get()
{
    return lcd;
}

//----------------------------------------------------------

void print_large_char(const byte *def, int offset)
{
    byte id = pgm_read_byte_near(def + offset);
    lcd.write(id);
}

//----------------------------------------------------------

void print_large_number(int col, int num)
{
    const byte *def = large_font[num];

    lcd.setCursor(col, 0);
    print_large_char(def, 0);
    print_large_char(def, 1);
    print_large_char(def, 2);
    lcd.setCursor(col, 1);
    print_large_char(def, 3);
    print_large_char(def, 4);
    print_large_char(def, 5);
}

//----------------------------------------------------------

}
