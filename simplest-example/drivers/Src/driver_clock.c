#include "driver_clock.h"
#include <stdbool.h>

/*********************************************************************
 * Private Helper Functions
 *********************************************************************/

static bool _clock_wait_flag(__IO uint32_t *pReg, uint32_t mask)
{
    uint32_t timeout = CLOCK_TIMEOUT_CYCLES;

    while((*pReg & mask) == 0U)
    {
        if(timeout == 0U)
        {
            return false;
        }
        timeout--;
    }

    return true;
}

static void _clock_power_scale_config(void)
{
    PWR_PCLK_EN();

    /* Config 1 to go above 84Mhz*/
    PWR->CR &= ~PWR_CR_VOS_Msk;
    PWR->CR |=  PWR_CR_VOS_SCALE1;
}

static CLOCK_Error_e _clock_flash_latency_config(uint32_t waitStates)
{
    uint32_t flash_acr = FLASH->ACR;

    flash_acr &= ~FLASH_ACR_LATENCY_Msk;
    flash_acr |= (waitStates << FLASH_ACR_LATENCY_Pos);
    flash_acr |= FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN;

    FLASH->ACR = flash_acr;

    /* the latency write is not guaranteed */
    if ((FLASH->ACR & FLASH_ACR_LATENCY_Msk) != (waitStates << FLASH_ACR_LATENCY_Pos))
    {
        return CLOCK_ERROR_LATENCY;
    }

    return CLOCK_OK;
}

static void _clock_pll_config(void)
{
    uint32_t rcc_pllcfgr = 0U;

    rcc_pllcfgr |= (PLL_M << RCC_PLLCFGR_PLLM_Pos);
    rcc_pllcfgr |= (PLL_N << RCC_PLLCFGR_PLLN_Pos);
    rcc_pllcfgr |= (((PLL_P / 2U) - 1U) << RCC_PLLCFGR_PLLP_Pos);   /* 00:/2 01:/4 10:/6 11:/8 */
    rcc_pllcfgr |= (PLL_Q << RCC_PLLCFGR_PLLQ_Pos);
    rcc_pllcfgr |= RCC_PLLCFGR_PLLSRC_HSE;

    RCC->PLLCFGR = rcc_pllcfgr;
}

static void _clock_bus_prescaler_config(void)
{
    uint32_t rcc_cfgr = RCC->CFGR;

    rcc_cfgr &= ~(RCC_CFGR_HPRE_Msk | RCC_CFGR_PPRE1_Msk | RCC_CFGR_PPRE2_Msk);

    rcc_cfgr |= RCC_CFGR_HPRE_DIV1;     /* AHB  = SYSCLK / 1 = 96 MHz */
    rcc_cfgr |= RCC_CFGR_PPRE1_DIV2;    /* APB1 = HCLK   / 2 = 48 MHz */
    rcc_cfgr |= RCC_CFGR_PPRE2_DIV1;    /* APB2 = HCLK   / 1 = 96 MHz */

    RCC->CFGR = rcc_cfgr;
}

static CLOCK_Error_e _clock_sysclk_switch_to_pll(void)
{
    uint32_t timeout = CLOCK_TIMEOUT_CYCLES;

    RCC->CFGR &= ~RCC_CFGR_SW_Msk;
    RCC->CFGR |=  RCC_CFGR_SW_PLL;

    /* Confirm that switch happened */
    while ((RCC->CFGR & RCC_CFGR_SWS_Msk) != RCC_CFGR_SWS_PLL)
    {
        if (timeout == 0U)
        {
            return CLOCK_ERROR_SW_TIMEOUT;
        }

        timeout--;
    }

    return CLOCK_OK;
}

/*********************************************************************
 * Public API Implementations
 *********************************************************************/

 CLOCK_Error_e clock_init(void)
 {
    CLOCK_Error_e clock_error = CLOCK_OK;

    // 1. regulator first
    _clock_power_scale_config();

    // 2. slow the flash
    clock_error = _clock_flash_latency_config(FLASH_WAIT_STATES);

    if(clock_error != CLOCK_OK)
    {
        return clock_error;
    }

    // 3. Enable the crystal
    RCC->CR |= RCC_CR_HSEON;

    if (_clock_wait_flag(&RCC->CR, RCC_CR_HSERDY) == false)
    {
        return CLOCK_ERROR_HSE_TIMEOUT;
    }

    /* 4. PLLCFGR must be stopped before config */
    RCC->CR &= ~RCC_CR_PLLON;

    _clock_pll_config();

    RCC->CR |= RCC_CR_PLLON;

    if (_clock_wait_flag(&RCC->CR, RCC_CR_PLLRDY) == false)
    {
        return CLOCK_ERROR_PLL_TIMEOUT;
    }

    /* 5. prescalers before the switch */
    _clock_bus_prescaler_config();

    /* 6. switch and confirm */
    clock_error = _clock_sysclk_switch_to_pll();

    if (clock_error != CLOCK_OK)
    {
        return clock_error;
    }

    /* TinyUSB reads SystemCoreClock, and it was in system_stm32f4xx.c */
    SystemCoreClock = HCLK_CLOCK;

    return CLOCK_OK;
 }

uint32_t clock_get(void)
{
    return HCLK_CLOCK;
}

uint32_t clock_get_hclk(void)
{
    return HCLK_CLOCK;
}

uint32_t clock_get_pclk1(void)
{
    return PCLK1_CLOCK;
}

uint32_t clock_get_pclk2(void)
{
    return PCLK2_CLOCK;
}
