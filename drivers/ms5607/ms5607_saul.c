/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     drivers_ms5607
 * @{
 *
 * @file
 * @brief       SAUL adaption for the MS5607 device
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 *
 * @}
 */

#include "saul.h"
#include "ms5607.h"

static int read_temperature(const void *dev, phydat_t *res)
{
    res->val[0] = ms5607_read_temperature((ms5607_t *)dev);
    res->unit = UNIT_TEMP_C;
    res->scale = -2;

    return 1;
}

static int read_pressure(const void *dev, phydat_t *res) {
    res->val[0] = ms5607_read_pressure((ms5607_t *)dev) / 100;
    res->unit = UNIT_PA;
    res->scale = 2;

    return 1;
}

const saul_driver_t ms5607_temperature_saul_driver = {
    .read = read_temperature,
    .write = saul_notsup,
    .type = SAUL_SENSE_TEMP,
};

const saul_driver_t ms5607_pressure_saul_driver = {
    .read = read_pressure,
    .write = saul_notsup,
    .type = SAUL_SENSE_PRESS
};
