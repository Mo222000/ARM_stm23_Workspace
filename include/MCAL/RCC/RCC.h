#ifndef RCC_H
#define RCC_H
#include <stdint.h>
#include <ErrorStatus.h>
/****************************************************************************************************/
/*******************************************Defines:*************************************************/
/****************************************************************************************************/
#define RCC_ClkHSION        			0x00000001  // HSI clock enable
#define RCC_ClkHSEON_NOTBYPASS       	0x00010000  // HSE clock enable oscillator not bypassed
#define RCC_ClkHSEON_BYPASS   	  		0x00050000  // HSE clock enable bypassed with an external clock
#define RCC_ClkPLLON   	     			0x01000000  // PLL enable

#define RCC_SYSCLK_HSI					0x00000000 	//system clock switch to HSI
#define RCC_SYSCLK_HSE 					0x00000001	//system clock switch to HSE
#define RCC_SYSCLK_PLL					0x00000002  // System clock switch to PLL

/*select source clock of PLL*/
#define RCC_PLLSRC_HSI             		0x00000000 	// PLLSRC = HSI oscillator clock
#define RCC_PLLSRC_HSE            		0x00400000 	// PLLSRC = HSE oscillator clock

/*peripheral enable Masks*/
#define RCC_PERI_AHB1ENR_GPIOA       	0x00000001U  // IO port A clock enable
#define RCC_PERI_AHB1ENR_GPIOB       	0x00000002U  // IO port B clock enable
#define RCC_PERI_AHB1ENR_GPIOC       	0x00000004U  // IO port C clock enable
#define RCC_PERI_AHB1ENR_GPIOD       	0x00000008U  // IO port D clock enable
#define RCC_PERI_AHB1ENR_GPIOE       	0x00000010U  // IO port E clock enable
#define RCC_PERI_AHB1ENR_CRC         	0x00001000U  // CRC clock enable
#define RCC_PERI_AHB1ENR_DMA1        	0x00200000U  // DMA1 clock enable
#define RCC_PERI_AHB1ENR_DMA2        	0x00400000U  // DMA2 clock enable
#define RCC_PERI_AHB2ENR_OTGFS      	0x00000080U  // USB OTG FS clock enable
#define RCC_PERI_APB1ENR_TIM2        	0x00000001U  // Timer 2 clock enable
#define RCC_PERI_APB1ENR_TIM3        	0x00000002U  // Timer 3 clock enable
#define RCC_PERI_APB1ENR_TIM4        	0x00000004U  // Timer 4 clock enable
#define RCC_PERI_APB1ENR_TIM5        	0x00000008U  // Timer 5 clock enable
#define RCC_PERI_APB1ENR_WWDG        	0x00000800U  // Window watchdog clock enable
#define RCC_PERI_APB1ENR_SPI2        	0x00004000U  // SPI 2 clock enable
#define RCC_PERI_APB1ENR_SPI3        	0x00008000U  // SPI 3 clock enable
#define RCC_PERI_APB1ENR_USART2      	0x00020000U  // USART 2 clock enable
#define RCC_PERI_APB1ENR_I2C1        	0x00200000U  // I2C 1 clock enable
#define RCC_PERI_APB1ENR_I2C2        	0x00400000U  // I2C 2 clock enable
#define RCC_PERI_APB1ENR_I2C3        	0x00800000U  // I2C 3 clock enable
#define RCC_PERI_APB1ENR_PWR         	0x10000000U  // Power interface clock enable
#define RCC_PERI_APB2ENR_TIM1       	0x00000001U  // Timer 1 clock enable
#define RCC_PERI_APB2ENR_USART1     	0x00000010U  // USART 1 clock enable
#define RCC_PERI_APB2ENR_USART6     	0x00000020U  // USART 6 clock enable
#define RCC_PERI_APB2ENR_ADC1       	0x00000100U  // ADC1 clock enable
#define RCC_PERI_APB2ENR_SDIO       	0x00000800U  // SDIO clock enable
#define RCC_PERI_APB2ENR_SPI1       	0x00001000U  // SPI 1 clock enable
#define RCC_PERI_APB2ENR_SPI4       	0x00002000U  // SPI 4 clock enable
#define RCC_PERI_APB2ENR_SYSCFG     	0x00004000U  // System configuration controller clock enable
#define RCC_PERI_APB2ENR_TIM9       	0x00010000U  // Timer 9 clock enable
#define RCC_PERI_APB2ENR_TIM10      	0x00020000U  // Timer 10 clock enable
#define RCC_PERI_APB2ENR_TIM11      	0x00040000U  // Timer 11 clock enable

/****************************************************************************************************/
/*******************************************Types:***************************************************/
/****************************************************************************************************/

typedef enum
{
	RCC_ok =0,
	RCC_NotOk
}RCC_enumErrorStatus_t;

typedef enum
{
	Status_Disable=0,
	Status_Enable
}RCC_enumStatus_t;

/****************************************************************************************************/
/*******************************************APIs:****************************************************/
/****************************************************************************************************/
/**
*@brief  : function to control any clock. Before calling this Function, You MUST be sure the selected clock is not the system clock.
*@param  : Type(Name)of clock, status of clock
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t RCC_ControlClock (uint32_t clock, RCC_enumStatus_t Status);

/**
*@brief  : function to configure the PLL Clock. Before calling this Function, You MUST be sure PLL is not the system clock 
			and the pll source selected is on and ready. 
*@param  : source of PLL, M , N, p, q
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t RCC_ConfigurePLL (uint32_t RCC_PLLSRC, uint32_t Copy_M, uint32_t Copy_N, uint32_t copy_p, uint32_t copy_q);


/**
*@brief  : function to Select System Clock. Before calling this Function, You MUST be sure the selected clock is enabled and have their time to be ready
*@param  : System Clock
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t RCC_SelectSystemClock(uint32_t SysClk);


/**
*@brief  : function to control on any clock
*@param  : ClockName, status
*@return : Error state -return 0 means that function done successfully-
*@Notice : Before calling this Function, You MUST be sure the selected clock is not the system clock
*/
ErrorStatus_t RCC_ControlPeripheral(uint32_t Peripheral, RCC_enumStatus_t Status);


/**
*@brief  : function to control on any clock
*@param  : ClockName, status
*@return : Error state -return 0 means that function done successfully-
*@Notice : Before calling this Function, You MUST be sure the selected clock is not the system clock
*/
ErrorStatus_t RCC_ConfigurePreScaler(uint32_t Bus, uint32_t PreScaler);

#endif
