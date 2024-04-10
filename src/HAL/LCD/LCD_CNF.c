/*******************************************************Includes: *****************************************/
#include <HAL/LCD/LCD.h>
#include <HAL/LCD/LCD_CNF.h>
/*******************************************************Pins struct:***************************************/
LCD_PinConfig LCD_Config[LCD_MODE]=
{
    [D0]    = {.port = GPIO_PORTA,     .pin = GPIO_PIN0},
    [D1]    = {.port = GPIO_PORTA,     .pin = GPIO_PIN1},
    [D2]    = {.port = GPIO_PORTA,     .pin = GPIO_PIN2},
    [D3]    = {.port = GPIO_PORTA,     .pin = GPIO_PIN3},

    #if LCD_MODE == LCD_8_BIT_MODE
    [D4]    = {.port = GPIO_PORTA,     .pin = GPIO_PIN4},
    [D5]    = {.port = GPIO_PORTA,     .pin = GPIO_PIN5},
    [D6]    = {.port = GPIO_PORTA,     .pin = GPIO_PIN6},
    [D7]    = {.port = GPIO_PORTA,     .pin = GPIO_PIN7},
    #endif
    
    [RW]    = {.port = GPIO_PORTA,     .pin = GPIO_PIN8},
    [RS]    = {.port = GPIO_PORTA,     .pin = GPIO_PIN9},
    [E]     = {.port = GPIO_PORTA,     .pin = GPIO_PIN10},
};