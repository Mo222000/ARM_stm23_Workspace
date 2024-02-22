#ifndef LED
#define LED
#include <stdint.h>
#include <ErrorStatus.h>
#include <HAL/LED/LED_CNFG.h>

/*************************************************************DEFINES:***************************************************************/
/* LED connection options:*/
#define LED_CONNECTION_FORWARD                  0
#define LED_CONNECTION_REVERSE                  1

/*LED status options:*/
#define LED_STATE_ON                            1
#define LED_STATE_OFF                           0

/*************************************************************NEW TYPES:*************************************************************/
typedef struct
{
    void* port;
    uint32_t pin;
    uint8_t connectionType;
}LED_CNFG_t;

/*************************************************************APIs:******************************************************************/
/**
*@brief  : call this function to initalize all LED you defined, Insure that you configure your led in LED_CNFG.h and LED_CNFG.c files well.
*@param  : no thing.
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t LED_init(void);

/**
*@brief  : function to set specific led state. please insure first you defined this led in LED_CNFG.h and LED_CNFG.c files and call init function first.
*@param  : LedName, state.
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t LED_setstatus(uint32_t led, uint8_t status);

#endif
