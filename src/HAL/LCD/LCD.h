#ifndef _LCD_H
#define _LCD_H
/**********************************************************************************************************/
/*******************************************************Includes: *****************************************/
/**********************************************************************************************************/
#include <stdint.h>
#include <LIB/ErrorStatus.h>
#include <HAL/LCD/LCD_CNF.h>
#include <MCAL/GPIO/GPIO.h>
/**********************************************************************************************************/
/*******************************************************Defines: ******************************************/
/**********************************************************************************************************/
#define LCD_4_BIT_MODE              7
#define LCD_8_BIT_MODE              11

/*DISPLAY STATE*/
#define DISPLAY_ON	1
#define DISLAY_OFF	0

/*CURSOR STATE*/
#define CURSOR_ON	1
#define CURSOR_OFF	0

/*CURSOR BLINKING*/
#define CURSOR_BLINKING		1
#define CURSOR_NOT_BLINKING 0

/* NUMBER OF LINES*/
#define ONE_LINE	0
#define TWO_LINES	1

/*FONT*/
#define SEVEN_DOTS		0
#define TEN_DOTS		1

/**********************************************************************************************************/
/*******************************************************typedefs:******************************************/
/**********************************************************************************************************/
typedef struct 
{
    void* port;
    uint32_t pin;
}LCD_PinConfig;
/**********************************************************************************************************/
/*******************************************************Enums: ********************************************/
/**********************************************************************************************************/
enum
{
    D0 = 0 ,
    D1,
    D2,
    D3,
    #if LCD_MODE == LCD_8_BIT_MODE 
    D4,
    D5,
    D6,
    D7,
    #endif
    RW,
    RS,
    E    
};
/**********************************************************************************************************/
/*******************************************************APIs:**********************************************/
/**********************************************************************************************************/

/**
 * @brief Initializes the GPIO pins for LCD interfacing.
 * 
 * This function initializes the GPIO pins required for interfacing with an LCD module.
 * It configures the GPIO pins based on the selected LCD mode (8-bit or 4-bit).
 * 
 * @return ErrorStatus_t Returns the status of the initialization process (Ok or Error).
 */
ErrorStatus_t LCD_initAsynch(void);


/**
 * @brief Writes a string asynchronously onto an LCD screen.
 * 
 * This function writes a string of characters onto an LCD screen asynchronously,
 * meaning it does not halt program execution while performing the operation.
 * 
 * @param string Pointer to the beginning of the string to be written.
 *               The string should be null-terminated ('\0').
 * @param copy_X_Position Horizontal position where the string will begin to be written.
 *                         X position typically ranges from 0 to the maximum width of the display.
 * @param copy_Y_position Vertical position where the string will begin to be written.
 *                         Y position typically ranges from 0 to the maximum height of the display.
 * @return ErrorStatus_t An enumeration indicating the success or failure of the operation.
 *                        Possible values include:
 *                        - SUCCESS: Operation completed successfully.
 *                        - ERROR: Operation encountered an error.
 * 
 * Example Usage:
 * 
 * uint8_t myString[] = "Hello, World!";
 * uint8_t xPosition = 0;
 * uint8_t yPosition = 0;
 * 
 * ErrorStatus_t status = LCD_WriteStringAsynch(myString, xPosition, yPosition);
 * 
 * if (status == ERROR) {
 *     // Handle error condition
 * } else {
 *     // String write operation successful
 * }
 */
ErrorStatus_t LCD_WriteStringAsynch(uint8_t* string, uint8_t copy_X_Position, uint8_t copy_Y_position);


/**
 * @brief Clears the content of the LCD asynchronously.
 * 
 * This function asynchronously clears the content displayed on the LCD screen. Asynchronous operation
 * means that the function does not block program execution while performing its task, allowing other
 * tasks to continue running concurrently.
 * 
 */
void LCD_ClearAsynch(void);

#endif