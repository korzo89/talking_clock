#include "screen_clock.h"
#include "audio_player.h"
#include "clock.h"
#include "display.h"
#include "screens.h"

using namespace ace_button;

//----------------------------------------------------------

void ScreenClock::create()
{
    PT_INIT(&updater_pt);
    PT_INIT(&speaker_pt);

    last_update = millis();
    speak_requested = false;
    prev_mm = -1;

    Display::get().clear();
}

//----------------------------------------------------------

void ScreenClock::destroy()
{
}

//----------------------------------------------------------

void ScreenClock::process()
{
    updater();
    speaker();
}

//----------------------------------------------------------

void ScreenClock::button1_event(uint8_t type)
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

void ScreenClock::button2_event(uint8_t type)
{
    if (type == AceButton::kEventPressed)
        ScreenManager::show_screen(Screens::set_volume());
}

void ScreenClock::button3_event(uint8_t type)
{
}

void ScreenClock::button4_event(uint8_t type)
{
}

//----------------------------------------------------------

void ScreenClock::update_time()
{
    auto &lcd = Display::get();

    DateTime now = Clock::get_time();
    uint8_t hh = now.hour();
    uint8_t mm = now.minute();
    uint8_t ss = now.second();
    Display::print_large_number(0,  hh / 10);
    Display::print_large_number(3,  hh % 10);
    Display::print_large_number(7,  mm / 10);
    Display::print_large_number(10, mm % 10);

    char dot = (ss % 2 == 0) ? ' ' : '\xA5';
    lcd.setCursor(6, 0);
    lcd.print(dot);
    lcd.setCursor(6, 1);
    lcd.print(dot);

    lcd.setCursor(14, 0);
    if (ss < 10)
        lcd.print('0');
    lcd.print(ss);

    if ((prev_mm != -1) && (prev_mm == 59) && (mm == 0))
        speak_requested = true;
    prev_mm = mm;
}

//----------------------------------------------------------

PT_THREAD(ScreenClock::updater())
{
    PT_BEGIN(&updater_pt);

    while (1)
    {
        update_time();

        last_update = millis();
        PT_YIELD_UNTIL(&updater_pt, millis() - last_update > 500);
    }

    PT_END(&updater_pt);
}

//----------------------------------------------------------

int8_t ScreenClock::get_hour_clip(uint8_t hh)
{
    if (hh == 0)
        return 12;
    else
        return hh;
}

int8_t ScreenClock::get_minutes_tens_clip(uint8_t mm)
{
    if ((mm >= 10) && (mm < 20))
        return 35 + (mm - 10);

    mm /= 10;
    if (mm == 0)
        return 25;
    else
        return 45 + (mm - 2);
}

int8_t ScreenClock::get_minutes_ones_clip(uint8_t mm)
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

    PT_BEGIN(&speaker_pt);

    while (1)
    {
        PT_YIELD_UNTIL(&speaker_pt, speak_requested);

        now = Clock::get_time();
        hour_clip = get_hour_clip(now.hour());
        tens_clip = get_minutes_tens_clip(now.minute());
        ones_clip = get_minutes_ones_clip(now.minute());

        PLAY_CLIP(&speaker_pt, 49);
        PT_DELAY(&speaker_pt, 100);

        PLAY_CLIP(&speaker_pt, hour_clip);
        PT_DELAY(&speaker_pt, 100);

        PLAY_CLIP(&speaker_pt, tens_clip);
        PT_DELAY(&speaker_pt, 100);

        if (ones_clip != -1)
        {
            PLAY_CLIP(&speaker_pt, ones_clip);
            PT_DELAY(&speaker_pt, 100);
        }

        speak_requested = false;
    }

    PT_END(&speaker_pt);
}
