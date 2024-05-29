#include <MCAL/GPIO/GPIO.h>
#include <HAL/SWITCH/SWITCH.h>

/*In this file you will configure:
    1- switch pin options:
        GPIO_PIN[0:15]
    2- switch port options:
        GPIO_PORTA
        GPIO_PORTB
        GPIO_PORTC
    3- switch connection type optins:
        SWITCH_CONNECTION_PULLUP
        SWITCH_CONNECTION_PULLDOWN
*/

const SWITCH_CNFG_t SWITCH[_SWITCH_NUMBER]=
{
    /*fill it in that format 
	[Name_Of_Switch]={
		.port		=			,
		.pin		=			,
		.ConnectionType	=			,
	}*/

    [Test_Switch]=
    {
        .pin            = GPIO_PIN2,
        .port           = GPIO_PORTC,
        .connectionType = SWITCH_CONNECTION_PULLUP,
    }
};
