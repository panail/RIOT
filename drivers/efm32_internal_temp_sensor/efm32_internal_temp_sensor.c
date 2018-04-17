/*
 * Copyright (C) 2018 Hoschule RheinMai
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
 * @brief       Device driver implementation for EFM32 Internal Temp Sensor
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 *
 * @}
 */

#include "efm32_internal_temp_sensor.h"
#include "efm32_internal_temp_sensor_params.h"
#include "periph/adc.h"

/**
 * @brief    Perform temperature conversion
 *
 * @param[in]  value         Measured temperature value
 *
 * @return                   Temperature value in c°C
 */
static inline int16_t temperature_conversion(int value);

/*--------------------------------------------------------------------------*/

static inline int16_t temperature_conversion(int value)
{
    /* Definition of the help variables */
    int32_t cal_temp;
    int32_t cal_value;

    /* Read calibration values from the chip */
    cal_temp = ((DEVINFO->CAL & _DEVINFO_CAL_TEMP_MASK) >> _DEVINFO_CAL_TEMP_SHIFT);
    cal_value = ((DEVINFO->ADC0CAL3 & 0xFFF0) >> _DEVINFO_ADC0CAL3_TEMPREAD1V25_SHIFT);

    return (cal_temp * 100 - (cal_value - value) * 12500000 / (4096 * (-184)));
}

/*--------------------------------------------------------------------------*/

int efm32_internal_temp_sensor_init(
        efm32_internal_temp_sensor_t *dev,
        const efm32_internal_temp_sensor_params_t *params)
{
    /* Copy params into device params */
    dev->params = *params;

    /* ADC initialization */
    if (adc_init(dev->params.adc_line)) {
        return EFM32_INTERNAL_TEMP_SENSOR_ERR_ADC;
    }

    return EFM32_INTERNAL_TEMP_SENSOR_OK;
}

int16_t efm32_internal_temp_sensor_read_temperature(
        efm32_internal_temp_sensor_t *dev)
{
    /* Definition of the help variables */
    int16_t value;

    /* Read temperature */
    if ((value = adc_sample(dev->params.adc_line, ADC_RES_12BIT)) < 0) {
        return EFM32_INTERNAL_TEMP_SENSOR_ERR_ADC;
    }

    return temperature_conversion(value);
}
