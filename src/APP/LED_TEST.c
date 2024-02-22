#include <HAL/LED/LED.h>


void LED_TEST ()
{
    LED_init();
    LED_setstatus(RED_LED,LED_STATE_ON);
    LED_setstatus(GREEN_LED,LED_STATE_ON);
    while (1)
    {
        /* code */
    }
    
}