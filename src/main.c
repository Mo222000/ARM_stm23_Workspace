#include <MCAL/SYSTICK/SYSTICK.h>
#include <HAL/LED/LED.h>
#include <Service/SCHEDULER/SCHED.h>

extern void BlinkingLed (void);

int main ()
{
    LED_init();
    SCHED_Init();
    SCHED_Start();
    
    return 0;
}