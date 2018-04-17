/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     drivers_ms5607
 *
 * @{
 * @file
 * @brief       Default configuration for the MS5607
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 */

#ifndef MS5607_PARAMS_H
#define MS5607_PARAMS_H

#include "board.h"
#include "ms5607.h"
#include "saul_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    Set default configuration parameters for the MS5607
 * @{
 */
#ifndef MS5607_PARAM_I2C_DEV
#define MS5607_PARAM_I2C_DEV         I2C_DEV(0)
#endif
#ifndef MS5607_PARAM_I2C_ADDR
#define MS5607_PARAM_I2C_ADDR       0x77
#endif

/* Defaults for Weather Monitoring */
#define MS5607_PARAMS_DEFAULT {                \
    .i2c_dev  = MS5607_PARAM_I2C_DEV,          \
    .i2c_addr = MS5607_PARAM_I2C_ADDR,         \
    .temp_osr = MS5607_OSR_4096,               \
    .pres_osr = MS5607_OSR_4096,               \
}
/** @} */

/**
 * @brief    Configure MS5607
 */
static const ms5607_params_t ms5607_params[] = {
#ifdef MS5607_PARAMS_BOARD
    MS5607_PARAMS_BOARD,
#else
    MS5607_PARAMS_DEFAULT,
#endif
};

/**
 * @brief    The number of configured sensor
 */
#define MS5607_NUMOF    (sizeof(ms5607_params) / sizeof(ms5607_params[0]))

/**
 * @brief    Configure SAUL registry entries
 */
static const saul_reg_info_t ms5607_saul_reg_info[] = {
    { .name = "ms5607" }
};

#ifdef __cplusplus
}
#endif

#endif /* MS5607_PARAMS_H */
/** @} */
