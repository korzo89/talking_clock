#ifndef SCREEN_SET_VOLUME_H_
#define SCREEN_SET_VOLUME_H_

#include "screen_set_value.h"

//----------------------------------------------------------

class ScreenSetVolume : public ScreenSetValue
{
public:
    void destroy() override;

private:
    const __FlashStringHelper* get_name() const override;
    byte get_minimum() const override;
    byte get_maximum() const override;
    Screen& get_next_screen() const override;
    byte get_value() const override;
    void save_value(byte val) override;
    virtual void set_value(byte val) override;
};

//----------------------------------------------------------

#endif