#include <Service/SCHEDULER/RUNNABLE.h>
#include <Service/SCHEDULER/SCHED.h>
/*---------------------------------------------------------------------------------------------------*/
/*                                           Extern Prototypes                                       */
/*---------------------------------------------------------------------------------------------------*/
extern void BlinkingLed(void);
extern void LCD_Runnable(void);
extern void LCD_Write();
extern void BlinkingLed2(void);
extern void RUNNABLE_LCD(void);
/*---------------------------------------------------------------------------------------------------*/
/*                                           Runnables List                                          */
/*---------------------------------------------------------------------------------------------------*/
Runnable_t Runnables_Arr [_RunnableNumber]=
{
    /**
     * [Name]=
     * {    .Name = 
     *      .Periodicity= 
     *      .DelayMs =
     *      .CB = 
     * }
     */
    [BlinkingLed_Runnable]=
    {
        .Name = "Blinking Led For Test",
        .Periodicity = 1000,
        .CB = &BlinkingLed,
        .DelayMs = 1000,
    },

    /*[BlinkingLed_Runnable2]=
    {
        .Name = "Blinking Led 2",
        .Periodicity = 1000,
        .CB = &BlinkingLed2,
        .DelayMs = 1500,
    },*/

    [LCD_RUNNABLE]=
    {
        .Name = "Lcd_runnable",
        .Periodicity = 20,
        .CB = &LCD_Runnable,
    },

   [LCD_Writing_runnable]=
    {
        .Name = "write",
        .Periodicity = 10,
        .DelayMs = 1000,
        .CB = &LCD_Write,
    },
    
};