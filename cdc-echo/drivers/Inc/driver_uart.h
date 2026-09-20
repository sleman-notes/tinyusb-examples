#ifndef INC_DRIVER_UART_H_
#define INC_DRIVER_UART_H_

#include "stm32f4xx.h"
#include <stdbool.h>

/*
 * Clock enable/disable and reset macros for USARTx
 */

#define UART1_PCLK_EN()		(RCC->APB2ENR |= RCC_APB2ENR_USART1EN)
#define UART2_PCLK_EN()		(RCC->APB1ENR |= RCC_APB1ENR_USART2EN)
#define UART6_PCLK_EN()		(RCC->APB2ENR |= RCC_APB2ENR_USART6EN)

#define UART1_PCLK_DI()		(RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN)
#define UART2_PCLK_DI()		(RCC->APB1ENR &= ~RCC_APB1ENR_USART2EN)
#define UART6_PCLK_DI()		(RCC->APB2ENR &= ~RCC_APB2ENR_USART6EN)

#define UART1_REG_RESET()	do{RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST; RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;}while(0)
#define UART2_REG_RESET()	do{RCC->APB1RSTR |= RCC_APB1RSTR_USART2RST; RCC->APB1RSTR &= ~RCC_APB1RSTR_USART2RST;}while(0)
#define UART6_REG_RESET()	do{RCC->APB2RSTR |= RCC_APB2RSTR_USART6RST; RCC->APB2RSTR &= ~RCC_APB2RSTR_USART6RST;}while(0)

typedef struct
{
    USART_TypeDef *pUARTx;
	uint8_t UART_Mode;
	uint32_t UART_Baud;
	uint8_t UART_NoOfStopBits;
	uint8_t UART_WordLength;
	uint8_t UART_ParityControl;
	uint8_t UART_HWFlowControl;
}UART_Config_t;

typedef enum
{
    UART_OK             = 0x00U,    /**< No error */
    UART_ERROR_TIMEOUT  = 0x01U,    /**< Timeout occurred */
    UART_ERROR_FE       = 0x02U,    /**< Framing error */
    UART_ERROR_NE       = 0x04U,    /**< Noise error */
    UART_ERROR_ORE      = 0x08U,    /**< Overrun error */
    UART_ERROR_PE       = 0x10U,    /**< Parity error */
    UART_ERROR_INVALID  = 0x20U,    /**< Invalid parameter */
} UART_Error_e;

#define UART_DEFAULT_TIMEOUT    100U


/* USART_CR1 */
#define UART_CR1_SBK        0
#define UART_CR1_RWU        1
#define UART_CR1_RE         2
#define UART_CR1_TE         3
#define UART_CR1_IDLEIE     4
#define UART_CR1_RXNEIE     5
#define UART_CR1_TCIE       6
#define UART_CR1_TXEIE      7
#define UART_CR1_PEIE       8
#define UART_CR1_PS         9
#define UART_CR1_PCE        10
#define UART_CR1_WAKE       11
#define UART_CR1_M          12
#define UART_CR1_UE         13
#define UART_CR1_OVER8      15

/* USART_CR2 */
#define UART_CR2_ADD        0
#define UART_CR2_LBDL       5
#define UART_CR2_LBDIE      6
#define UART_CR2_LBCL       8
#define UART_CR2_CPHA       9
#define UART_CR2_CPOL       10
#define UART_CR2_STOP       12
#define UART_CR2_LINEN      14

/* USART_CR3 */
#define UART_CR3_EIE        0
#define UART_CR3_IREN       1
#define UART_CR3_IRLP       2
#define UART_CR3_HDSEL      3
#define UART_CR3_NACK       4
#define UART_CR3_SCEN       5
#define UART_CR3_DMAR       6
#define UART_CR3_DMAT       7
#define UART_CR3_RTSE       8
#define UART_CR3_CTSE       9
#define UART_CR3_CTSIE      10
#define UART_CR3_ONEBIT     11

