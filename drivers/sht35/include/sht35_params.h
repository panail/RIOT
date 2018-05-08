/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup      drivers_sht35
 *
 * @{
 * @file
 * @brief        Default configuration for SHT35
 *
 * @author       Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 */

#ifndef SHT35_PARAMS_H
#define SHT35_PARAMS_H

#include "board.h"
#include "sht35.h"
#include "saul_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    Set default configuration parameters for the SHT35
 * @{
 */
#ifndef SHT35_PARAM_I2C_DEV
#define SHT35_PARAM_I2C_DEV         I2C_DEV(0)
#endif
#ifndef SHT35_PARAM_I2C_ADDR
#define SHT35_PARAM_I2C_ADDR        (0x44)
#endif

/* Defaults for Weather Monitoring */
#define SHT35_PARAMS_DEFAULT {              \
    .i2c_dev = SHT35_PARAM_I2C_DEV,         \
    .i2c_addr = SHT35_PARAM_I2C_ADDR,       \
    .rep = SHT35_HIGH_REP,                  \
}
/** @} */

/**
 * @brief    Configure SHT35
 */
static const sht35_params_t sht35_params[] = {
#ifdef SHT35_PARAMS_BOARD
    SHT35_PARAMS_BOARD,
#else
    SHT35_PARAMS_DEFAULT
#endif
};

/**
 * @brief    The number of configured sensors
 */
#define SHT35_NUMOF    (sizeof(sht35_params) / sizeof(sht35_params[0]))

/**
 * @brief    Configuration details of SAUL registry entries
 */
static const saul_reg_info_t sht35_saul_reg_info[SHT35_NUMOF] = {
    { .name = "sht35" }
};

#ifdef __cplusplus
}
#endif

#endif /* SHT35_PARAMS_H */
/** @} */
