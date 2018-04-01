#ifndef SCREEN_SET_VALUE_H_
#define SCREEN_SET_VALUE_H_

#include "screen_manager.h"

//----------------------------------------------------------

class ScreenSetValue : public Screen
{
public:
    virtual void create() override;
    virtual void destroy() override;
    virtual void process() override;
    virtual void button1_event(uint8_t type) override;
    virtual void button2_event(uint8_t type) override;
    virtual void button3_event(uint8_t type) override;
    virtual void button4_event(uint8_t type) override;

protected:
    byte value;

    virtual const __FlashStringHelper* get_name() const = 0;
    virtual byte get_minimum() const = 0;
    virtual byte get_maximum() const = 0;
    virtual byte get_digits() const = 0;
    virtual Screen& get_next_screen() const = 0;
    virtual byte get_value() const = 0;
    virtual void save_value(byte val) = 0;
    virtual void set_value(byte val);

    void update();
};

//----------------------------------------------------------

#endif