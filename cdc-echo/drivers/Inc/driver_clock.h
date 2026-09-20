#ifndef INC_DRIVER_CLOCK_H_
#define INC_DRIVER_CLOCK_H_

#include "stm32f4xx.h"
#include <stdint.h>

/*
 * Blackpill WeAct -> 25 MHz HSE crystal
 *
 * VCO_in  = HSE     / PLL_M =  25 MHz / 25  =   1 MHz
 * VCO_out = VCO_in  * PLL_N =   1 MHz * 192 = 192 MHz
 * SYSCLK  = VCO_out / PLL_P = 192 MHz / 2   =  96 MHz
 * USB_CLK = VCO_out / PLL_Q = 192 MHz / 4   =  48 MHz  <- OTG_FS needs exactly this
 */
#define PLL_M                   25U
#define PLL_N                   192U
#define PLL_P                   2U
#define PLL_Q                   4U


#define HSI_CLOCK               16000000U   /* internal RC, the reset default    */
#define HSE_CLOCK               25000000U   /* Blackpill WeAct crystal           */

#define SYSCLK_CLOCK            96000000U
#define HCLK_CLOCK              96000000U   /* AHB  = SYSCLK / 1                 */
#define PCLK1_CLOCK             48000000U   /* APB1 = HCLK / 2, 50 MHz max       */
#define PCLK2_CLOCK             96000000U   /* APB2 = HCLK / 1, 100 MHz max      */

#define CLOCK_TIMEOUT_CYCLES    0x00100000U /* dumb loop, systick is not up yet  */

/*
 * Clock enable/disable for the peripherals this driver touches.
 */
#define PWR_PCLK_EN()           (RCC->APB1ENR |= RCC_APB1ENR_PWREN)
#define PWR_PCLK_DI()           (RCC->APB1ENR &= ~RCC_APB1ENR_PWREN)

#define OTGFS_PCLK_EN()         (RCC->AHB2ENR |= RCC_AHB2ENR_OTGFSEN)
#define OTGFS_PCLK_DI()         (RCC->AHB2ENR &= ~RCC_AHB2ENR_OTGFSEN)

#define PWR_CR_VOS_SCALE1       (PWR_CR_VOS_0 | PWR_CR_VOS_1)   /* 11 = Scale 1  */
#define FLASH_WAIT_STATES       FLASH_ACR_LATENCY_3WS           /* 90..100 MHz   */

typedef enum
{
    CLOCK_OK                    = 0x00U,    /**< No error                        */
    CLOCK_ERROR_LATENCY         = 0x01U,    /**< Flash refused the wait states   */
    CLOCK_ERROR_HSE_TIMEOUT     = 0x02U,    /**< Crystal never became ready      */
    CLOCK_ERROR_PLL_TIMEOUT     = 0x04U,    /**< PLL never locked                */
    CLOCK_ERROR_SW_TIMEOUT      = 0x08U,    /**< SYSCLK never switched to PLL    */
} CLOCK_Error_e;

/********************************************************************************************
 *                              APIs supported by this driver                               *
 *                  for more information check the function definitions                     *
 ********************************************************************************************/

CLOCK_Error_e clock_init(void);

uint32_t clock_get(void);
uint32_t clock_get_hclk(void);
uint32_t clock_get_pclk1(void);
uint32_t clock_get_pclk2(void);

#endif /* INC_DRIVER_CLOCK_H_ */