/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     auto_init_saul
 * @{
 *
 * @file
 * @brief       Auto initialization of Battery Monitor driver.
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 *
 * @}
 */

#ifdef MODULE_BATTERY_MONITOR

#include "log.h"
#include "saul_reg.h"

#include "battery_monitor_params.h"
#include "battery_monitor.h"

/**
 * @brief    Allocation of memory for device descriptors
 */
static battery_monitor_t battery_monitor_devs[BATTERY_MONITOR_NUMOF];

/**
 * @brief    Memory for the SAUL registry entries
 */
static saul_reg_t saul_entries[BATTERY_MONITOR_NUMOF];

/**
 * @brief    Reference the driver structs.
 * @{
 */
extern const saul_driver_t battery_monitor_voltage_saul_driver;
/** @} */

void auto_init_battery_monitor(void)
{
    for(size_t i = 0; i < BATTERY_MONITOR_NUMOF; i++) {
        LOG_DEBUG("[auto_init_saul] initializing Battery Monitor #%u\n", i);
        int res = battery_monitor_init(&battery_monitor_devs[i],
                                       &battery_monitor_params[i]);
        if (res < 0) {
            LOG_ERROR("[auto_init_saul] error initializing Battery Monitor #%i\n", i);
            continue;
        }

        /* voltage */
        saul_entries[i].dev = &battery_monitor_devs[i];
        saul_entries[i].name = battery_monitor_reg_info[i].name;
        saul_entries[i].driver = &battery_monitor_voltage_saul_driver;
        saul_reg_add(&saul_entries[i]);
    }
}

#else
typedef int dont_be_pedantic;
#endif /* MODULE_BATTERY_MONITOR */
