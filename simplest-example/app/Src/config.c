#include "config.h"

/*
 * PC13 -> onboard led 
 * PA2  -> UART2 TX
 * PA3  -> UART2 RX
 */
static const GPIO_PinConfig_t pins[] =
{
	{
		.pGPIOx					= LED_PORT,
		.GPIO_PinNumber			= LED_PIN,
		.GPIO_PinMode			= GPIO_MODE_OUT,
		.GPIO_PinSpeed			= GPIO_SPEED_LOW,
		.GPIO_PinOPType			= GPIO_OP_TYPE_PP,
		.GPIO_PinPuPdControl	= GPIO_NO_PUPD,
		.GPIO_PinAltFunMode		= GPIO_PIN_NO_ALTFN,
	},
	{
		.pGPIOx					= GPIOA,
		.GPIO_PinNumber			= GPIO_PIN_NO_2,
		.GPIO_PinMode			= GPIO_MODE_ALTFN,
		.GPIO_PinSpeed			= GPIO_SPEED_FAST,
		.GPIO_PinOPType			= GPIO_OP_TYPE_PP,
		.GPIO_PinPuPdControl	= GPIO_PIN_PU,
		.GPIO_PinAltFunMode		= PA2_ALTFN_UART2_TX,
	},
	{
		.pGPIOx					= GPIOA,
		.GPIO_PinNumber			= GPIO_PIN_NO_3,
		.GPIO_PinMode			= GPIO_MODE_ALTFN,
		.GPIO_PinSpeed			= GPIO_SPEED_FAST,
		.GPIO_PinOPType			= GPIO_OP_TYPE_PP,
		.GPIO_PinPuPdControl	= GPIO_PIN_PU,
		.GPIO_PinAltFunMode		= PA3_ALTFN_UART2_RX,
	},
	{
		.pGPIOx					= GPIOA,
		.GPIO_PinNumber			= GPIO_PIN_NO_11,
		.GPIO_PinMode			= GPIO_MODE_ALTFN,
		.GPIO_PinSpeed			= GPIO_SPEED_HIGH,
		.GPIO_PinOPType			= GPIO_OP_TYPE_PP,
		.GPIO_PinPuPdControl	= GPIO_NO_PUPD,
		.GPIO_PinAltFunMode		= PA11_ALTFN_OTG_FS_DM,
	},
	{
		.pGPIOx					= GPIOA,
		.GPIO_PinNumber			= GPIO_PIN_NO_12,
		.GPIO_PinMode			= GPIO_MODE_ALTFN,
		.GPIO_PinSpeed			= GPIO_SPEED_HIGH,
		.GPIO_PinOPType			= GPIO_OP_TYPE_PP,
		.GPIO_PinPuPdControl	= GPIO_NO_PUPD,
		.GPIO_PinAltFunMode		= PA12_ALTFN_OTG_FS_DP,
	},
};

static void serial_init(void)
{
	UART_Config_t uart =
	{
		.pUARTx				= USART2,
		.UART_Mode			= UART_MODE_TXRX,
		.UART_Baud			= UART_STD_BAUD_115200,
		.UART_NoOfStopBits	= UART_STOPBITS_1,
		.UART_WordLength	= UART_WORDLEN_8BITS,
		.UART_ParityControl	= UART_PARITY_DISABLE,
		.UART_HWFlowControl	= UART_HW_FLOW_CTRL_NONE,
	};

	UART_Init(&uart);
	UART_PeripheralControl(USART2, ENABLE);
}

void config_app(void)
{
    if(clock_init() != CLOCK_OK)
    {
        while(1); // stop here
    }
	systick_init(TICK_HZ);

	GPIO_Init_table(pins, sizeof(pins)/sizeof(pins[0]));

	serial_init();
}
