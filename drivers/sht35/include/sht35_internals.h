/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup      drivers_sht35
 * @brief        Internal addresses, registers, constants for the SHT35 sensor.
 * @{
 * @file
 * @brief        Internal addresses, registers, constants for the SHT35 sensor.
 *
 * @author       Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 */

#ifndef SHT35_INTERNALS_H
#define SHT35_INTERNALS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    SHT35 registers
 * @{
 */
#define SHT35_SOFT_RESET_MSB                    0x30
#define SHT35_SOFT_RESET_LSB                    0xA2

#define SHT35_STATUS_READ_OUT_MSB               0xF3
#define SHT35_STATUS_READ_OUT_LSB               0x2D

#define SHT35_SINGLE_SHOT_MODE                  0x2C

#define SHT35_HIGH_REPEATABILITY                0x06
#define SHT35_MEDIUM_REPEATABILITY              0x0D
#define SHT35_LOW_REPEATABILITY                 0x10
/** @} */

/**
 * @name    SHT35 constants
 * @{
 */
#define SHT35_SOFT_RESET_DELAY_US               1000

#define SHT35_STATUS_DEFAULT_MSB                0x80
#define SHT35_STATUS_DEFAULT_LSB                0x10

#define SHT35_CRC_SEED                          0xFF
#define SHT35_CRC_POLYNOMIAL                    0x31
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* SHT35_INTERNALS_H */
/** @} */
