/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup      drivers_m24512
 *
 * @{
 * @file
 * @brief        Default configuration for M24512
 *
 * @author       Alexander Wilhelm <alexander.wilhem@student.hs-rm.de>
 */

#ifndef M24512_PARAMS_H
#define M24512_PARAMS_H

#include "board.h"
#include "m24512.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    Set default configuration parameters for the M24512
 * @{
 */
#ifndef M24512_PARAM_I2C_DEV
#define M24512_PARAM_I2C_DEV           I2C_DEV(0)
#endif
#ifndef M24512_PARAM_I2C_ADDR
#define M24512_PARAM_I2C_ADDR          (0x50)
#endif

/* Defaults for M24512 EEPROM */
#define M24512_PARAMS_DEFAULT              \
    {                                      \
        .i2c_dev = M24512_PARAM_I2C_DEV,   \
        .i2c_addr = M24512_PARAM_I2C_ADDR, \
    } 
/** @} */

/**
 * @brief    Configure M24512
 */
static const m24512_params_t m24512_params[] =
{
#ifdef M24512_PARAMS_BOARD
    M24512_PARAMS_BOARD,
#else
    M24512_PARAMS_DEFAULT
#endif
};

/**
 * @brief    The number of configured EEPROMS
 */
#define M24512_NUMOF    (sizeof(m24512_params) / sizeof(m24512_params[0]))

#ifdef __cplusplus
}
#endif

#endif /* M24512_PARAMS_H */
/** @} */
