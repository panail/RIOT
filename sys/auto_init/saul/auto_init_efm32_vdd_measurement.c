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
 * @brief       Auto initialization of EFM32 VDD Measurement driver.
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 *
 * @}
 */

#ifdef MODULE_EFM32_VDD_MEASUREMENT

#include "log.h"
#include "saul_reg.h"

#include "efm32_vdd_measurement_params.h"
#include "efm32_vdd_measurement.h"

/**
 * @brief    Allocation of memory for device descriptors
 */
static efm32_vdd_measurement_t efm32_vdd_measurement_devs[EFM32_VDD_MEASUREMENT_NUMOF];

/**
 * @brief    Memory for the SAUL registry entries
 */
static saul_reg_t saul_entries[EFM32_VDD_MEASUREMENT_NUMOF];

/**
 * @brief    Reference the driver structs.
 * @{
 */
extern const saul_driver_t efm32_vdd_measurement_voltage_saul_driver;
/** @} */

void auto_init_efm32_vdd_measurement(void)
{
    for(size_t i = 0; i < EFM32_VDD_MEASUREMENT_NUMOF; i++) {
        LOG_DEBUG("[auto_init_saul] initializing EFM32 VDD Measurement #%u\n", i);
        int res = efm32_vdd_measurement_init(&efm32_vdd_measurement_devs[i],
                                             &efm32_vdd_measurement_params[i]);
        if (res < 0) {
            LOG_ERROR("[auto_init_saul] error initializing EFM32 VDD Measurement #%i\n", i);
            continue;
        }

        /* voltage */
        saul_entries[i].dev = &efm32_vdd_measurement_devs[i];
        saul_entries[i].name = efm32_vdd_measurement_reg_info[i].name;
        saul_entries[i].driver = &efm32_vdd_measurement_voltage_saul_driver;
        saul_reg_add(&saul_entries[i]);
    }
}

#else
typedef int dont_be_pedantic;
#endif /* MODULE_EFM32_VDD_MEASUREMENT */
