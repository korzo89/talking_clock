#include "screen_clock.h"
#include "audio_player.h"
#include "clock.h"
#include "large_font.h"

using namespace ace_button;

//----------------------------------------------------------

void ScreenClock::create()
{
    PT_INIT(&updater_pt);
    PT_INIT(&speaker_pt);

    last_update = millis();
    speak_requested = false;
}

//----------------------------------------------------------

void ScreenClock::destroy()
{
}

//----------------------------------------------------------

void ScreenClock::process(LiquidCrystal &lcd)
{
    updater(lcd);
    speaker();
}

//----------------------------------------------------------

void ScreenClock::button_event(uint8_t type, uint8_t state)
{
    switch (type)
    {
    case AceButton::kEventPressed:
        speak_requested = true;
        break;

    case AceButton::kEventReleased:
        repeat_counter = 0;
        break;

    case AceButton::kEventRepeatPressed:
        repeat_counter++;
        if (repeat_counter == 20)
            AudioPlayer::play_track(50);
        break;

    default:
        break;
    }
}

//----------------------------------------------------------

void ScreenClock::update_time(LiquidCrystal &lcd)
{
    DateTime now = Clock::get_time();
    int hh = now.hour();
    int mm = now.minute();
    int ss = now.second();
    LargeFont::print_number(lcd,  0, hh / 10);
    LargeFont::print_number(lcd,  3, hh % 10);
    LargeFont::print_number(lcd,  7, mm / 10);
    LargeFont::print_number(lcd, 10, mm % 10);

    char dot = (ss % 2 == 0) ? ' ' : '\xA5';
    lcd.setCursor(6, 0);
    lcd.print(dot);
    lcd.setCursor(6, 1);
    lcd.print(dot);

    lcd.setCursor(14, 0);
    if (ss < 10)
        lcd.print('0');
    lcd.print(ss);

    static int prev_mm = -1;
    if ((prev_mm != -1) && (prev_mm == 59) && (mm == 0))
        speak_requested = true;
    prev_mm = mm;
}

//----------------------------------------------------------

PT_THREAD(ScreenClock::updater(LiquidCrystal &lcd))
{
    PT_BEGIN(&updater_pt);

    while (1)
    {
        update_time(lcd);

        last_update = millis();
        PT_YIELD_UNTIL(&updater_pt, millis() - last_update > 500);
    }

    PT_END(&updater_pt);
}

//----------------------------------------------------------

int ScreenClock::get_hour_clip(int hh)
{
    if (hh == 0)
        return 12;
    else
        return hh;
}

int ScreenClock::get_minutes_tens_clip(int mm)
{
    if ((mm >= 10) && (mm < 20))
        return 35 + (mm - 10);

    mm /= 10;
    if (mm == 0)
        return 25;
    else
        return 45 + (mm - 2);
}

int ScreenClock::get_minutes_ones_clip(int mm)
{
    if (mm == 0)
        return 25;

    if ((mm >= 10) && (mm < 20))
        return -1;

    mm %= 10;
    if (mm == 0)
        return -1;
    else
        return 25 + mm;
}

//----------------------------------------------------------

#define PT_DELAY(_pt, _ms)  \
    wait_start = millis();  \
    PT_YIELD_UNTIL(_pt, millis() - wait_start > (_ms));  \

#define PLAY_CLIP(_pt, _clip) \
    AudioPlayer::play_track(_clip); \
    PT_YIELD_UNTIL(_pt, AudioPlayer::is_finished());

PT_THREAD(ScreenClock::speaker())
{
    DateTime now;

    struct pt *pt = &speaker_pt;

    PT_BEGIN(pt);

    while (1)
    {
        PT_YIELD_UNTIL(pt, speak_requested);

        now = Clock::get_time();
        hour_clip = get_hour_clip(now.hour());
        tens_clip = get_minutes_tens_clip(now.minute());
        ones_clip = get_minutes_ones_clip(now.minute());

        PLAY_CLIP(pt, 49);
        PT_DELAY(pt, 100);

        PLAY_CLIP(pt, hour_clip);
        PT_DELAY(pt, 100);

        PLAY_CLIP(pt, tens_clip);
        PT_DELAY(pt, 100);

        if (ones_clip != -1)
        {
            PLAY_CLIP(pt, ones_clip);
            PT_DELAY(pt, 100);
        }

        speak_requested = false;
    }

    PT_END(pt);
}
