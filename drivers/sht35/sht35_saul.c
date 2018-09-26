/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     drivers_sht35
 * @{
 *
 * @file
 * @brief       SAUL adoption for SHT35 sensor.
 *
 * @author      Alexander Wihelm <alexander.wilhelm@student.hs-rm.de>
 *
 * @}
 */

#include "saul.h"

#include "sht35.h"

static int read_temperature(const void *dev, phydat_t *res)
{
    res->val[0] = sht35_read_temperature((sht35_t *)dev);
    res->unit = UNIT_TEMP_C;
    res->scale = -2;

    return 1;
}

static int read_humidity(const void *dev, phydat_t *res)
{
    res->val[0] = sht35_read_humidity((const sht35_t *)dev);
    res->unit = UNIT_PERCENT;
    res->scale = -2;

    return 1;
}

const saul_driver_t sht35_temperature_saul_driver = {
    .read = read_temperature,
    .write = saul_notsup,
    .type = SAUL_SENSE_TEMP,
};

const saul_driver_t sht35_humidity_saul_driver = {
    .read = read_humidity,
    .write = saul_notsup,
    .type = SAUL_SENSE_HUM,
};
