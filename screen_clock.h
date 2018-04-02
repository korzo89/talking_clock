#ifndef SCREEN_CLOCK_H_
#define SCREEN_CLOCK_H_

#include "screen_manager.h"
#include "pt.h"

//----------------------------------------------------------

class ScreenClock : public Screen
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
    struct pt updater_pt;
    struct pt speaker_pt;

    bool speak_requested;

    unsigned long last_update;
    unsigned long wait_start;
    unsigned long repeat_counter;

    int8_t prev_mm;
    int8_t hour_clip;
    int8_t tens_clip;
    int8_t ones_clip;

    PT_THREAD(updater());
    PT_THREAD(speaker());

    void update_time();
    static int8_t get_hour_clip(uint8_t hh);
    static int8_t get_minutes_tens_clip(uint8_t mm);
    static int8_t get_minutes_ones_clip(uint8_t mm);
};

//----------------------------------------------------------

#endif
