/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @defgroup    drivers_m24512 M24512 EEPROM
 * @ingroup     drivers_nvram
 * @brief       Device driver interface for the ST M24512 EEPROM.
 *
 * @{
 * @file
 * @brief       Device driver interface for the M24512 EEPROM.
 *
 * @details     M24512 is a EEPROM with the storage size of 64KB. In case of the
 *              access into the EEPROM, read or write, the data length must be
 *              smaller than the entire storage size.
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 */

#ifndef M24512_H
#define M24512_H

#include "nvram.h"
#include "periph/i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Bus parameters for M24512
 */
typedef struct {
    /* I2C details */
    i2c_t i2c_dev;                      /**< I2C device which is used */
    uint8_t i2c_addr;                   /**< I2C address */
} m24512_params_t;

/**
 * @brief   Status and error return codes
 */
enum {
    M24512_OK         =  0,      /**< everything was fine */
    M24512_ERR_I2C    = -1,      /**< I2C bus error */
    M24512_ERR_NODEV  = -2,      /**< did not detect M24512 EEPROM */
    M24512_ERR_SIZEOV = -3,      /**< size is greater than the NVRAM size */
};

/**
 * @brief   Initialize an nvram_t sturcture with M24512 settings.
 *
 * @param[out] dev      Pointer to NVRAM device descriptor
 * @param[out] params   Pointer to M24512 settings
 * @param[in]  size     Device capacity
 *
 * @return              0 on success
 * @return              <0 on errors
 */
int m24512_init(nvram_t *dev, const m24512_params_t *params);

#ifdef __cplusplus
}
#endif

#endif /* M24512_H */
/** @} */
