#ifndef SCREEN_SET_VOLUME_H_
#define SCREEN_SET_VOLUME_H_

#include "screen_manager.h"

//----------------------------------------------------------

class ScreenSetVolume : public Screen
{
public:
    void create(LiquidCrystal &lcd) override;
    void destroy(LiquidCrystal &lcd) override;
    void process(LiquidCrystal &lcd) override;
    void button_event(LiquidCrystal &lcd, uint8_t type, uint8_t state) override;

private:
    byte volume;

    void update(LiquidCrystal &lcd);
};

//----------------------------------------------------------

#endif