#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <Arduino.h>

//----------------------------------------------------------

namespace Settings
{

void init();

byte get_volume();
void set_volume(byte val);

byte get_led_red();
void set_led_red(byte val);

byte get_led_green();
void set_led_green(byte val);

byte get_led_blue();
void set_led_blue(byte val);

}

//----------------------------------------------------------

#endif