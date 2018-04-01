#include "buttons.h"
#include "hal.h"
#include "screen_manager.h"
#include <AceButton.h>

using namespace ace_button;

//----------------------------------------------------------

namespace Buttons
{

AceButton button1(HAL_BUTTON1_PIN);
AceButton button2(HAL_BUTTON2_PIN);
AceButton button3(HAL_BUTTON3_PIN);
AceButton button4(HAL_BUTTON4_PIN);

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
