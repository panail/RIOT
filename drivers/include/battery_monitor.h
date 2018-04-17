/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    drivers_battery_monitor Battery Monitor
 * @ingroup     drivers_sensors
 * @brief       Device driver interface for Battery Monitor using ADC.
 *
 * Battery Monitor measure voltage in mV.
 *
 * @{
 * @file
 * @brief       Device driver interface for Battery Monitor.
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 */

#ifndef BATTERY_MONITOR_H
#define BATTERY_MONITOR_H

#include "saul.h"
#include "periph/adc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief    Parameter for Battery Monitor
 *
 * These parameters are needed to configure the device at startup
 */
typedef struct {
    /* ADC details */
    adc_t adc_line;                             /**< ADC line which is used */
    gpio_t on_off;                              /**< GPIO used to turn measure ON/OFF */
} battery_monitor_params_t;

/**
 * @brief    Device descriptor for the Battery Monitor
 */
typedef struct {
    battery_monitor_params_t params;            /**< Device parameters */
} battery_monitor_t;

/**
 * @brief    Status and error return codes
 */
enum {
    BATTERY_MONITOR_OK      =  0,               /**< everything was fine */
    BATTERY_MONITOR_ERR_ADC = -1,               /**< error on the ADC */
};

/**
 * @brief    Initialize the given Battery Monitor device
 *
 * @param[out] dev         Initialized device descriptor of Battery Monitor
 * @param[in]  params      The parameters for the Battery Monitor device
 *
 * @return                 BATTERY_MONITOR_OK on success
 * @return                 BATTERY_MONITOR_ERR_ADC on error
 */
int battery_monitor_init(battery_monitor_t *dev,
                         const battery_monitor_params_t *params);

/**
 * @brief    Read voltage value from the given Battery Monitor device,
 *           returned in mV
 *
 * @param[in]  dev          Device descriptor of Battery Monitor device to read from
 *
 * @returns                 The voltage in mV.
 */
int16_t battery_monitor_read_voltage(battery_monitor_t *dev);

#ifdef __cplusplus
}
#endif

#endif /* BATTERY_MONITOR_H */
/** @} */
