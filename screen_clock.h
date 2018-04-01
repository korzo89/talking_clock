#ifndef SCREEN_CLOCK_H_
#define SCREEN_CLOCK_H_

#include "screen_manager.h"
#include "pt.h"

//----------------------------------------------------------

class ScreenClock : public Screen
{
public:
    void create(LiquidCrystal &lcd) override;
    void destroy(LiquidCrystal &lcd) override;
    void process(LiquidCrystal &lcd) override;
    void button1_event(LiquidCrystal &lcd, uint8_t type) override;
    void button2_event(LiquidCrystal &lcd, uint8_t type) override;
    void button3_event(LiquidCrystal &lcd, uint8_t type) override;
    void button4_event(LiquidCrystal &lcd, uint8_t type) override;

private:
    struct pt updater_pt;
    struct pt speaker_pt;

    bool speak_requested;

    unsigned long last_update;
    unsigned long wait_start;
    unsigned long repeat_counter;

    int hour_clip;
    int tens_clip;
    int ones_clip;

    PT_THREAD(updater(LiquidCrystal &lcd));
    PT_THREAD(speaker());

    void update_time(LiquidCrystal &lcd);
    static int get_hour_clip(int hh);
    static int get_minutes_tens_clip(int mm);
    static int get_minutes_ones_clip(int mm);
};

//----------------------------------------------------------

#endif
