#include "config.h"
#include "usb.h"
#include "tusb.h"

int main(void)
{
    config_app();
	usb_init();

	ticks_timeout_t blink;
	ticks_timeoutInit(&blink, BLINK_PERIOD_MS);

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
