#include <HAL/LCD/LCD.h>
#include <Service/SCHEDULER/SCHED.h>
#include <HAL/LED/LED.h>
void LCD_Write()
{
    static uint8_t counter = 0;
    if(counter == 0)
    {
        LCD_ClearAsynch();
        LCD_WriteStringAsynch("ahmed", 1, 1);
        counter++;
    }
    
}


int main()
{
    LED_init();
    LCD_initAsynch();   
    SCHED_Init();
    SCHED_Start();
    return 0;
}
