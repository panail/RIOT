/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup      drivers_battery_monitor
 *
 * @{
 * @file
 * @brief        Default configuration for Battery Monitor
 *
 * @author       Alexander Wihlelm <alexander.wilhelm@student.hs-rm.de>
 */

#ifndef BATTERY_MONITOR_PARAMS_H
#define BATTERY_MONITOR_PARAMS_H

#include "board.h"
#include "battery_monitor.h"
#include "saul_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    Set default configuration parameters for the Battery Monitor
 * @{
 */
#ifndef BATTERY_MONITOR_PARAM_ADC_LINE
#define BATTERY_MONITOR_PARAM_ADC_LINE              ADC_LINE(BATT_MEASS_LINE)
#endif
#ifndef BATTERY_MONITOR_PARAM_ON_OFF
#define BATTERY_MONITOR_PARAM_ON_OFF                BATT_MEASS_ONOFF_PIN
#endif

/* Defaults for Voltage Monitoring */
#define BATTERY_MONITOR_PARAMS_DEFAULT {                    \
    .adc_line = BATTERY_MONITOR_PARAM_ADC_LINE,             \
    .on_off = BATTERY_MONITOR_PARAM_ON_OFF,                 \
}
/** @} */

/**
 * @brief    Configure Battery Monitor
 */
static const battery_monitor_params_t battery_monitor_params[] = {
#ifdef BATTERY_MONITOR_PARAMS_BOARD
    BATTERY_MONITOR_PARAMS_BOARD,
#else
    BATTERY_MONITOR_PARAMS_DEFAULT
#endif
};

/**
 * @brief    The number of configured sensors
 */
#define BATTERY_MONITOR_NUMOF           (sizeof(battery_monitor_params) /       \
                                         sizeof(battery_monitor_params[0]))

/**
 * @brief    Configuration details of SAUL registry entries
 */
static const saul_reg_info_t battery_monitor_reg_info[BATTERY_MONITOR_NUMOF] = {
    { .name = "battery_monitor" }
};

#ifdef __cplusplus
}
#endif

#endif /* BATTERY_MONITOR_H */
