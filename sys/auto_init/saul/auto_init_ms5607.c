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
 * @brief       Auto initialization of MS5607 driver.
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 *
 * @}
 */

#ifdef MODULE_MS5607

#include "log.h"
#include "saul_reg.h"

#include "ms5607_params.h"
#include "ms5607.h"

/**
 * @brief    Allocation of memory for device descriptors
 */
static ms5607_t ms5607_devs[MS5607_NUMOF];

/**
 * @brief    Memory for the SAUL registry entries
 */
static saul_reg_t saul_entries[MS5607_NUMOF * 2];

/**
 * @brief    Reference the driver structs
 * @{
 */
extern const saul_driver_t ms5607_temperature_saul_driver;
extern const saul_driver_t ms5607_pressure_saul_driver;
/** @} */

void auto_init_ms5607(void)
{
    size_t se_ix = 0;
    for (size_t i = 0; i < MS5607_NUMOF; i++) {
        LOG_DEBUG("[auto_init_saul] initializing MS5607 #%u\n", i);
        int res = ms5607_init(&ms5607_devs[i], &ms5607_params[i]);
        if (res < 0) {
            LOG_ERROR("[auto_init_saul] error initializing MS5607 #%i\n", i);
            continue;
        }

        /* temperature */
        saul_entries[se_ix].dev = &ms5607_devs[i];
        saul_entries[se_ix].name = ms5607_saul_reg_info[i].name;
        saul_entries[se_ix].driver = &ms5607_temperature_saul_driver;
        saul_reg_add(&saul_entries[se_ix]);
        se_ix++;

        /* pressure */
        saul_entries[se_ix].dev = &ms5607_devs[i];
        saul_entries[se_ix].name = ms5607_saul_reg_info[i].name;
        saul_entries[se_ix].driver = &ms5607_pressure_saul_driver;
        saul_reg_add(&saul_entries[se_ix]);
        se_ix++;
    }
}

#else
typedef int dont_be_pedantic;
#endif /* MODULE_MS5607 */
