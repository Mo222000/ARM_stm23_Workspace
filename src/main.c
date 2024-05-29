#include <HAL/LCD/LCD.h>
#include <Service/SCHEDULER/SCHED.h>
#include <HAL/LED/LED.h>
void LCD_Write()
{
    static uint8_t counter = 0;
    if(counter == 0)
    {
        //LCD_ClearAsynch();
        //LCD_WriteNumberAsynch(256);
        LCD_WriteStringAsynch("ahmed");
        counter++;
    }

    else if(counter == 100)
    {
        LCD_ClearAsynch();
        LED_Toggle(RED_LED);
    }
    
}


int main()
{
    LED_init();
    LCD_initAsynch();   
    SCHED_Init();
    SCHED_Start();
    LED_setstatus(GREEN_LED, LED_STATE_ON);
    return 0;
}
