#ifndef SCREEN_SET_LED_RED_H_
#define SCREEN_SET_LED_RED_H_

#include "screen_set_value.h"

//----------------------------------------------------------

class ScreenSetLedRed : public ScreenSetValue
{
public:
    void destroy() override;

protected:
    const __FlashStringHelper* get_name() const override;
    byte get_minimum() const override;
    byte get_maximum() const override;
    byte get_digits() const override;
    Screen& get_next_screen() const override;
    byte get_value() const override;
    void save_value(byte val) override;
    virtual void set_value(byte val) override;
};

//----------------------------------------------------------

#endif