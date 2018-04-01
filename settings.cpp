#include "settings.h"
#include <EEPROM.h>

//----------------------------------------------------------

namespace Settings
{

#define MAGIC_NUMBER            0xDEADBEEF
#define MAGIC_NUMBER_SIZE       4

#define MAGIC_NUMBER_ADDRESS    0
#define VOLUME_ADDRESS          (MAGIC_NUMBER_ADDRESS + MAGIC_NUMBER_SIZE)

//----------------------------------------------------------

void init()
{
    uint32_t magic;
    EEPROM.get(MAGIC_NUMBER_ADDRESS, magic);

    if (magic == MAGIC_NUMBER)
        return;

    EEPROM.put(MAGIC_NUMBER_ADDRESS, MAGIC_NUMBER);
    set_volume(30);
}

//----------------------------------------------------------

byte get_volume()
{
    byte val;
    return EEPROM.get(VOLUME_ADDRESS, val);
}

void set_volume(byte val)
{
    EEPROM.put(VOLUME_ADDRESS, val);
}

//----------------------------------------------------------

}