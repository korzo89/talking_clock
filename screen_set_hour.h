#ifndef SCREEN_SET_HOUR_H_
#define SCREEN_SET_HOUR_H_

#include "screen_set_value.h"

//----------------------------------------------------------

class ScreenSetHour : public ScreenSetValue
{
protected:
    const __FlashStringHelper* get_name() const override;
    byte get_minimum() const override;
    byte get_maximum() const override;
    Screen& get_next_screen() const override;
    byte get_value() const override;
    void save_value(byte val) override;
};

//----------------------------------------------------------

#endif