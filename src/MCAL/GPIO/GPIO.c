#include <MCAL/GPIO/GPIO.h>
/************************************************Defines:***************************************************************/
#define GPIO_MODER_MASK             0x00000003  //Mask for 2 bits represent the 2 bits of Moder value 
#define GPIO_OTYPER_MASK            0x00000004  //Mask For 1 bit represent the output Mode 
#define GPIO_PUPD_MASK              0x00000018
#define GPIO_CLR_MASK               0x00000003

#define GPIO_OTYPER_SHIFT           0x00000002
#define GPIO_PUPD_SHIFT             0x00000003

#define GPIO_1BIT_REGISTER          0x00000001
#define GPIO_2BIT_REGISTER          0x00000002
#define GPIO_4BIT_REGISTER          0x00000004

#define GPIO_HALF_WORD_SIZE         16

/************************************************GPIO Registers Struct:*************************************************/
typedef struct {
    volatile uint32_t MODER;        // GPIO port mode register
    volatile uint32_t OTYPER;       // GPIO port output type register
    volatile uint32_t OSPEEDR;      // GPIO port output speed register
    volatile uint32_t PUPDR;        // GPIO port pull-up/pull-down register
    volatile uint32_t IDR;          // GPIO port input data register
    volatile uint32_t ODR;          // GPIO port output data register
    volatile uint32_t BSRR;         // GPIO port bit set/reset register
    volatile uint32_t LCKR;         // GPIO port configuration lock register
    volatile uint32_t AFRL;         // GPIO alternate function registers AFR[0]
    volatile uint32_t AFRH;         // GPIO alternate function registers AFR[1]
} GPIO_t;

/************************************************APIs:******************************************************************/
/**
*@brief  : function to set the configuration of GPIO pin.
*@param  : pointer of GPIO_PIN_t struct, Which contain the Port, Pin Number, Speed, Mode of the selected pin. 
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t GPIO_Init(GPIO_PIN_t* Copy_PinStruct)
{
    ErrorStatus_t Loc_Return= Ok;
    if(Copy_PinStruct == NULL)
    {
        Loc_Return = NullPointerError;
    }
    else if((Copy_PinStruct->pin > GPIO_PIN15)||(Copy_PinStruct->pin < GPIO_PIN0))
    {
        Loc_Return = ArgumentError;
    }
    else if (
        (Copy_PinStruct->mode != GPIO_MODE_IN_FL) &&
        (Copy_PinStruct->mode != GPIO_MODE_IN_PU) &&
        (Copy_PinStruct->mode != GPIO_MODE_IN_PD) &&
        (Copy_PinStruct->mode != GPIO_MODE_OUT_PP) &&
        (Copy_PinStruct->mode != GPIO_MODE_OUT_PP_PU) &&
        (Copy_PinStruct->mode != GPIO_MODE_OUT_PP_PD) &&
        (Copy_PinStruct->mode != GPIO_MODE_OUT_OD) &&
        (Copy_PinStruct->mode != GPIO_MODE_OUT_OD_PU) &&
        (Copy_PinStruct->mode != GPIO_MODE_OUT_OD_PD) &&
        (Copy_PinStruct->mode != GPIO_MODE_AF_PP) &&
        (Copy_PinStruct->mode != GPIO_MODE_AF_PP_PU) &&
        (Copy_PinStruct->mode != GPIO_MODE_AF_PP_PD) &&
        (Copy_PinStruct->mode != GPIO_MODE_AF_OD) &&
        (Copy_PinStruct->mode != GPIO_MODE_AF_OD_PU) &&
        (Copy_PinStruct->mode != GPIO_MODE_AF_OD_PD) &&
        (Copy_PinStruct->mode != GPIO_MODE_AN)
    ) {
        Loc_Return = ArgumentError;
    }
    else if((Copy_PinStruct->port != GPIO_PORTA)&&
            (Copy_PinStruct->port != GPIO_PORTB)&&
            (Copy_PinStruct->port != GPIO_PORTC)
    )
    {
        Loc_Return = ArgumentError;
    }
    else if ((Copy_PinStruct->speed > GPIO_SPEED_VHIGH)||(Copy_PinStruct->speed <GPIO_SPEED_LOW))
    {
        Loc_Return = ArgumentError;
    }
    else
    {
        uint32_t Loc_MODER   = ((GPIO_t*)Copy_PinStruct->port)->MODER;
        uint32_t Loc_OSPEEDR = ((GPIO_t*)Copy_PinStruct->port)->OSPEEDR;
        uint32_t Loc_PUPDR   = ((GPIO_t*)Copy_PinStruct->port)->PUPDR;
        
        /*configure Mode*/
        Loc_MODER &= ~(GPIO_CLR_MASK << (GPIO_2BIT_REGISTER*(Copy_PinStruct->pin)));  //shifting by 2*(PinNumber)
        Loc_MODER |= (Copy_PinStruct->mode & GPIO_MODER_MASK) << (GPIO_2BIT_REGISTER*(Copy_PinStruct->pin));
        ((GPIO_t*)Copy_PinStruct->port)->MODER = Loc_MODER;

        /*configure OTYPER*/
        ((GPIO_t*)Copy_PinStruct->port)->OTYPER |= ((Copy_PinStruct->mode & GPIO_OTYPER_MASK)>>GPIO_OTYPER_SHIFT) << (GPIO_1BIT_REGISTER*(Copy_PinStruct->pin));

        /*configure PUPDR*/
        Loc_PUPDR &= ~(GPIO_CLR_MASK << (GPIO_2BIT_REGISTER*(Copy_PinStruct->pin)));
        Loc_PUPDR |= ((Copy_PinStruct->mode & GPIO_PUPD_MASK)>>GPIO_PUPD_SHIFT) << (GPIO_2BIT_REGISTER*(Copy_PinStruct->pin));
        ((GPIO_t*)Copy_PinStruct->port)->PUPDR = Loc_PUPDR;

        /*configure speed*/
        Loc_OSPEEDR &= ~(GPIO_CLR_MASK << (GPIO_2BIT_REGISTER*(Copy_PinStruct->pin)));
        Loc_OSPEEDR |= (Copy_PinStruct->speed << (GPIO_2BIT_REGISTER*(Copy_PinStruct->pin)));
        ((GPIO_t*)Copy_PinStruct->port)->OSPEEDR = Loc_OSPEEDR;

        Loc_Return = Ok;
    }
    return Loc_Return;
}

