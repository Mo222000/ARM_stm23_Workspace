#include <HAL/LED/LED.h>

void BlinkingLed (void)
{
    LED_Toggle(RED_LED);
    LED_Toggle(GREEN_LED);
}