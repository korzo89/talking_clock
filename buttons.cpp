#include "buttons.h"
#include <AceButton.h>
#include "screen_manager.h"

using namespace ace_button;

//----------------------------------------------------------

namespace Buttons
{

#define BUTTON1_PIN  A0
#define BUTTON2_PIN  A1
#define BUTTON3_PIN  A2
#define BUTTON4_PIN  A3

AceButton button1(BUTTON1_PIN);
AceButton button2(BUTTON2_PIN);
AceButton button3(BUTTON3_PIN);
AceButton button4(BUTTON4_PIN);

//----------------------------------------------------------

void button_event(AceButton* button, uint8_t type, uint8_t state) 
{
    if (button == &button1)
        ScreenManager::button1_event(type);
    else if (button == &button2)
        ScreenManager::button2_event(type);
    else if (button == &button3)
        ScreenManager::button3_event(type);
    else if (button == &button4)
        ScreenManager::button4_event(type);
}

//----------------------------------------------------------

void init_button(AceButton &button)
{
    pinMode(button.getPin(), INPUT_PULLUP);

    ButtonConfig *cfg = button.getButtonConfig();
    cfg->setFeature(ButtonConfig::kFeatureRepeatPress);
    cfg->setEventHandler(button_event);
}

//----------------------------------------------------------

void init()
{
    init_button(button1);
    init_button(button2);
    init_button(button3);
    init_button(button4);
}

//----------------------------------------------------------

void process()
{
    button1.check();
    button2.check();
    button3.check();
    button4.check();
}

//----------------------------------------------------------

}