/**
*@brief  : function to set the value of GPIO pin.
*@param  : Port, Pin, state. 
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t GPIO_SetPinValue(void* Copy_port, uint32_t Copy_Pin, uint32_t Copy_state)
{
    ErrorStatus_t Loc_Return = NotOk;
    if((Copy_port != GPIO_PORTA ) && (Copy_port != GPIO_PORTB) && (Copy_port != GPIO_PORTC))
    {
        Loc_Return = ArgumentError;
    }
    else if ((Copy_Pin < GPIO_PIN0)||(Copy_Pin > GPIO_PIN15))
    {
        Loc_Return = ArgumentError;
    }
    /*else if ((Copy_state != GPIO_SPEED_HIGH) && (Copy_state != GPIO_STATE_LOW))
    {
        Loc_Return = ArgumentError;
    }*/
    else
    {
        Loc_Return = Ok;
        switch (Copy_state)
        {
        case GPIO_STATE_HIGH:
            ((GPIO_t*)Copy_port)->BSRR |= 1 << Copy_Pin;    
        break;
        
        case GPIO_STATE_LOW:
            ((GPIO_t*)Copy_port)->BSRR |= 1 << (Copy_Pin + GPIO_HALF_WORD_SIZE);
        break;
        
        default:
            /*do nothing*/
        break;
        }
    }
    return Loc_Return;    
}

/**
*@brief  : function to get the value of GPIO pin.
*@param  : Port, Pin. 
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t GPIO_GetPinValue(void* Copy_port, uint32_t Copy_Pin, uint8_t* Copy_PinState)
{
    ErrorStatus_t Loc_Return = NotOk;
    if((Copy_port != GPIO_PORTA ) && (Copy_port != GPIO_PORTB) &&(Copy_port != GPIO_PORTC))
    {
        Loc_Return = ArgumentError;
    }
    else if ((Copy_Pin < GPIO_PIN0)||(Copy_Pin > GPIO_PIN15))
    {
        Loc_Return = ArgumentError;
    }
    else
    {
        Loc_Return = Ok;
        *Copy_PinState = (((GPIO_t*)Copy_port)->IDR >> Copy_Pin) & 1;
    }
    return Loc_Return;
}

