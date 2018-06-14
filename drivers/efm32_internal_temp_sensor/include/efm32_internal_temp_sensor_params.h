/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     drivers_efm32_internal_temp_sensor
 *
 * @{
 * @file
 * @brief       Default configuration for EFM32 Internal Temp Sensor
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 */

#ifndef EFM32_INTERNAL_TEMP_SENSOR_PARAMS_H
#define EFM32_INTERNAL_TEMP_SENSOR_PARAMS_H

#include "board.h"
#include "efm32_internal_temp_sensor.h"
#include "saul_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    Set default configuration parameter for the EFM32 Internal Temp Sensor
 * @{
 */
#ifndef EFM32_INTERNAL_TEMP_SENSOR_PARAM_ADC_LINE
#define EFM32_INTERNAL_TEMP_SENSOR_PARAM_ADC_LINE                       \
    ADC_LINE(INTERNAL_TEMP_SENSOR_MEASS_LINE)
#endif

/**
 * @name    Default for Temperature Monitoring */
#define EFM32_INTERNAL_TEMP_SENSOR_PARAMS_DEFAULT {                     \
    .adc_line = EFM32_INTERNAL_TEMP_SENSOR_PARAM_ADC_LINE,              \
}
/** @} */

/**
 * @brief    Configure EFM32 Internal Temp Sensor
 */
static const efm32_internal_temp_sensor_params_t
    efm32_internal_temp_sensor_params[] = {
#ifdef EFM32_INTERNAL_TEMP_SENSOR_PARAMS_BOARD
        EFM32_INTERNAL_TEMP_SENSOR_PARAMS_BOARD,
#else
        EFM32_INTERNAL_TEMP_SENSOR_PARAMS_DEFAULT
#endif
};

/**
 * @brief    The number of configured sensors
 */
#define EFM32_INTERNAL_TEMP_SENSOR_NUMOF (                              \
    sizeof(efm32_internal_temp_sensor_params) /                         \
    sizeof(efm32_internal_temp_sensor_params[0])                        \
)

/**
 * @brief    Configuration details of SAUL registry entries
 */
static const saul_reg_info_t
    efm32_internal_temp_sensor_reg_info[EFM32_INTERNAL_TEMP_SENSOR_NUMOF] = {
        { .name = "efm32_internal_temp_sensor" }
};

#ifdef __cplusplus
}
#endif

#endif /* EFM32_INTERNAL_TEMP_SENSOR_PARAMS_H */
