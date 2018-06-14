/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     tests
 *
 * @file
 * @brief       Test application for the EFM32 Internal Temp Sensor device.
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 *
 * @}
 */

#include <stdio.h>

#include "efm32_internal_temp_sensor_params.h"
#include "efm32_internal_temp_sensor.h"
#include "xtimer.h"

#define MAINLOOP_DELAY (2 * 1000 * 1000u)

int main(void)
{
    efm32_internal_temp_sensor_t dev;
    int result;

    puts("EFM32 Internal Temp Sensor test applicatioin\n");

    printf("\n+-------------Initializing-------------+\n");

    result = efm32_internal_temp_sensor_init(&dev, &efm32_internal_temp_sensor_params[0]);
    if (result == EFM32_INTERNAL_TEMP_SENSOR_ERR_ADC) {
        puts("[Error] The given ADC line is not enabled");
        return 1;
    }

    printf("Initialization successful\n");

    printf("\n+---------Starting Measurements---------+\n");
    while (1) {
        int16_t temperature;

        /* Get temperature in centi degrees Celcius */
        temperature = efm32_internal_temp_sensor_read_temperature(&dev);
        bool negative = (temperature < 0);
        if (negative) {
            temperature = -temperature;
        }

        printf("Temperature [°C]:%c%d.%d\n"
               "\n+---------------------------------------+\n",
               (negative) ? '-' : ' ',
               temperature / 100, temperature % 100);

        xtimer_usleep(MAINLOOP_DELAY);
    }

    return 0;
}
