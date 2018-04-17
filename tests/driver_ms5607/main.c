/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     tests
 * @{
 *
 * @file
 * @brief       Test application for the MS5607 temperature and
 *              air pressure sensor.
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 *
 * @}
 */

#include <stdio.h>

#include "ms5607_params.h"
#include "ms5607.h"
#include "xtimer.h"

#define MAINLOOP_DELAY (2 * 1000 * 1000u)

int main(void)
{
    ms5607_t dev;
    int result;

    puts("MS5607 test application\n");

    printf("+------------Initializing------------+\n");

    result = ms5607_init(&dev, &ms5607_params[0]);
    if (result == MS5607_ERR_I2C) {
        puts("[Error] The given i2c is not enabled");
        return 1;
    }
    if (result == MS5607_ERR_NODEV) {
        printf("[Error] The sensor did not answer correctly at address 0x%02X\n",
               ms5607_params[0].i2c_addr);
        return 1;
    }

    printf("Initialization successful\n");

    printf("\n+------------Calibration Data------------+\n");
    printf("C1: %u\n", dev.calibration.c1);
    printf("C2: %u\n", dev.calibration.c2);
    printf("C3: %u\n", dev.calibration.c3);
    printf("C4: %u\n", dev.calibration.c4);
    printf("C5: %u\n", dev.calibration.c5);
    printf("C6: %u\n", dev.calibration.c6);

    printf("\n+---------Starting Measurements---------+\n");
    while(1) {
        int32_t temperature;
        int32_t pressure;

        /* Get temperature in centi degrees Celsius */
        temperature = ms5607_read_temperature(&dev);
        bool negative = (temperature < 0);
        if (negative) {
            temperature = -temperature;
        }

        /* Get air pressure in Pa */
        pressure = ms5607_read_pressure(&dev);

        printf("Temperature [°C]:%c%ld.%ld\n"
               "Pressure [hPa]: %ld.%ld\n"
               "\n+---------------------------------------+\n",
               (negative) ? '-' : ' ',
               temperature / 100, temperature % 100,
               pressure / 100, pressure % 100);

        xtimer_usleep(MAINLOOP_DELAY);
    }

    return 0;
}
