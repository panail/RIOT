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
 * @brief       Auto initialization of SHT35 driver.
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 *
 * @}
 */

#ifdef MODULE_SHT35

#include "log.h"
#include "saul_reg.h"

#include "sht35_params.h"
#include "sht35.h"

/**
 * @brief    Allocation of memory for device descriptors
 */
static sht35_t sht35_devs[SHT35_NUMOF];

/**
 * @brief    Memory for the SAUL registry entries
 */
static saul_reg_t saul_entries[SHT35_NUMOF * 2];

/**
 * @brief    Reference the driver structs.
 * @{
 */
extern const saul_driver_t sht35_temperature_saul_driver;
extern const saul_driver_t sht35_humidity_saul_driver;
/** @} */


void auto_init_sht35(void)
{
    size_t se_ix = 0;
    for (size_t i = 0; i < SHT35_NUMOF; i++) {
        LOG_DEBUG("[auto_init_saul] initializing SHT35 #%u\n", i);
        int res = sht35_init(&sht35_devs[i], &sht35_params[i]);
        if (res < 0) {
            LOG_ERROR("[auto_init_saul] error initializing SHT35 #%i\n", i);
            continue;
        }

        /* temperature */
        saul_entries[se_ix].dev = &sht35_devs[i];
        saul_entries[se_ix].name = sht35_saul_reg_info[i].name;
        saul_entries[se_ix].driver = &sht35_temperature_saul_driver;
        saul_reg_add(&saul_entries[se_ix]);
        se_ix++;

        /* relative humidity */
        saul_entries[se_ix].dev = &sht35_devs[i];
        saul_entries[se_ix].name = sht35_saul_reg_info[i].name;
        saul_entries[se_ix].driver = &sht35_humidity_saul_driver;
        saul_reg_add(&saul_entries[se_ix]);
        se_ix++;
    }
}

#else
typedef int dont_be_pedantic;
#endif /* MODULE_SHT35 */
