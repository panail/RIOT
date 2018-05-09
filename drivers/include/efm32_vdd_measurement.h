/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    drivers_efm32_vdd_measurement EFM32 VDD Measurement
 * @ingroup     drivers_sensors
 * @brief       Device driver interface for EFM32 VDD Measurement using ADC.
 *
 * EFM32 VDD Measurement measure voltage in mV.
 *
 * @{
 * @file
 * @brief       Device driver interface for EFM32 VDD Measurement.
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 */

#ifndef EFM32_VDD_MEASUREMENT_H
#define EFM32_VDD_MEASUREMENT_H

#include "saul.h"
#include "periph/adc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief    Parameter for EFM32 VDD Measurement
 *
 * These parameters are needed to configure the device at startup
 */
typedef struct {
    /* ADC details */
    adc_t adc_line;                                     /**< ADC line which is used */
} efm32_vdd_measurement_params_t;

/**
 * @brief    Device descriptor for the EFM32 VDD Measurement
 */
typedef struct {
    efm32_vdd_measurement_params_t params;              /**< Device parameters */
} efm32_vdd_measurement_t;

/**
 * @brief    Status and error return codes
 */
enum {
    EFM32_VDD_MEASUREMENT_OK      =  0,                 /**< everything was fine */
    EFM32_VDD_MEASUREMENT_ERR_ADC = -1,                 /**< error on the ADC */
};

/**
 * @brief    Initialize the given EFM32 VDD Measurement device
 *
 * @param[out] dev         Initialized device descriptor of EFM32 VDD Measurement
 * @param[in]  params      The parameters for the EFM32 VDD Measurement device
 *
 * @return                 EFM32_VDD_MEASUREMENT_OK on success
 */
int efm32_vdd_measurement_init(
        efm32_vdd_measurement_t *dev,
        const efm32_vdd_measurement_params_t *params);

/**
 * @brief    Read voltage value from the given EFM32 VDD Measurement device,
 *           returned in mV
 *
 * @param[in]  dev          Device descriptor of EFM32 VDD Measurement device to read from
 *
 * @returns                 The voltage in mV.
 */
int16_t efm32_vdd_measurement_read_voltage(efm32_vdd_measurement_t *dev);

#ifdef __cplusplus
}
#endif

#endif /* EFM32_VDD_MEASUREMENT_H */
/** @} */
