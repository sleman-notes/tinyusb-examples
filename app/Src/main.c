#include "config.h"




static void serial_print(const char *msg)
{
	UART_Write(USART2, (const uint8_t *)msg, strlen(msg));
}

int main(void)
{
    config_app();
	
	serial_print("Hello World\r\n");

	while(1)
	{
		GPIO_ToggleOutputPin(LED_PORT, LED_PIN);

		ticks_delay(BLINK_PERIOD_MS);
	}
}
