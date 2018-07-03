/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_TK-MPRS06-LCD-A
 * @{
 *
 * @file
 * @brief       Config for board specific gpio
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 */

#ifndef GPIO_PARAMS_H
#define GPIO_PARAMS_H

#include "board.h"
#include "saul/periph.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   GPIO pin configuration
 */
static const saul_gpio_params_t saul_gpio_params[] =
{
    {
        .name = "LED",
        .pin = LED0_PIN,
        .mode = GPIO_OUT
    },
    {
        .name = "Button 0",
        .pin = BTN0_PIN,
        .mode = GPIO_IN_PU
    },
    {
        .name = "Button 1",
        .pin = BTN1_PIN,
        .mode = GPIO_IN_PU
    },
    {
        .name = "Button 2",
        .pin = BTN2_PIN,
        .mode = GPIO_IN_PU
    },
    {
        .name = "Button 3",
        .pin = BTN3_PIN,
        .mode = GPIO_IN_PU
    },
    {
        .name = "Button 4",
        .pin = BTN4_PIN,
        .mode = GPIO_IN_PU
    },
};

#ifdef __cplusplus
}
#endif

#endif /* GPIO_PARAMS_H */
/** @} */
