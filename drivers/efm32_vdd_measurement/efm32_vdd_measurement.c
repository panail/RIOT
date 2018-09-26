/*
 * Copyright (C) 2018 Hochschule RheinMain
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
 * @brief       Device driver implementation for EFM32 VDD Measurement
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 *
 * @}
 */

#include "efm32_vdd_measurement.h"
#include "efm32_vdd_measurement_params.h"
#include "periph/adc.h"

/**
 * @brief    Perform voltage conversion
 *
 * @param[in]  value       Measured voltage value
 *
 * @return                 Voltage value in mV
 */
static inline int16_t voltage_conversion(int value);

/*--------------------------------------------------------------------------*/

static inline int16_t voltage_conversion(int value)
{
    return (value * 5000 / 4095);
}

/*--------------------------------------------------------------------------*/

int efm32_vdd_measurement_init(
        efm32_vdd_measurement_t *dev,
        const efm32_vdd_measurement_params_t * params)
{
    /* Copy params into device params */
    dev->params = *params;

    /* ADC initialization */
    if (adc_init(dev->params.adc_line)) {
        return EFM32_VDD_MEASUREMENT_ERR_ADC;
    }

    return EFM32_VDD_MEASUREMENT_OK;
}

int16_t efm32_vdd_measurement_read_voltage(efm32_vdd_measurement_t *dev)
{
    /* Definition of the help variables */
    int16_t value;

    /* Read VDD voltage */
    if ((value = adc_sample(dev->params.adc_line, ADC_RES_12BIT)) < 0) {
        return EFM32_VDD_MEASUREMENT_ERR_ADC;
    }

    return voltage_conversion(value);
}
