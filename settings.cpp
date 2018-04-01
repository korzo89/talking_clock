#include "settings.h"
#include <EEPROM.h>

//----------------------------------------------------------

namespace Settings
{

#define MAGIC_NUMBER            0xDEADBEEF
#define MAGIC_NUMBER_SIZE       4

#define MAGIC_NUMBER_ADDRESS    0
#define VOLUME_ADDRESS          (MAGIC_NUMBER_ADDRESS + MAGIC_NUMBER_SIZE)
#define LED_RED_ADDRESS         (VOLUME_ADDRESS + 1)
#define LED_GREEN_ADDRESS       (LED_RED_ADDRESS + 1)
#define LED_BLUE_ADDRESS        (LED_GREEN_ADDRESS + 1)

//----------------------------------------------------------

void init()
{
    uint32_t magic;
    EEPROM.get(MAGIC_NUMBER_ADDRESS, magic);

    if (magic == MAGIC_NUMBER)
        return;

    EEPROM.put(MAGIC_NUMBER_ADDRESS, MAGIC_NUMBER);

    set_volume(30);
    set_led_red(255);
    set_led_green(255);
    set_led_blue(255);
}

//----------------------------------------------------------

byte get_volume()
{
    return EEPROM.read(VOLUME_ADDRESS);
}

void set_volume(byte val)
{
    EEPROM.write(VOLUME_ADDRESS, val);
}

//----------------------------------------------------------

byte get_led_red()
{
    return EEPROM.read(LED_RED_ADDRESS);
}

void set_led_red(byte val)
{
    EEPROM.write(LED_RED_ADDRESS, val);
}

//----------------------------------------------------------

byte get_led_green()
{
    return EEPROM.read(LED_GREEN_ADDRESS);
}

void set_led_green(byte val)
{
    EEPROM.write(LED_GREEN_ADDRESS, val);
}

//----------------------------------------------------------

byte get_led_blue()
{
    return EEPROM.read(LED_BLUE_ADDRESS);
}

void set_led_blue(byte val)
{
    EEPROM.write(LED_BLUE_ADDRESS, val);
}

//----------------------------------------------------------

}