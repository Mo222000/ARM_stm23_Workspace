#include <MCAL/SYSTICK/SYSTICK.h>
#include <HAL/LED/LED.h>

uint8_t static volatile RED_FLAG = 0;
void SYSTICK_HANDLER (void)
{
    if (RED_FLAG == 0)
    {
        LED_setstatus(RED_LED, LED_STATE_ON);
        RED_FLAG = 1;    
    }
    else
    {
        LED_setstatus(RED_LED, LED_STATE_OFF);
        RED_FLAG = 0;
    }    
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