/*
 * Copyright (C) 2015-2017 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_brd4162a
 * @{
 *
 * @file
 * @brief       Configuration of CPU peripherals for the BRD4162A starter kit
 *
 * @author      Kai Beckmann <kai.beckmann@hs-rm.de>
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 */

#ifndef PERIPH_CONF_H
#define PERIPH_CONF_H

#include "cpu.h"

#include "periph_cpu.h"

#include "em_cmu.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Internal macro to calculate *_NUMOF based on config.
 */
#define PERIPH_NUMOF(config)    (sizeof(config) / sizeof(config[0]))

/**
 * @name    Clock configuration
 * @{
 */
#ifndef CMU_HFXOINIT
#define CMU_HFXOINIT        CMU_HFXOINIT_DEFAULT
#endif
#ifndef CMU_LFXOINIT
#define CMU_LFXOINIT        CMU_LFXOINIT_DEFAULT
#endif

#ifndef CLOCK_HF
#define CLOCK_HF            cmuSelect_HFXO
#endif
#ifndef CLOCK_CORE_DIV
#define CLOCK_CORE_DIV      cmuClkDiv_1
#endif
#ifndef CLOCK_LFA
#define CLOCK_LFA           cmuSelect_LFRCO
#endif
#ifndef CLOCK_LFB
#define CLOCK_LFB           cmuSelect_LFRCO
#endif
#ifndef CLOCK_LFE
#define CLOCK_LFE           cmuSelect_LFRCO
#endif
/** @} */

/**
 * @name    EMU configuration
 * @{
 */
#ifndef EMU_DCDCINIT
#define EMU_DCDCINIT         EMU_DCDCINIT_DEFAULT
#endif
#ifndef EMU_EM23INIT
#define EMU_EM23INIT         EMU_EM23INIT_DEFAULT
#endif
#ifndef EMU_EM4INIT
#define EMU_EM4INIT         EMU_EM4INIT_DEFAULT
#endif
/** @} */

#if 0
#define CLOCK_HFXO_INIT                                                  \
  {                                                                        \
    false,      /* Low-noise mode for EFR32 */                             \
    false,      /* Disable auto-start on EM0/1 entry */                    \
    false,      /* Disable auto-select on EM0/1 entry */                   \
    false,      /* Disable auto-start and select on RAC wakeup */          \
    _CMU_HFXOSTARTUPCTRL_CTUNE_DEFAULT,                                    \
    0x142,      /* Steady-state CTUNE for WSTK boards without load caps */ \
    _CMU_HFXOSTEADYSTATECTRL_REGISH_DEFAULT,                               \
    0x20,       /* Matching errata fix in CHIP_Init() */                   \
    0x7,        /* Recommended steady-state osc core bias current */       \
    0x6,        /* Recommended peak detection threshold */                 \
    _CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_DEFAULT,                          \
    0xA,        /* Recommended peak detection timeout  */                  \
    0x4,        /* Recommended steady timeout */                           \
    _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_DEFAULT,                           \
    cmuOscMode_Crystal,                                                    \
  }

#if !defined(CMU_HFXOINIT_WSTK_DEFAULT)
#define CMU_HFXOINIT_WSTK_DEFAULT                                          \
  {                                                                        \
    false,      /* Low-noise mode for EFR32 */                             \
    false,      /* Disable auto-start on EM0/1 entry */                    \
    false,      /* Disable auto-select on EM0/1 entry */                   \
    false,      /* Disable auto-start and select on RAC wakeup */          \
    _CMU_HFXOSTARTUPCTRL_CTUNE_DEFAULT,                                    \
    0x142,      /* Steady-state CTUNE for WSTK boards without load caps */ \
    _CMU_HFXOSTEADYSTATECTRL_REGISH_DEFAULT,                               \
    _CMU_HFXOSTARTUPCTRL_IBTRIMXOCORE_DEFAULT,                             \
    0x7,        /* Recommended steady-state osc core bias current */       \
    0x6,        /* Recommended peak detection threshold */                 \
    _CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_DEFAULT,                          \
    0xA,        /* Recommended peak detection timeout  */                  \
    0x4,        /* Recommended steady timeout */                           \
    _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_DEFAULT,                           \
    cmuOscMode_Crystal,                                                    \
  }
#endif

#endif

#if 0
#if !defined(EMU_DCDCINIT_WSTK_DEFAULT)
/* Use emlib defaults */
#define EMU_DCDCINIT_WSTK_DEFAULT EMU_DCDCINIT_DEFAULT
#endif
#endif

#define CLOCK_HFXO_FREQ 38400000UL
#define CLOCK_LFXO_FREQ 32768UL




/** @} */

/**
 * @name    EMU configuration
 * @{
 */
#ifndef EMU_DCDCINIT
#define EMU_DCDCINIT         EMU_DCDCINIT_DEFAULT
#endif
#ifndef EMU_EM23INIT
#define EMU_EM23INIT         EMU_EM23INIT_DEFAULT
#endif
#ifndef EMU_EM4INIT
#define EMU_EM4INIT         EMU_EM4INIT_DEFAULT
#endif
/** @} */

