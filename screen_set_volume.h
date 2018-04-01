#ifndef SCREEN_SET_VOLUME_H_
#define SCREEN_SET_VOLUME_H_

#include "screen_manager.h"

//----------------------------------------------------------

class ScreenSetVolume : public Screen
{
public:
    void create() override;
    void destroy() override;
    void process() override;
    void button1_event(uint8_t type) override;
    void button2_event(uint8_t type) override;
    void button3_event(uint8_t type) override;
    void button4_event(uint8_t type) override;

private:
    byte volume;

    void set_volume(byte value);
    void update();
};

//----------------------------------------------------------

#endif