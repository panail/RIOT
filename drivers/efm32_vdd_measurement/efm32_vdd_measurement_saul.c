/*
 * Copyright (C) Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     drivers_efm32_vdd_measurement
 * @{
 *
 * @file
 * @brief       SAUL adoption for EFM32 VDD Measurement.
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 *
 * @}
 */

#include "saul.h"

#include "efm32_vdd_measurement.h"

static int read_voltage(const void *dev, phydat_t *res)
{
    res->val[0] = efm32_vdd_measurement_read_voltage((efm32_vdd_measurement_t *)dev) / 10;
    res->unit = UNIT_V;
    res->scale = -2;

    return 1;
}

const saul_driver_t efm32_vdd_measurement_voltage_saul_driver = {
    .read = read_voltage,
    .write = saul_notsup,
    .type = SAUL_SENSE_ANALOG,
};
