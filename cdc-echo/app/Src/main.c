#include "config.h"
#include "usb.h"
#include "tusb.h"
#include <stdio.h>

static void usb_wait_connection(void)
{
    while(!tud_cdc_connected())
    {
        tud_task();
    }
}

int main(void)
{
    config_app();
	usb_init();
	usb_wait_connection();

	ticks_timeout_t blink;
	ticks_timeoutInit(&blink, BLINK_PERIOD_MS);

	printf("Init the board!\r\n");

	while(1)
	{
		tud_task();

		if(ticks_timeoutIsExpired(&blink))
		{
			GPIO_ToggleOutputPin(LED_PORT, LED_PIN);
			ticks_timeoutInit(&blink, BLINK_PERIOD_MS);
		}

		if(tud_cdc_available())
		{
			uint8_t buf[64];
			uint32_t count = tud_cdc_read(buf, sizeof(buf));

			tud_cdc_write(buf, count);
			tud_cdc_write_flush();
		}
	}
}

int __io_putchar(int ch)
{
	tud_cdc_write_char((char)ch);

    if(ch == '\n') tud_cdc_write_flush();

    return ch;
}
