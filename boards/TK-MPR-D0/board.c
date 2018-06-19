/*
 * Copyright (C) 2017 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_TK-MPRS01-A
 * @{
 *
 * @file
 * @brief       Board specific implementations for Thermokon
 * board  TK-MPRS01-A
 *
 * @author      Kai Beckmann <kai.beckmann@hs-rm.de> 
 *
 * @}
 */

#include "board.h"
#include "board_common.h"
#include "periph/gpio.h"
#include "periph/i2c.h"
#include "periph/adc.h"

#include "panic.h"

#include "bsp_trace.h"

void board_init(void)
{
    /* initialize the CPU */
    cpu_init();

    /* perform common board initialization */
    board_common_init();

    /* init led, done in common_init */
    //gpio_init(LED0_PIN, GPIO_OUT);

    gpio_init(LED_LRN_PIN, GPIO_OUT);
    gpio_init(LED_PRG_PIN, GPIO_OUT);

    /* init the button, done in common_init */
   // gpio_init(PB0_PIN, GPIO_IN);
    gpio_init(BTN_LRN_PIN, GPIO_IN);
    gpio_init(BTN_PRG_PIN, GPIO_IN);

    /* init reed contact gpio */
    gpio_init(RELAIS_PIN, GPIO_OUT);





    /* init battery measure adc */
    int ret = 0;


  //  assert(ret > 0);

    /* init internal VDD measure adc */
    ret = adc_init(VDD_MEASS_LINE);
  //  assert(ret > 0);

    /* init internal temp sensor adc */
    ret = adc_init(INTERNAL_TEMP_SENSOR_MEASS_LINE);
  //  assert(ret > 0);
    ret = ret;

    /* init i2c? */

    /* init barometer sensor */

    /* init humility sensor */

    /* init pm? */

    /* init energy harvesting module? */

}
