#ifndef INC_DRIVER_INTERRUPT_H_
#define INC_DRIVER_INTERRUPT_H_

#include "stm32f4xx.h"

/* IRQ numbers now come from the IRQn_Type enum in stm32f411xe.h, e.g. USART2_IRQn */

/********************************************************************************************
 *                              APIs supported by this driver                               *
 *                  for more information check the function definitions                     *
 ********************************************************************************************/

void interrupt_Config(IRQn_Type IRQNumber, uint8_t EnorDi);


#endif /* INC_DRIVER_INTERRUPT_H_ */