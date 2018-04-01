#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <Arduino.h>

//----------------------------------------------------------

namespace Settings
{

void init();

byte get_volume();
void set_volume(byte val);

}

//----------------------------------------------------------

#endif