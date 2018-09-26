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
 * @brief       Auto initialization of EFM32 Internal Temp Sensor driver.
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 *
 * @}
 */

#ifdef MODULE_EFM32_INTERNAL_TEMP_SENSOR

#include "log.h"
#include "saul_reg.h"

#include "efm32_internal_temp_sensor_params.h"
#include "efm32_internal_temp_sensor.h"

/**
 * @brief    Allocation of memory for device descriptors
 */
static efm32_internal_temp_sensor_t
    efm32_internal_temp_sensor_devs[EFM32_INTERNAL_TEMP_SENSOR_NUMOF];

/*
 * @brief    Memory for the SAUL registry entries
 */
static saul_reg_t saul_entries[EFM32_INTERNAL_TEMP_SENSOR_NUMOF];

/**
 * @brief    Reference the driver structs.
 * @{
 */
extern const saul_driver_t efm32_internal_temp_sensor_temperature_saul_driver;
/** @} */

void auto_init_efm32_internal_temp_sensor(void)
{
    for (size_t i = 0; i < EFM32_INTERNAL_TEMP_SENSOR_NUMOF; i++) {
        LOG_DEBUG("[auto_init_saul] initializing EFM32 Internal Temp Sensor #%u\n", i);
        int res = efm32_internal_temp_sensor_init(
            &efm32_internal_temp_sensor_devs[i],
            &efm32_internal_temp_sensor_params[i]);
        if (res < 0) {
            LOG_ERROR("[auto_init_saul] error initializing EFM32 Internal Temp Sensor #%i\n", i);
            continue;
        }

        /* temperature */
        saul_entries[i].dev = &efm32_internal_temp_sensor_devs[i];
        saul_entries[i].name = efm32_internal_temp_sensor_reg_info[i].name;
        saul_entries[i].driver = &efm32_internal_temp_sensor_temperature_saul_driver;
        saul_reg_add(&saul_entries[i]);
    }
}

#else
typedef int dont_be_pedantic;
#endif /* MODULE_EFM32_INTERNAL_TEMP_SENSOR */