/**
 * @name    ADC configuration
 * @{
 */
static const adc_conf_t adc_config[] = {
    {
        .dev = ADC0,
        .cmu = cmuClock_ADC0,
    }
};

static const adc_chan_conf_t adc_channel_config[] = {
    {
        .dev = 0,
        .input = adcPosSelTEMP,
        .reference = adcRef1V25,
        .acq_time = adcAcqTime8
    },
    {
        .dev = 0,
        .input = adcPosSelAVDD,
        .reference = adcRef5V,
        .acq_time = adcAcqTime8
    }
};

#define ADC_DEV_NUMOF       PERIPH_NUMOF(adc_config)
#define ADC_NUMOF           PERIPH_NUMOF(adc_channel_config)
/** @} */

/**
 * @name    I2C configuration
 * @{
 */
static const i2c_conf_t i2c_config[] = {
    {
        .dev = I2C0,
        .sda_pin = GPIO_PIN(PC, 10),
        .scl_pin = GPIO_PIN(PC, 11),
        .loc = I2C_ROUTELOC0_SDALOC_LOC15 |
               I2C_ROUTELOC0_SCLLOC_LOC15,
        .cmu = cmuClock_I2C0,
        .irq = I2C0_IRQn
    }
};

#define I2C_NUMOF           PERIPH_NUMOF(i2c_config)
/** @} */

/**
 * @brief   RTC configuration
 */
#define RTC_NUMOF           (1U)

/**
 * @name    RTT configuration
 * @{
 */
#define RTT_NUMOF           (1U)

#define RTT_MAX_VALUE       (0xFFFFFFFF)
#define RTT_FREQUENCY       (1U)
/** @} */

/**
 * @name    SPI configuration
 * @{
 */
static const spi_dev_t spi_config[] = {
    {
        .dev = USART1,
        .mosi_pin = GPIO_PIN(PC, 6),
        .miso_pin = GPIO_PIN(PC, 7),
        .clk_pin = GPIO_PIN(PC, 8),
        .loc = USART_ROUTELOC0_RXLOC_LOC11 |
               USART_ROUTELOC0_TXLOC_LOC11 |
               USART_ROUTELOC0_CLKLOC_LOC11,
        .cmu = cmuClock_USART1,
        .irq = USART1_RX_IRQn
    }
};

#define SPI_NUMOF           PERIPH_NUMOF(spi_config)
/** @} */

/**
 * @name    Timer configuration
 *
 * The implementation uses two timers in cascade mode.
 * @{
 */
static const timer_conf_t timer_config[] = {
    {
        {
            .dev = TIMER0,
            .cmu = cmuClock_TIMER0
        },
        {
            .dev = TIMER1,
            .cmu = cmuClock_TIMER1
        },
        .irq = TIMER1_IRQn
    }
};

#define TIMER_NUMOF         PERIPH_NUMOF(timer_config)
#define TIMER_0_ISR         isr_timer1
/** @} */

/**
 * @name    UART configuration
 * @{
 */
static const uart_conf_t uart_config[] = {
    {
        .dev = USART0,
        .rx_pin = GPIO_PIN(PA, 1),
        .tx_pin = GPIO_PIN(PA, 0),
        .loc = USART_ROUTELOC0_RXLOC_LOC0 |
               USART_ROUTELOC0_TXLOC_LOC0,
        .cmu = cmuClock_USART0,
        .irq = USART0_RX_IRQn
    },
    {
        .dev = USART2,
        .rx_pin = GPIO_PIN(PA, 7),
        .tx_pin = GPIO_PIN(PA, 6),
        .loc = USART_ROUTELOC0_RXLOC_LOC1 |
               USART_ROUTELOC0_TXLOC_LOC1,
        .cmu = cmuClock_USART2,
        .irq = USART2_RX_IRQn
    },
    {
        .dev = USART3,
        .rx_pin = GPIO_PIN(PB, 7),
        .tx_pin = GPIO_PIN(PB, 6),
        .loc = USART_ROUTELOC0_RXLOC_LOC10 |
               USART_ROUTELOC0_TXLOC_LOC10,
        .cmu = cmuClock_USART3,
        .irq = USART3_RX_IRQn
    },
    {
        .dev = LEUART0,
        .rx_pin = GPIO_PIN(PD, 11),
        .tx_pin = GPIO_PIN(PD, 10),
        .loc = LEUART_ROUTELOC0_RXLOC_LOC18 |
               LEUART_ROUTELOC0_TXLOC_LOC18,
        .cmu = cmuClock_LEUART0,
        .irq = LEUART0_IRQn
    }
};

#define UART_NUMOF          PERIPH_NUMOF(uart_config)
#define UART_0_ISR_RX       isr_usart0_rx
#define UART_1_ISR_RX       isr_usart2_rx
#define UART_2_ISR_RX       isr_usart3_rx
#define UART_3_ISR_RX       isr_leuart0
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_CONF_H */
/** @} */
