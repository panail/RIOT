/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    boards_TK-MPRS06-LCD-A Thermokon window contact
 * @ingroup     boards
 * @brief       Support for the Thermokon TK-MPRS06-LCD-A
 * @{
 *
 * @file
 * @brief       Board specific definitions for the Thermokon TK-MPRS06-LCD-A
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
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
 * @brief   Xtimer configuration
 * @note    The timer runs at 250 KHz to increase accuracy.
 * @{
 */
#define XTIMER_HZ           (250000UL)
#define XTIMER_WIDTH        (16)
/** @} */


/**
 * @brief   Push button pin definitions
 * @{
 */
#define BTN0_PIN            GPIO_PIN(PF, 7)
#define BTN1_PIN            GPIO_PIN(PC, 10)
#define BTN2_PIN            GPIO_PIN(PA, 4)
#define BTN3_PIN            GPIO_PIN(PB, 11)
#define BTN4_PIN            GPIO_PIN(PA, 5)
/** @} */

/**
 * @brief   LED pin definitions
 * @{
 */
#define LED0_PIN            GPIO_PIN(PF, 6)
/** @} */

/**
 * @brief   Macros for controlling the on-board LEDs
 * @{
 */
#define LED0_ON             gpio_set(LED0_PIN)
#define LED0_OFF            gpio_clear(LED0_PIN)
#define LED0_TOGGLE         gpio_toggle(LED0_PIN)
/** @} */

/**
 * @brief   Motion out pin
 * @{
 */
#define MOTION_OUT_PIN      GPIO_PIN(PC, 11)
/** @} */

/**
 * @brief   LCD chip select pin
 * @{
 */
#define LCD_CS_PIN          GPIO_PIN(PD, 15)
/** @} */

/**
 * @brief   LCD extcomin pin
 * @{
 */
#define LCD_EXTCOMIN_PIN    GPIO_PIN(PA, 2)
/** @} */

/**
 * @brief   GPIO to supply peripherals with vcc
 * @{
 */
#define PERIPH_VCC_PIN      GPIO_PIN(PF, 5)
/** @} */

/**
 * @brief   GPIO to supply LCD with vcc
 * @{
 */
#define LCD_VCC_PIN         GPIO_PIN(PA, 3)
/** @} */

/**
 * @brief   adc line for battery voltage
 * @{
 */
#define BATT_MEASS_LINE 2
/** @} */

/**
 * @brief   adc line for measure VDD voltage
 * @{
 */
#define VDD_MEASS_LINE 1
/** @} */

/**
 * @brief   adc line for internal temperature sensor
 * @{
 */
#define INTERNAL_TEMP_SENSOR_MEASS_LINE 0
/** @} */

/**
 * @brief   GPIO to activate / deactivate battery measurement
 * @{
 */
#define BATT_MEASS_ONOFF_PIN    GPIO_PIN(PB, 12)
/** @} */

// TODO Sensors

/**
 * @brief   Initialize the board (GPIO, sensors, clocks)
 */
void board_init(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
/** @} */
