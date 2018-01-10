/*
 * Copyright (C) 2018 Feie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    boards_ruuvitag RuuviTag
 * @ingroup     boards
 * @brief       Board specific configuration for the RuuviTag board
 * @{
 *
 * @file
 * @brief       Board specific configuration for the RuuviTag board
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 */

#ifndef BOARD_H
#define BOARD_H

#include "cpu.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    LED pin configuration
 * @{
 */
#define LED0_PIN            GPIO_PIN(0, 17)
#define LED1_PIN            GPIO_PIN(0, 19)

#define LED_PORT            NRF_P0
#define LED0_MASK           (1 << 17)
#define LED1_MASK           (1 << 19)
#define LED_MASK            (LED0_MASK | LED1_MASK)

#define LED0_ON             (LED_PORT->OUTCLR = LED0_MASK)
#define LED0_OFF            (LED_PORT->OUTSET = LED0_MASK)
#define LED0_TOGGLE         (LED_PORT->OUT   ^= LED0_MASK)

#define LED1_ON             (LED_PORT->OUTCLR = LED1_MASK)
#define LED1_OFF            (LED_PORT->OUTSET = LED1_MASK)
#define LED1_TOGGLE         (LED_PORT->OUT   ^= LED1_MASK)
/** @} */

/**
 * @name    Button pin configuration
 * @{
 */
#define BTN0_PIN            GPIO_PIN(0, 13)
#define BTN0_MODE           GPIO_IN_PU
/** @} */

/**
 * @name    Environmental sensor configuration (Bosch BMX280)
 * @{
 */
#define BMX280_PARAM_CS     GPIO_PIN(0, 3)
/** @} */

/**
 * @name    Accelerometer configuration
 * @{
 */
#define LIS2DH12_PARAM_CS   GPIO_PIN(0, 8)
#define LIS2DH12_PARAM_INT1 GPIO_PIN(0, 2)
#define LIS2DH12_PARAM_INT2 GPIO_PIN(0, 6)
/** @} */

/**
 * @brief   Initialize board specific hardware
 */
void board_init(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
/** @} */