/* USART_SR */
#define UART_SR_PE          0
#define UART_SR_FE          1
#define UART_SR_NE          2
#define UART_SR_ORE         3
#define UART_SR_IDLE        4
#define UART_SR_RXNE        5
#define UART_SR_TC          6
#define UART_SR_TXE         7
#define UART_SR_LBD         8
#define UART_SR_CTS         9


/******************************************************************************************
 *                          POSSIBLE CONFIGURATIONS
 ******************************************************************************************/

/* @UART_Mode */
#define UART_MODE_ONLY_TX       0
#define UART_MODE_ONLY_RX       1
#define UART_MODE_TXRX          2

/* @UART_Baud */
#define UART_STD_BAUD_1200      1200
#define UART_STD_BAUD_2400      2400
#define UART_STD_BAUD_9600      9600
#define UART_STD_BAUD_19200     19200
#define UART_STD_BAUD_38400     38400
#define UART_STD_BAUD_57600     57600
#define UART_STD_BAUD_115200    115200
#define UART_STD_BAUD_230400    230400
#define UART_STD_BAUD_460800    460800
#define UART_STD_BAUD_921600    921600
#define UART_STD_BAUD_2M        2000000
#define UART_STD_BAUD_3M        3000000

/* @UART_ParityControl */
#define UART_PARITY_DISABLE     0
#define UART_PARITY_EN_EVEN     1
#define UART_PARITY_EN_ODD      2

/* @UART_WordLength */
#define UART_WORDLEN_8BITS      0
#define UART_WORDLEN_9BITS      1

/* @UART_NoOfStopBits */
#define UART_STOPBITS_1         0
#define UART_STOPBITS_0_5       1
#define UART_STOPBITS_2         2
#define UART_STOPBITS_1_5       3

/* @UART_HWFlowControl */
#define UART_HW_FLOW_CTRL_NONE      0
#define UART_HW_FLOW_CTRL_CTS       1
#define UART_HW_FLOW_CTRL_RTS       2
#define UART_HW_FLOW_CTRL_CTS_RTS   3

/* UART status flags */
#define UART_FLAG_TXE       (1U << UART_SR_TXE)
#define UART_FLAG_RXNE      (1U << UART_SR_RXNE)
#define UART_FLAG_TC        (1U << UART_SR_TC)

/* UART CR1 interrupt enable bits */
#define UART_INTERRUPT_RXNEIE   (1U << UART_CR1_RXNEIE)
#define UART_INTERRUPT_TXEIE    (1U << UART_CR1_TXEIE)
#define UART_INTERRUPT_TCIE     (1U << UART_CR1_TCIE)


/********************************************************************************************
 *                                  Driver API
 ********************************************************************************************/

/* Peripheral clock */
void UART_PeriClockControl(USART_TypeDef *pUARTx, uint8_t EnorDi);

/* Init and De-init */
void UART_Init(UART_Config_t *pUARTConfig);
void UART_DeInit(USART_TypeDef *pUARTx);

/* Data write and read */
UART_Error_e UART_Write(USART_TypeDef *pUARTx, const uint8_t *pTxBuffer, uint32_t Len);
UART_Error_e UART_WriteByte(USART_TypeDef *pUARTx, uint8_t data);
uint8_t      UART_ReadByte(USART_TypeDef *pUARTx);

/* Status and control */
UART_Error_e UART_WaitForFlag(USART_TypeDef *pUARTx, uint32_t flag, bool status, uint32_t timeoutMs);
bool         UART_GetFlagStatus(USART_TypeDef *pUARTx, uint32_t flag);
void         UART_PeripheralControl(USART_TypeDef *pUARTx, uint8_t EnorDi);
void         UART_InterruptControl(USART_TypeDef *pUARTx, uint32_t interruptMask, uint8_t EnorDi);

#endif /* INC_DRIVER_UART_H_ */