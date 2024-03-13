#ifndef SWITCH_H
#define SWITCH_H

#include <stdint.h>
#include <ErrorStatus.h>
#include <HAL/SWITCH/SWITCH_CNFG.h>
/*************************************************************DEFINES:***************************************************************/
/* LED connection options:*/
#define SWITCH_CONNECTION_PULLUP            0x00000008
#define SWITCH_CONNECTION_PULLDOWN          0x00000010

/*LED status options:*/
#define SWITCH_PRESSED                      1
#define SWITCH_NOTPRESSED                   0

/*************************************************************NEW TYPES:*************************************************************/
typedef struct
{
    void* port;
    uint32_t pin;
    uint8_t connectionType;
}SWITCH_CNFG_t;

/*************************************************************APIs:******************************************************************/
/**
*@brief  : call this function to initalize all switches you defined, Insure that you configure your switches in SWITCH_CNFG.h and SWITCH_CNFG.c files well.
*@param  : no thing.
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t SWITCH_init(void);

/**
*@brief  : function to set specific SWITCH state. please insure first you defined this SWITCH in SWITCH_CNFG.h and SWITCH_CNFG.c files and call init function first.
*@param  : SwitchName, state.
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t SWITCH_GetStatus(uint32_t copy_switch, uint8_t* copy_status);
#endif
