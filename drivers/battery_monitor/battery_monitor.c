/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     drivers_battery_monitor
 * @{
 *
 * @file
 * @brief       Device driver implementation for Battery Monitor
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 *
 * @}
 */

#include "battery_monitor.h"
#include "battery_monitor_params.h"
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
    return (value * 2 * 5000 / 4095);
}

/*--------------------------------------------------------------------------*/

int battery_monitor_init(battery_monitor_t *dev,
                         const battery_monitor_params_t *params)
{
    /* Copy params into device params */
    dev->params = *params;

    /* Power battery monitor off */
    gpio_set(dev->params.on_off);

    /* ADC initialization */
    if (adc_init(dev->params.adc_line)) {
        return BATTERY_MONITOR_ERR_ADC;
    }

    return BATTERY_MONITOR_OK;
}

int16_t battery_monitor_read_voltage(battery_monitor_t *dev)
{
    /* Definition of the help variables */
    int16_t value;

    /* Read battery voltage */
    gpio_clear(dev->params.on_off);
    if ((value = adc_sample(dev->params.adc_line, ADC_RES_12BIT)) < 0) {
        return BATTERY_MONITOR_ERR_ADC;
    }
    gpio_set(dev->params.on_off);

    return voltage_conversion(value);
}
