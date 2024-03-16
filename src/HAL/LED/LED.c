/*****************************************************************INCLUDES:**************************************************/
#include <MCAL/GPIO/GPIO.h>
#include <HAL/LED/LED.h>
#include <MCAL/RCC/RCC.h>

/*****************************************************************VARIABLES:*************************************************/
extern LED_CNFG_t Led[_LED_NUMBER];

/*****************************************************************APIS:**************************************************/
/**
*@brief  : call this function to initalize all LED you defined, Insure that you configure your led in LED_CNFG.h and LED_CNFG.c files well.
*@param  : no thing.
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t LED_init(void)
{
    ErrorStatus_t Loc_Return = Ok;

    Loc_Return = RCC_Control_AHB1Peripherals(RCC_PERI_AHB1ENR_GPIOA, Status_Enable);
    Loc_Return = RCC_Control_AHB1Peripherals(RCC_PERI_AHB1ENR_GPIOB, Status_Enable);
    Loc_Return = RCC_Control_AHB1Peripherals(RCC_PERI_AHB1ENR_GPIOC, Status_Enable);

    GPIO_PIN_t LED_struct;
    
    for (uint8_t itr = 0; itr < _LED_NUMBER; itr++)
    {
        LED_struct.pin = Led[itr].pin;
        LED_struct.port = Led[itr].port;
        LED_struct.mode = GPIO_MODE_OUT_PP;
        LED_struct.speed = GPIO_SPEED_HIGH;
        Loc_Return= GPIO_Init(&LED_struct);       
    }

    return Loc_Return;
}

/**
*@brief  : function to set specific led state. please insure first you defined this led in LED_CNFG.h and LED_CNFG.c files and call init function first.
*@param  : LedName, state.
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t LED_setstatus(uint32_t copy_led, uint8_t copy_status)
{
    ErrorStatus_t Loc_Return = Ok;
    if (copy_led > _LED_NUMBER)
    {
        Loc_Return = ArgumentError;
    }
    else if ( (copy_status != LED_STATE_OFF) && (copy_status != LED_STATE_ON) )
    {
        Loc_Return = ArgumentError;
    }
    else
    {
        GPIO_SetPinValue(Led[copy_led].port, Led[copy_led].pin, (Led[copy_led].connectionType^copy_status));
    }
    return Loc_Return;
}

/**
*@brief  : function to toggle specific led state. please insure first you defined this led in LED_CNFG.h and LED_CNFG.c files and call init function first.
*@param  : LedName
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t LED_Toggle(uint32_t copy_led)
{
    ErrorStatus_t Loc_Return = Ok;
    if(copy_led > _LED_NUMBER)
    {
        Loc_Return = ArgumentError;
    }
    else
    {
        uint8_t state;
        GPIO_GetPinValue(Led[copy_led].port,Led[copy_led].pin, &state);
        if(state == LED_STATE_ON)
        {
            LED_setstatus(copy_led,LED_STATE_OFF);
        }
        else
        {
            LED_setstatus(copy_led,LED_STATE_ON);
        }
    }
    return Loc_Return;
}