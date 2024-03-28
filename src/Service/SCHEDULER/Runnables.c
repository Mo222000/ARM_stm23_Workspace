#include <Service/SCHEDULER/RUNNABLE.h>
#include <Service/SCHEDULER/SCHED.h>
/*---------------------------------------------------------------------------------------------------*/
/*                                           Extern Prototypes                                       */
/*---------------------------------------------------------------------------------------------------*/
extern void BlinkingLed(void);

/*---------------------------------------------------------------------------------------------------*/
/*                                           Runnables List                                          */
/*---------------------------------------------------------------------------------------------------*/
const Runnable_t Runnables_Arr [_RunnableNumber]=
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
        .Periodicity = 10000,
        .CB = &BlinkingLed,
    }
    
};