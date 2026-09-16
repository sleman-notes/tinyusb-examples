#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "stm32f4xx.h"

/*
 * Clock enable/disable and reset macros for GPIOx
 */

#define GPIOA_PCLK_EN()		(RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN)
#define GPIOB_PCLK_EN()		(RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN)
#define GPIOC_PCLK_EN()		(RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN)
#define GPIOD_PCLK_EN()		(RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN)
#define GPIOE_PCLK_EN()		(RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN)
#define GPIOH_PCLK_EN()		(RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN)

#define GPIOA_PCLK_DI()		(RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN)
#define GPIOB_PCLK_DI()		(RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN)
#define GPIOC_PCLK_DI()		(RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOCEN)
#define GPIOD_PCLK_DI()		(RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIODEN)
#define GPIOE_PCLK_DI()		(RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOEEN)
#define GPIOH_PCLK_DI()		(RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOHEN)

#define GPIOA_REG_RESET()	do{RCC->AHB1RSTR |= RCC_AHB1RSTR_GPIOARST; RCC->AHB1RSTR &= ~RCC_AHB1RSTR_GPIOARST;}while(0)
#define GPIOB_REG_RESET()	do{RCC->AHB1RSTR |= RCC_AHB1RSTR_GPIOBRST; RCC->AHB1RSTR &= ~RCC_AHB1RSTR_GPIOBRST;}while(0)
#define GPIOC_REG_RESET()	do{RCC->AHB1RSTR |= RCC_AHB1RSTR_GPIOCRST; RCC->AHB1RSTR &= ~RCC_AHB1RSTR_GPIOCRST;}while(0)
#define GPIOD_REG_RESET()	do{RCC->AHB1RSTR |= RCC_AHB1RSTR_GPIODRST; RCC->AHB1RSTR &= ~RCC_AHB1RSTR_GPIODRST;}while(0)
#define GPIOE_REG_RESET()	do{RCC->AHB1RSTR |= RCC_AHB1RSTR_GPIOERST; RCC->AHB1RSTR &= ~RCC_AHB1RSTR_GPIOERST;}while(0)
#define GPIOH_REG_RESET()	do{RCC->AHB1RSTR |= RCC_AHB1RSTR_GPIOHRST; RCC->AHB1RSTR &= ~RCC_AHB1RSTR_GPIOHRST;}while(0)

/* SYSCFG is needed to route the EXTI lines to a port */
#define SYSCFG_PCLK_EN()	(RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN)

/*
 *  Macro to give the code of a port
 */

#define GPIO_BASEADDR_TO_CODE(x)	  ( (x == GPIOA) ? 0 :\
										(x == GPIOB) ? 1 :\
										(x == GPIOC) ? 2 :\
										(x == GPIOD) ? 3 :\
										(x == GPIOE) ? 4 :\
										(x == GPIOH) ? 7 : 0 )

/*
 * This is a configuration structure for a GPIO pin
 */

typedef struct
{
	GPIO_TypeDef *pGPIOx;      /* hold the base address of the GPIO port which the pin belongs */
	uint8_t GPIO_PinNumber; 	/*!< possible modes from @GPIO_PIN_NUMBER >*/
	uint8_t GPIO_PinMode;		/*!< possible modes from @GPIO_PIN_MODES >*/
	uint8_t	GPIO_PinSpeed; 		/*!< possible modes from @GPIO_PIN_SPEED >*/
	uint8_t GPIO_PinOPType;		/*!< possible modes from @GPIO_PIN_OP_TYPE >*/
	uint8_t GPIO_PinPuPdControl;/*!< possible modes from @GPIO_PIN_PUPD >*/
	uint8_t GPIO_PinAltFunMode;	/*!< possible modes from @GPIO_PIN_ >*/
}GPIO_PinConfig_t;


/*
 * @GPIO_PIN_NUMBER
 * GPIO pin possible number
 */

#define GPIO_PIN_NO_0		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3		3
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5		5
#define GPIO_PIN_NO_6		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15		15


/*
 * @GPIO_PIN_MODES
 * GPIO pin possible modes
 */

#define GPIO_MODE_IN 		0
#define GPIO_MODE_OUT 		1
#define GPIO_MODE_ALTFN 	2
#define GPIO_MODE_ANALOG	3
#define GPIO_MODE_IT_FT		4 // input type falling
#define GPIO_MODE_IT_RT		5 // input type rising
#define GPIO_MODE_IT_RFT	6 // input type rising and falling


/* 
 * @GPIO_PIN_SPEED
 * GPIO pin possible output speeds
 */

#define GPIO_SPEED_LOW		0
#define	GPIO_SPEED_MEDIUM	1
#define GPIO_SPEED_FAST		2
#define GPIO_SPEED_HIGH		3


/*
 * @GPIO_PIN_SPEED
 * GPIO pin possible output types
 */

#define GPIO_OP_TYPE_PP		0
#define GPIO_OP_TYPE_OD		1


/*
 * @GPIO_PIN_PUPD
 * GPIO pin pull up and pull down configuration
 */

#define GPIO_NO_PUPD		0
#define GPIO_PIN_PU			1
#define GPIO_PIN_PD			2

/*
 * @GPIO_PIN_ALTFN
 * GPIO alternate functions
 */

#define GPIO_PIN_ALTFN_0            0
#define GPIO_PIN_ALTFN_1            1
#define GPIO_PIN_ALTFN_2            2
#define GPIO_PIN_ALTFN_3            3
#define GPIO_PIN_ALTFN_4            4
#define GPIO_PIN_ALTFN_5            5
#define GPIO_PIN_ALTFN_6            6
#define GPIO_PIN_ALTFN_7            7

#define GPIO_PIN_NO_ALTFN           GPIO_PIN_ALTFN_0


// GPIO_PIN_ALTFN_SPECIF_FUNCTION

#define PA5_ALTFN_TIM2_CH1			GPIO_PIN_ALTFN_1
#define PA2_ALTFN_UART2_TX			GPIO_PIN_ALTFN_7
#define PA3_ALTFN_UART2_RX			GPIO_PIN_ALTFN_7

#define GPIO_OK                     0

#define GPIO_PIN_SET                1
#define GPIO_PIN_RESET              0


/********************************************************************************************
 * 								APIs supported by this driver
 * 					for more information check the function definitions
 ********************************************************************************************/

/*
 *  Peripheral clock setup
 */
void GPIO_PeriClockControl(GPIO_TypeDef *pGPIOx, uint8_t EnorDi);

/*
 * Init and De-init
 */
uint8_t GPIO_Init(GPIO_PinConfig_t *pGPIOConfig);
void GPIO_Init_table(const GPIO_PinConfig_t *pGPIOConfig, uint32_t Len);
void GPIO_DeInit(GPIO_TypeDef *pGPIOx);

/*
 * Data read and write
 */
uint8_t  GPIO_ReadFromInputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_TypeDef *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_ToggleOutputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber);

/*
 * Runtime configurations
 */
void GPIO_SetPinMode      (GPIO_TypeDef *pGPIOx, uint8_t pinNumber, uint8_t mode);
void GPIO_SetPinPull      (GPIO_TypeDef *pGPIOx, uint8_t pinNumber, uint8_t pull);
void GPIO_SetPinSpeed     (GPIO_TypeDef *pGPIOx, uint8_t pinNumber, uint8_t speed);
void GPIO_SetPinOutputType(GPIO_TypeDef *pGPIOx, uint8_t pinNumber, uint8_t otype);



#endif /* INC_GPIO_H_ */