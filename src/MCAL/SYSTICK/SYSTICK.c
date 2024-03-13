/********************************************************Includes:*********************************************************/
#include <MCAL/SYSTICK/SYSTICK.h>

/********************************************************Defines:**********************************************************/

#define SYSTICK_BASE_ADDRESS        0xE000E010
#define SYSTICK_ENABLE              0x00000001

#define MAXIMUM_LOAD_VALUE          0x00FFFFFF
#define SYSTCIK_COUNT_FLAG          0x00010000
/********************************************************Types:************************************************************/

typedef struct 
{
    volatile uint32_t CTRL;             /* control and status register*/ 
    volatile uint32_t LOAD;             /* reload value register*/
    volatile uint32_t VAL;              /* current value register*/
    volatile uint32_t CALIB;            /* callibration value register*/
}SYSTICK_Type;

/********************************************************Variables: *******************************************************/
SYSTICK_Type *const SYSTICK = (SYSTICK_Type*) SYSTICK_BASE_ADDRESS;  

/* flag to source clock of systick will be 0 if clock source divied by 8 and 1 if it not divided */
uint8_t Global_ClockSourceFlag = 3;

SYSTICK_CBF_t Current_CBF;

/********************************************************APIs:*************************************************************/

/**
 * @brief function to start the systick timer 
 * @return error status -0 means that function done successfully-
 */
ErrorStatus_t SYSTICK_StartTimer (void)
{
    ErrorStatus_t Loc_Return = Ok;
    SYSTICK->CTRL |= SYSTICK_ENABLE;
    return Loc_Return;
}

/**
 * @brief function to stop the systick timer 
 * @return error status -0 means that function done successfully-
 */
ErrorStatus_t SYSTICK_StopTimer (void)
{
    ErrorStatus_t Loc_Return = Ok;
    SYSTICK->CTRL &= ~(SYSTICK_ENABLE);
    return Loc_Return;
}

/**
 * @brief function to configure the source of systick timer clock
 * @param SYSTICK_CLOCK -> SYSTICK_CLOCK_AHB, SYSTICK_CLOCK_AHB_DIV8
 * @return error status -0 means that function done successfully-
 */
ErrorStatus_t SYSTICK_ConfigureClock (uint32_t SYSTICK_CLOCK)
{
    ErrorStatus_t Loc_Return = Ok;
    if((SYSTICK_CLOCK != SYSTICK_CLOCK_AHB_DIV8) && (SYSTICK_CLOCK != SYSTICK_CLOCK_AHB))
    {
        Loc_Return = ArgumentError;
    }
    else
    {
        Loc_Return = Ok;
        uint32_t Loc_Reg = SYSTICK->CTRL;

        
        Loc_Reg &= ~(SYSTICK_CLOCK_AHB);                                //clear bit at first                        
        Loc_Reg |= SYSTICK_CLOCK;
        SYSTICK->CTRL = Loc_Reg;
    }
    return Loc_Return;
}

/**
 * @brief function to control IRQ of systick
 * @param SYSTICK_IQR->SYSTICK_IQR_ENABLE , SYSTICK_IQR_DISABLE.
 * @return error status -0 means that function done successfully-
 */
ErrorStatus_t SYSTICK_ControlIRQ (uint32_t SYSTICK_IQR)
{
    ErrorStatus_t Loc_Return = Ok;
    if ((SYSTICK_IQR != SYSTICK_IQR_DISABLE) && (SYSTICK_IQR != SYSTICK_IQR_ENABLE))
    {
        Loc_Return = ArgumentError;
    }
    else
    {
        Global_ClockSourceFlag = SYSTICK_IQR >> 2;
        uint32_t Loc_Reg = SYSTICK->CTRL;


        Loc_Reg &= ~(SYSTICK_IQR_DISABLE);
        Loc_Reg |= SYSTICK_IQR;
        SYSTICK->CTRL = Loc_Reg;
    }
    return Loc_Return;
}

/**
 * @brief function to set specific time in milli seconds using systick timer 
 * @param time in milli seconds 
 * @return error status -0 means that function done successfully-
 */
ErrorStatus_t SYSTICK_SetTime_ms(uint32_t Copy_timeMs)
{
    ErrorStatus_t Loc_Return = Ok;
    uint32_t Load_Value = 0xFFFFFFFF;

    /*Calculate load value if clock source is divided by 8 */
    if(Global_ClockSourceFlag)
    {
        Load_Value = ((Copy_timeMs * (SYSTICK_CLOCK_VALUE/8))/1000) - 1;
    }
    else
    {
        Load_Value = ((Copy_timeMs * SYSTICK_CLOCK_VALUE)/1000) - 1;
    }


    if(Load_Value > MAXIMUM_LOAD_VALUE)
    {
        Loc_Return = ArgumentError;
    }
    else
    {
        SYSTICK->LOAD = Load_Value;
        Loc_Return = Ok;
    }
    
    return Loc_Return;
}

/**
 * @brief function to assign the desired handler that handle systick IRQ 
 * @param pointer to function (handler)
 * @return error status -0 means that function done successfully-
 */
ErrorStatus_t SYSTICK_SetCallBack(SYSTICK_CBF_t CBF)
{
    ErrorStatus_t Loc_return = Ok;
    if(CBF == NULL)
    {
        Loc_return = NullPointerError;
    }
    else
    {
        Current_CBF = CBF;
        Loc_return = Ok;
    }
    return Loc_return;
}

void SysTick_Handler (void)
{
    if(Current_CBF)
    {
        Current_CBF();
    }   
}