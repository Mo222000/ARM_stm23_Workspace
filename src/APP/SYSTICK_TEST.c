#include <MCAL/SYSTICK/SYSTICK.h>
#include <HAL/LED/LED.h>

void SYSTICK_HANDLER (void)
{
    LED_Toggle(RED_LED);
}

void SYSTICK_TSET (void)
{
    LED_init();
    SYSTICK_SetTime_ms(1000);
    SYSTICK_ControlIRQ(SYSTICK_IQR_ENABLE);
    SYSTICK_ConfigureClock(SYSTICK_CLOCK_AHB);
    SYSTICK_SetCallBack(&SYSTICK_HANDLER);
    SYSTICK_StartTimer();
    while (1)
    {

    }
}