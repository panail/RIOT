/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     tests
 * @{
 *
 * @file
 * @brief       Test application for the M24512 EEPROM.
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 *
 * @}
 */

#include <stdio.h>

#include "m24512_params.h"
#include "m24512.h"
#include "xtimer.h"

#define MESSAGE_SIZE 256

int main(void)
{
    nvram_t dev;
    int result;
    uint8_t message[MESSAGE_SIZE];

    puts("M24512 test application\n");

    printf("+-------------Initializing-------------+\n");
    if (m24512_init(&dev, &m24512_params[0]) == M24512_ERR_I2C) {
        puts("[Error] The given i2c is not enabled");
        return 1;
    }

    printf("Initialization successful\n\n");

    for (size_t i = 0; i < MESSAGE_SIZE; i++) {
        message[i] = i;
    }
    xtimer_sleep(3);

    printf("\n+----------Writing into EEPROM----------+\n");
    result = dev.write(&dev, message, 0, MESSAGE_SIZE);
    if (result == M24512_ERR_I2C) {
        printf("[Error] The given i2c is not enabled");
        return 1;
    }
    if (result == M24512_ERR_NODEV) {
        printf("[Error] The given device is not on the i2c bus");
        return 1;
    }
    if (result == M24512_ERR_SIZEOV) {
        printf("[Error] The given size is greater than the EEPROM size");
        return 1;
    }
    printf("\n+----------Writing successful----------+\n");

    printf("\n+----------Reading from EEPROM----------+\n");
    result = dev.read(&dev, message, 0, MESSAGE_SIZE);
    if (result == M24512_ERR_I2C) {
        printf("[Error] The given i2c is not enabled");
        return 1;
    }
    if (result == M24512_ERR_NODEV) {
        printf("[Error] The given device is not on the i2c bus");
        return 1;
    }
    printf("\n+----------Reading successful----------+\n");

    printf("\n+---------Printing into terminal---------+\n");

    for (size_t i = 0; i < MESSAGE_SIZE; i++) {
        printf("Message %3u: %3u\n", i, message[i]);
    }

    return 0;
}
