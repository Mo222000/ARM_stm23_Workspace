#ifndef GPIO
#define GPIO
/**************************************************************Includes:******************************************************************/
#include <stdint.h>
#include <ErrorStatus.h>
/**************************************************************Defines:*******************************************************************/
/*Ports options:*/
#define GPIO_PORTA              (void*) 0x40020000 
#define GPIO_PORTB              (void*) 0x40020400
#define GPIO_PORTC              (void*) 0x40020800

/*Pins options:*/
#define GPIO_PIN0               0x00000000
#define GPIO_PIN1               0x00000001
#define GPIO_PIN2               0x00000002
#define GPIO_PIN3               0x00000003
#define GPIO_PIN4               0x00000004
#define GPIO_PIN5               0x00000005
#define GPIO_PIN6               0x00000006
#define GPIO_PIN7               0x00000007
#define GPIO_PIN8               0x00000008
#define GPIO_PIN9               0x00000009
#define GPIO_PIN10              0x0000000A
#define GPIO_PIN11              0x0000000B
#define GPIO_PIN12              0x0000000C
#define GPIO_PIN13              0x0000000D
#define GPIO_PIN14              0x0000000E
#define GPIO_PIN15              0x0000000F

/*Pin Mode Options:*/
#define GPIO_MODE_IN_FL 	    0x00000000
#define GPIO_MODE_IN_PU 	    0x00000008
#define GPIO_MODE_IN_PD 	    0x00000010

#define GPIO_MODE_OUT_PP   	    0x00000001
#define GPIO_MODE_OUT_PP_PU	    0x00000009
#define GPIO_MODE_OUT_PP_PD	    0x00000011
#define GPIO_MODE_OUT_OD   	    0x00000005
#define GPIO_MODE_OUT_OD_PU	    0x0000000D
#define GPIO_MODE_OUT_OD_PD	    0x00000015

#define GPIO_MODE_AF_PP    	    0x00000002
#define GPIO_MODE_AF_PP_PU 	    0x0000000A
#define GPIO_MODE_AF_PP_PD 	    0x00000012
#define GPIO_MODE_AF_OD    	    0x00000006
#define GPIO_MODE_AF_OD_PU 	    0x0000000E
#define GPIO_MODE_AF_OD_PD 	    0x00000016

#define GPIO_MODE_AN       	    0x00000003

/*Pin Speed Options:*/
#define GPIO_SPEED_LOW     	    0x00000000
#define GPIO_SPEED_MED     	    0x00000001
#define GPIO_SPEED_HIGH    	    0x00000002
#define GPIO_SPEED_VHIGH   	    0x00000003

/*Pin State Options:*/
#define GPIO_STATE_HIGH         0x00000001
#define GPIO_STATE_LOW          0x00000000

/**************************************************************Typedefs:******************************************************************/
typedef struct
{
    void*       port;
    uint32_t    pin;
    uint32_t    speed;
    uint32_t    mode;
}GPIO_PIN_t;

/**************************************************************APIs:**********************************************************************/
/**
*@brief  : function to set the configuration of GPIO pin.
*@param  : pointer of GPIO_PIN_t struct, Which contain the Port, Pin Number, Speed, Mode of the selected pin. 
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t GPIO_Init(GPIO_PIN_t* Copy_PinStruct);

/**
*@brief  : function to set the value of GPIO pin.
*@param  : Port, Pin, state. 
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t GPIO_SetPinValue(void* Copy_port, uint32_t Copy_Pin, uint32_t Copy_state);

/**
*@brief  : function to get the value of GPIO pin.
*@param  : Port, Pin. 
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t GPIO_GetPinValue(void* Copy_port, uint32_t Copy_Pin, uint8_t* Copy_PinState);


#endif