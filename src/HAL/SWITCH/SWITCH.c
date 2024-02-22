/*****************************************************************INCLUDES:**************************************************/
#include <MCAL/GPIO/GPIO.h>
#include <HAL/SWITCH/SWITCH.h>
#include <MCAL/RCC/RCC.h>

/*****************************************************************VARIABLES:*************************************************/
extern SWITCH_CNFG_t SWITCH[_SWITCH_NUMBER];

/*****************************************************************APIS:**************************************************/
/**
*@brief  : call this function to initalize all switches you defined, Insure that you configure your switches in SWITCH_CNFG.h and SWITCH_CNFG.c files well.
*@param  : no thing.
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t SWITCH_init(void)
{
    ErrorStatus_t Loc_Return = Ok;

    Loc_Return = RCC_Control_AHB1Peripherals(RCC_PERI_AHB1ENR_GPIOA, Status_Enable);
    Loc_Return = RCC_Control_AHB1Peripherals(RCC_PERI_AHB1ENR_GPIOB, Status_Enable);
    Loc_Return = RCC_Control_AHB1Peripherals(RCC_PERI_AHB1ENR_GPIOC, Status_Enable);

    GPIO_PIN_t SWITCH_struct;
    for (uint8_t itr = 0; itr < _SWITCH_NUMBER; itr++)
    {
        SWITCH_struct.pin = SWITCH[itr].pin;
        SWITCH_struct.port = SWITCH[itr].port;
        SWITCH_struct.mode = SWITCH[itr].connectionType;

        Loc_Return= GPIO_Init(&SWITCH_struct);       
    }
    return Loc_Return;
}

/**
*@brief  : function to set specific SWITCH state. please insure first you defined this SWITCH in SWITCH_CNFG.h and SWITCH_CNFG.c files and call init function first.
*@param  : SwitchName, state.
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t SWITCH_GetStatus(uint32_t copy_switch, uint8_t* copy_status)
{
    ErrorStatus_t Loc_Return = Ok;
    uint8_t Loc_status;
    if (copy_switch > _SWITCH_NUMBER)
    {
        Loc_Return = ArgumentError;
    }
    else if (copy_status ==  NULL)
    {
        Loc_Return = NullPointerError;
    }
    else
    {
        Loc_Return = Ok;
        Loc_Return = GPIO_GetPinValue(SWITCH[copy_switch].port,SWITCH[copy_switch].pin,&Loc_status);
        *copy_status = !(Loc_status ^ (SWITCH[copy_switch].connectionType >> 4)); 
    }
    return Loc_Return;
}