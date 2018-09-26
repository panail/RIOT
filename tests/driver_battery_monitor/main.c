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
 * @brief       Test application for the Battery Monitor using ADC.
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 *
 * @}
 */

#include <stdio.h>

#include "battery_monitor_params.h"
#include "battery_monitor.h"
#include "xtimer.h"

#define MAINLOOP_DELAY (2 * 1000 * 1000u)

int main(void)
{
    battery_monitor_t dev;
    int16_t result;

    puts("Battery Monitor test application\n");

    printf("\n+-----------Initializing-------------+\n");

    result = battery_monitor_init(&dev, &battery_monitor_params[0]);
    if (result == BATTERY_MONITOR_ERR_ADC) {
        puts("[Error] The given ADC line is not enabled");
        return 1;
    }

    printf("Initialization successful\n");

    printf("\n+---------Starting Measurements---------+\n");
    while (1) {
        int16_t voltage;

        /* Get voltage in mV */
        voltage = battery_monitor_read_voltage(&dev);

        printf("Voltage [V]: %d.%d\n"
               "\n+---------------------------------------+\n",
               voltage / 1000, (voltage % 1000) / 10);

        xtimer_usleep(MAINLOOP_DELAY);
    }

    return 0;
}
