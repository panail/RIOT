/*
 * Copyright (C) 2015-2016 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_tk-mprs01a
 * @{
 *
 * @file
 * @brief       Configuration of CPU peripherals for Thermokon MPRS01-A
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
 * @brief   Clock configuration
 * @{
 */
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
#ifndef CLOCK_HFXO_FREQ
#define CLOCK_HFXO_FREQ 38400000UL
#endif
#ifndef CLOCK_LFXO_FREQ
#define CLOCK_LFXO_FREQ 32768UL
#endif
/** @} */


/**
 * @brief   ADC configuration
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
        .input = adcPosSelTEMP,         /* internal temp sensor see RefMan 24.3.8.9 page 772 */
        .reference = adcRef1V25,
        .acq_time = adcAcqTime8
    },
    {
        .dev = 0,
        .input = adcPosSelAVDD,         /* internal route of VDD to adc */
        .reference = adcRef5V,
        .acq_time = adcAcqTime8
    },
    
};

#define ADC_DEV_NUMOF       PERIPH_NUMOF(adc_config)
#define ADC_NUMOF           PERIPH_NUMOF(adc_channel_config)

/** @} */

/**
 * @brief   DAC configuration
 */
#define DAC_NUMOF           (0U)

/**
 * @brief   I2C configuration
 * @{
 */

#define I2C_NUMOF           PERIPH_NUMOF(0U)


/** @} */

/**
 * @brief   PWM configuration
 * @{
 */
static const pwm_chan_conf_t pwm_channel_config[] = {
    /* no available channels */
};

static const pwm_conf_t pwm_config[] = {
    /* no available timers */
};

#define PWM_NUMOF                    (0U)
/** @} */

/**
 * @brief   RTC configuration
 */
#define RTC_NUMOF           (1U)

/**
 * @brief   RTT configuration
 * @{
 */
#define RTT_NUMOF           (1U)

#define RTT_MAX_VALUE       (0xFFFFFFFF)
#define RTT_FREQUENCY       (1U)
/** @} */

/**
 * @brief   SPI configuration
 * @{
 */
 
//static const spi_dev_t spi_config[] = {
//    {
//        USART1,                             /* device */
//        GPIO_PIN(PC, 6),                    /* MOSI pin */
//        GPIO_PIN(PC, 7),                    /* MISO pin */
//        GPIO_PIN(PC, 8),                    /* CLK pin */
//        USART_ROUTELOC0_RXLOC_LOC11 |
//            USART_ROUTELOC0_TXLOC_LOC11 |
//            USART_ROUTELOC0_CLKLOC_LOC11,   /* AF location */
//        cmuClock_USART1,                    /* CMU register */
//        USART1_RX_IRQn                      /* IRQ base channel */
//    }
//};



/** @} */

/**
 * @brief   Timer configuration
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
 * @brief   UART configuration
 * @{
 */
static const uart_conf_t uart_config[] = {
    {
        .dev = USART0,
        .rx_pin = GPIO_PIN(PC, 9),
        .tx_pin = GPIO_PIN(PC, 8),
        .loc = USART_ROUTELOC0_RXLOC_LOC13 |
               USART_ROUTELOC0_TXLOC_LOC13,
        .cmu = cmuClock_USART0,
        .irq = USART0_RX_IRQn
    },

//    ,
//    {
//        LEUART0,                            /* device */
//        GPIO_PIN(PD, 11),                   /* RX pin */
//        GPIO_PIN(PD, 10),                   /* TX pin */
//        LEUART_ROUTELOC0_RXLOC_LOC18 |
//            LEUART_ROUTELOC0_TXLOC_LOC18,   /* AF location */
//        cmuClock_LEUART0,                   /* CMU register */
//        LEUART0_IRQn                        /* IRQ base channel */
//    }
};

#define UART_NUMOF          PERIPH_NUMOF(uart_config)
#define UART_0_ISR_RX       isr_usart0_rx


/** @} */

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_CONF_H */
/** @} */
