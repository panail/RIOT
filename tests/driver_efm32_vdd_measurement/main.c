/*
 * Copyright (C) Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details:
 */

/**
 * @ingroup     tests
 *
 * @file
 * @brief       Test application for the EFM32 VDD Measurement using ADC.
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 *
 * @}
 */

#include <stdio.h>

#include "efm32_vdd_measurement_params.h"
#include "efm32_vdd_measurement.h"
#include "xtimer.h"

#define MAINLOOP_DELAY (2 * 1000 * 1000u)

int main(void)
{
    efm32_vdd_measurement_t dev;
    int result;

    puts("EFM32 VDD Measurement test application\n");

    printf("\n+-------------Initializing-------------+\n");

    result = efm32_vdd_measurement_init(&dev, &efm32_vdd_measurement_params[0]);
    if (result == EFM32_VDD_MEASUREMENT_ERR_ADC) {
        puts("[Error] The given ADC line is not enabled");
        return 1;
    }

    printf("Initialization successful\n");

    printf("\n+---------Starting Measurements---------+\n");
    while(1) {
        int16_t voltage;

        /* Get voltage in mV */
        voltage = efm32_vdd_measurement_read_voltage(&dev);

        printf("Voltage [V]: %d.%d\n"
               "\n+---------------------------------------+\n",
               voltage / 1000, (voltage % 1000) / 10);

        xtimer_usleep(MAINLOOP_DELAY);
    }

    return 0;
}
