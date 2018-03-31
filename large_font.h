#ifndef LARGE_FONT_H_
#define LARGE_FONT_H_

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

#endif
