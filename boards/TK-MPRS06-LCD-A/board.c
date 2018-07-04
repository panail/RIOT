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
 * @brief       Board specific implementations for Thermokon board TK-MPRS06-LCD-A
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 *
 * @}
 */

#include "board.h"
#include "cpu.h"

#include "periph/gpio.h"
#include "periph/i2c.h"
#include "periph/adc.h"

#include "panic.h"

#include "bsp_trace.h"

void board_init(void)
{
    /* cpu init */
    cpu_init();

    /* enable SWO output pin for Energy Profiler TODO ifdef stuff */
    BSP_TraceProfilerSetup();

    /* init led */
    gpio_init(LED0_PIN, GPIO_OUT);

    /* init the buttons */
    gpio_init(BTN0_PIN, GPIO_IN);
    gpio_init(BTN1_PIN, GPIO_IN);
    gpio_init(BTN2_PIN, GPIO_IN);
    gpio_init(BTN3_PIN, GPIO_IN);
    gpio_init(BTN4_PIN, GPIO_IN);

    /* init motion out gpio */
    gpio_init(MOTION_OUT_PIN, GPIO_IN);

    /* init periph onoff / vcc supply gpio */
    gpio_init(PERIPH_VCC_PIN, GPIO_OUT);

    /* init lcd onoff / vcc supply gpio */
    gpio_init(LCD_VCC_PIN, GPIO_OUT);

    /* init battery measure onoff gpio */
    gpio_init(BATT_MEASS_ONOFF_PIN, GPIO_OUT);

    /* init battery measure adc */
    int ret = 0;

    ret = adc_init(BATT_MEASS_LINE);
    //assert(ret > 0);

    /* init internal VDD measure adc */
    ret = adc_init(VDD_MEASS_LINE);
    //assert(ret > 0);

    /* init internal temp sensor adc */
    ret = adc_init(INTERNAL_TEMP_SENSOR_MEASS_LINE);
    //assert(ret > 0);
    ret = ret;

    /* power on periphery supply */
    gpio_set(PERIPH_VCC_PIN);

    /* power on LCD supply */
    gpio_set(LCD_VCC_PIN);
    volatile uint32_t count = (1000 * (SystemCoreClock / 1000 / 1000)) / 2;
    while (count--) {}

    /* init i2c? */

    /* init spi? */

    /* init barometer sensor */

    /* init humidity sensor */

    /* init ambient light sensor */

    /* init pm? */

    /* init energy harverstin module? */

}
