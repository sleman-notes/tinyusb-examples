#include "driver_interrupt.h"

void interrupt_Config(IRQn_Type IRQNumber, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		NVIC_EnableIRQ(IRQNumber);
	}else
	{
		NVIC_DisableIRQ(IRQNumber);
	}
}
