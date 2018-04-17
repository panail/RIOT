/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup    drivers_m24512
 * @brief      Constants for the M24512 EEPROM
 * @{
 * @file
 * @brief      Constants for the M24512 EEPROM
 *
 * @author     Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 */

#ifndef M24512_INTERNALS_H
#define M24512_INTERNALS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name   M24512 constants
 * @{
 */
#define M24512_SIZE                65536       /**< The size of the M24512 in bytes */
#define M24512_PAGE_SIZE           128         /**< Number of bytes one page contains */
#define M24512_WRITE_DELAY_US      5000        /**< Delay after each write cycle */
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* M24512_INTERNALS_H */
/** @} */
