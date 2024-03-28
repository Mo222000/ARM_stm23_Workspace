/*---------------------------------------------------------------------------------------------------*/
/*                                           Includes:                                               */
/*---------------------------------------------------------------------------------------------------*/
#include <MCAL/SYSTICK/SYSTICK.h>
#include <Service/SCHEDULER/RUNNABLE.h>
#include <Service/SCHEDULER/SCHED.h>

/*---------------------------------------------------------------------------------------------------*/
/*                                           Variables:                                              */
/*---------------------------------------------------------------------------------------------------*/
static volatile uint32_t SCHED_PendingTicks = 1 ;

/*---------------------------------------------------------------------------------------------------*/
/*                                           Extern:                                                 */
/*---------------------------------------------------------------------------------------------------*/
extern const Runnable_t Runnables_Arr [_RunnableNumber];

/*---------------------------------------------------------------------------------------------------*/
/*                                           Static Function:                                        */
/*---------------------------------------------------------------------------------------------------*/
static void TickIncrement (void)
{
    SCHED_PendingTicks++;
}

static void SCHED (void)
{
    static uint32_t Current_Runnable = 0;
    static uint32_t TimeStampMs = 0;
    for(Current_Runnable =0 ; Current_Runnable < _RunnableNumber ; Current_Runnable++)
    {
        /**check if the delay time is passed and call back function is set*/
        if((Runnables_Arr[Current_Runnable].CB) && (TimeStampMs % Runnables_Arr[Current_Runnable].Periodicity == 0))
        {
            Runnables_Arr[Current_Runnable].CB();
        }
    }
    /* increment the time stamp variable by the value of tick time */
    TimeStampMs += SCHED_TICK_TIME;
}

/*---------------------------------------------------------------------------------------------------*/
/*                                           APIs:                                                   */
/*---------------------------------------------------------------------------------------------------*/

/**
 * @brief Call this function at the start to initialize the scheduler.
 * @param NoThing
 * @return NoThing 
 */
void SCHED_Init (void)
{
    SYSTICK_SetTime_ms(SCHED_TICK_TIME);
    SYSTICK_SetCallBack(TickIncrement);
    SYSTICK_ControlIRQ(SYSTICK_IQR_ENABLE);
    SYSTICK_ConfigureClock(SYSTICK_CLOCK_AHB);
}

/**
 * @brief this function to start the schedular after initialize it.
 * @param NoThing
 * @return NoThing 
 */
void SCHED_Start (void)
{
    SYSTICK_StartTimer();
    while (1)
    {
        if(SCHED_PendingTicks)
        {
            SCHED_PendingTicks--;
            SCHED();
        }
    }
    
}
