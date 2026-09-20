#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#include <string.h>

#include "driver_gpio.h"
#include "driver_uart.h"
#include "driver_systick.h"
#include "driver_clock.h"

#define LED_PORT		GPIOC
#define LED_PIN			GPIO_PIN_NO_13

#define BLINK_PERIOD_MS	500U

void config_app(void);

#endif /* INC_CONFIG_H_ */
