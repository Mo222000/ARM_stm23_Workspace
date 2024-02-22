#include <HAL/LED/LED.h>
#include <HAL/SWITCH/SWITCH.h>

uint8_t flag =0;
uint8_t sw_state =0;

void LED_TEST ()
{
    LED_init();
    SWITCH_init();
    LED_setstatus(RED_LED,LED_STATE_ON);
    LED_setstatus(GREEN_LED,LED_STATE_ON);
    while (1)
    {
        SWITCH_GetStatus(Test_Switch, &sw_state);

        while (sw_state == SWITCH_NOTPRESSED)
        {
            SWITCH_GetStatus(Test_Switch, &sw_state);
        }
        if (flag == 0)
        {
            LED_setstatus(RED_LED, LED_STATE_ON);
            flag = 1;
        }
        else if (flag == 1)
        {
            LED_setstatus(RED_LED, LED_STATE_OFF);
            flag = 0;
        }

        while (sw_state == SWITCH_PRESSED)
        {
            SWITCH_GetStatus(Test_Switch, &sw_state);
        }
        
    }
    
}