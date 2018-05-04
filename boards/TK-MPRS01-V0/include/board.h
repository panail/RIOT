/*
 * Copyright (C) 2017 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    boards_TK-MPRS01-V0 Thermokon window contact
 * @ingroup     boards
 * @brief       Support for the Thermokon MPRS01-V0 pre version
 * @{
 *
 * @file
 * @brief       Board specific definitions for the Thermokon MPRS01-V0 model a
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
 * @name    Enable Advanced Energy Monitor
 *
 * When enabled, additional CPU statistics are available via SWO.
 * @{
 */
#ifndef AEM_ENABLED
#define AEM_ENABLED         (1)
#endif
/** @} */

/**
 * @brief   Push button pin definitions.
 * @{
 */
#define BTN0_PIN            GPIO_PIN(PD, 14)
/** @} */

/**
 * @brief    LED pin definitions.
 * @{
 */
#define LED0_PIN            GPIO_PIN(PC, 10)
/** @} */

/**
 * @brief   Macros for controlling the on-board LEDs.
 * @{
 */
#define LED0_ON             gpio_set(LED0_PIN)
#define LED0_OFF            gpio_clear(LED0_PIN)
#define LED0_TOGGLE         gpio_toggle(LED0_PIN)
/** @} */

/**
 * @brief   Reed contact
 * @{
 */
#define REED_CONTACT_PIN    GPIO_PIN(PF, 7)
/** @} */

 /**
 * @brief   GPIO to suply peripherals with vcc
 * @{
 */
#define PERIPH_VCC_PIN    GPIO_PIN(PC, 11)
/** @} */

 /**
 * @brief   adc line for battery voltage
 * @{
 */
#define BATT_MEASS_LINE    2
/** @} */

/**
 * @brief   adc line for measure VDD voltage
 * @{
 */
#define VDD_MEASS_LINE    1
/** @} */

 /**
 * @brief   adc line for internal temperature sensor
 * @{
 */
#define INTERNAL_TEMP_SENSOR_MEASS_LINE    0
/** @} */

/**
 * @brief   GPO to activate / deactive battary measurement
 * @{
 */
#define BATT_MEASS_ONOFF_PIN    GPIO_PIN(PB, 12)
/** @} */

/**
 * @brief   Pin for communication with the Power & Interrupt Controller.
 * @{
 */
#define PIC_INT_WAKE_PIN    GPIO_PIN(PD, 10)
#define PIC_I2C             (0)
#define PIC_I2C_ADDR        (0x90)
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
