/*
 * Copyright (C) 2017 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    boards_TK-MPRS01-A Thermokon window contact
 * @ingroup     boards
 * @brief       Support for the Thermokon TK-MPRS01-A
 * @{
 *
 * @file
 * @brief       Board specific definitions for the Thermokon TK-MPRS01-A
 *
 *
 * @author      Kai Beckmann <kai.beckmann@hs-rm.de>
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 */

#ifndef BOARD_H
#define BOARD_H

#include "cpu.h"

#include "periph_conf.h"
#include "periph/gpio.h"
#include "periph/spi.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Xtimer configuration.
 * @note    The timer runs at 250 KHz to increase accuracy.
 * @{
 */
#define XTIMER_HZ           (250000UL)
#define XTIMER_WIDTH        (16)
/** @} */


/**
 * @brief   Push button pin definitions.
 * @{
 */
#define PB0_PIN            GPIO_PIN(PF, 7)
#define BTN_LRN_PIN         GPIO_PIN(PA, 0)
#define BTN_PRG_PIN         GPIO_PIN(PD, 15)
/** @} */

/**
 * @brief    LED pin definitions.
 * @{
 */
#define LED0_PIN            GPIO_PIN(PF, 6)
#define LED_LRN_PIN         GPIO_PIN(PD, 13)
#define LED_PRG_PIN         GPIO_PIN(PD, 14)
/** @} */

/**
 * @brief   Macros for controlling the on-board LEDs.
 * @{
 */
#define LED0_ON             gpio_set(LED0_PIN)
#define LED0_OFF            gpio_clear(LED0_PIN)
#define LED0_TOGGLE         gpio_toggle(LED0_PIN)

#define LED_LRN_ON          gpio_set(LED_LRN_PIN)
#define LED_LRN_OFF         gpio_clear(LED_LRN_PIN)
#define LED_LRN_TOGGLE      gpio_toggle(LED_LRN_PIN)

#define LED_PRG_ON          gpio_set(LED_PRG_PIN)
#define LED_PRG_OFF         gpio_clear(LED_PRG_PIN)
#define LED_PRG_TOGGLE      gpio_toggle(LED_PRG_PIN)
/** @} */

/**
 * @brief   Reed contact
 * @{
 */
#define RELAIS_PIN    GPIO_PIN(PA, 1)
/** @} */


 /**
 * @brief   adc line for internal temperature sensor
 * @{
 */
#define INTERNAL_TEMP_SENSOR_MEASS_LINE    0
/** @} */

/**
 * @brief   adc line for measure VDD voltage
 * @{
 */
#define VDD_MEASS_LINE    1
/** @} */



// TODO Sensors


/**
 * @brief   Initialize the board (GPIO, sensors, clocks).
 */
void board_init(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
/** @} */
