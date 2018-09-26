/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    drivers_efm32_internal_temp_sensor                       \
 *              EFM32 Internal Temp Sensor
 * @ingroup     drivers_sensors
 * @brief       Device driver interface for Temperature Measurement using ADC.
 *
 * EFM32 Internal Temp Sensor measure temperature in c°C.
 *
 * @{
 * @file
 * @brief       Device driver interface for Temperature Measurement.
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 */

#ifndef EFM32_INTERNAL_TEMP_SENSOR
#define EFM32_INTERNAL_TEMP_SENSOR

#include "saul.h"
#include "periph/adc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief    Parameter for EFM32 Internal Temp Sensor
 *
 * These parameters are needed to configure the device at startup
 */
typedef struct {
    /* ADC details */
    adc_t adc_line;                                         /**< ADC line which is used */
} efm32_internal_temp_sensor_params_t;

/**
 * @brief    Device descriptor for the EFM32 Internal Temp Sensor
 */
typedef struct {
    efm32_internal_temp_sensor_params_t params;             /**< Device parameters */
} efm32_internal_temp_sensor_t;

/**
 * @brief    Status and error return codes
 */
enum {
    EFM32_INTERNAL_TEMP_SENSOR_OK      =  0,                /**< everything was fine */
    EFM32_INTERNAL_TEMP_SENSOR_ERR_ADC = -1,                /**< error on the ADC */
};

/**
 * @brief    Initialize the given EFM32 Internal Temp Sensor device
 *
 * @param[out] dev         Initialized device descriptor of EFM32 Internal Temp Sensor
 * @param[in]  params      The parameters for the EFM32 Internal Temp sensor device
 *
 * @return                 EFM32_INTERNAL_TEMP_SENSOR_OK on success
 */
int efm32_internal_temp_sensor_init(
    efm32_internal_temp_sensor_t *dev,
    const efm32_internal_temp_sensor_params_t *params
);

/**
 * @brief    Read temperature value for the given EFM32 Internal
 *           Temp Sensor device, return in c°C (centi)
 *
 * @param[in]  dev         Device descriptor of EFM32 Internal
 *                         Temp Sensor device to read from
 *
 * @returns                The temperature in c°C.
 */
int16_t efm32_internal_temp_sensor_read_temperature(
    efm32_internal_temp_sensor_t *dev
);

#ifdef __cplusplus
}
#endif

#endif /* EFM32_INTERNAL_TEMP_SENSOR_H */
/** @} */
