#include <HAL/LED/LED.h>

void BlinkingLed(void)
{
    LED_init();
    LED_setstatus(RED_LED, LED_STATE_OFF);
    
}