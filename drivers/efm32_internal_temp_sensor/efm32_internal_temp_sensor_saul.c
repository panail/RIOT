/*
 * Copyright (C) Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     drivers_efm32_internal_temp_sensor
 * @{
 *
 * @file
 * @brief       SAUL adoption for EFM32 Internal Temp Sensor
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 *
 * @}
 */

#include "saul.h"

#include "efm32_internal_temp_sensor.h"

static int read_temperature(const void *dev, phydat_t *res)
{
    res->val[0] = efm32_internal_temp_sensor_read_temperature(
        (efm32_internal_temp_sensor_t *)dev);
    res->unit = UNIT_TEMP_C;
    res->scale = -2;

    return 1;
}

const saul_driver_t efm32_internal_temp_sensor_temperature_saul_driver = {
    .read = read_temperature,
    .write = saul_notsup,
    .type = SAUL_SENSE_TEMP,
};
