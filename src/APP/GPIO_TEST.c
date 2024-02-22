#include <MCAL/RCC/RCC.h>
#include <MCAL/GPIO/GPIO.h>


void GPIO_TEST ()
{
    GPIO_PIN_t LED;
    LED.mode = GPIO_MODE_OUT_PP;
    LED.pin = GPIO_PIN10;
    LED.port = GPIO_PORTA;
    LED.speed = GPIO_SPEED_HIGH;
    RCC_Control_AHB1Peripherals(RCC_PERI_AHB1ENR_GPIOA, Status_Enable);
    GPIO_Init(&LED);
    GPIO_SetPinValue(GPIO_PORTA,GPIO_PIN0,GPIO_STATE_HIGH);
    while (1)
    {

    }
    
}