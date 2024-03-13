#ifndef _SYSTICK_H
#define _SYSTICK_H
/********************************************************Includes:************************************************/
#include <ErrorStatus.h>
#include <stdint.h>

/********************************************************Defines:*************************************************/
#define SYSTICK_CLOCK_AHB                       0x00000000
#define SYSTICK_CLOCK_AHB_DIV8                  0x00000004
#define SYSTICK_IQR_ENABLE                      0x00000002
#define SYSTICK_IQR_DISABLE                     0x00000000

#define SYSTICK_CLOCK_VALUE                     16000000UL

/********************************************************Types:***************************************************/
typedef void (*SYSTICK_CBF_t)(void);  // Define a function pointer type for SysTick callback function

/********************************************************APIs:****************************************************/

/**
 * @brief function to start the systick timer 
 * @return error status -0 means that function done successfully-
 */
ErrorStatus_t SYSTICK_StartTimer (void);

/**
 * @brief function to stop the systick timer 
 * @return error status -0 means that function done successfully-
 */
ErrorStatus_t SYSTICK_StopTimer (void);

/**
 * @brief function to configure the source of systick timer clock
 * @param SYSTICK_CLOCK -> SYSTICK_CLOCK_AHB, SYSTICK_CLOCK_AHB_DIV8
 * @return error status -0 means that function done successfully-
 */
ErrorStatus_t SYSTICK_ConfigureClock (uint32_t SYSTICK_CLOCK);

/**
 * @brief function to control IRQ of systick
 * @param SYSTICK_IQR->SYSTICK_IQR_ENABLE , SYSTICK_IQR_DISABLE.
 * @return error status -0 means that function done successfully-
 */
ErrorStatus_t SYSTICK_ControlIRQ (uint32_t SYSTICK_IQR);

/**
 * @brief function to set specific time in milli seconds using systick timer 
 * @param time in milli seconds 
 * @return error status -0 means that function done successfully-
 */
ErrorStatus_t SYSTICK_SetTime_ms(uint32_t Copy_timeMs);

/**
 * @brief function to assign the desired handler that handle systick IRQ 
 * @param pointer to function (handler)
 * @return error status -0 means that function done successfully-
 */
ErrorStatus_t SYSTICK_SetCallBack(SYSTICK_CBF_t CBF);

#endif
