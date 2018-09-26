/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     drivers_ms5607
 * @brief       Internal addresses, registers and constants for the MS5607 sensor.
 * @{
 *
 * @file
 * @brief       Internal addresses, registers and constrant for the Ms5607 sensor.
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 */

#ifndef MS5607_INTERNALS_H
#define MS5607_INTERNALS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    MS5607 registers
 * @{
 */
#define MS5607_RESET                       0x1E

#define MS5607_READ_PROM_C1                0xA2
#define MS5607_READ_PROM_C2                0xA4
#define MS5607_READ_PROM_C3                0xA6
#define MS5607_READ_PROM_C4                0xA8
#define MS5607_READ_PROM_C5                0xAA
#define MS5607_READ_PROM_C6                0xAC

#define MS5607_PRESSURE_CONVERSION         0x40
#define MS5607_TEMPERATURE_CONVERSION      0x50

#define MS5607_OSR_256_REG                 0x00
#define MS5607_OSR_512_REG                 0x02
#define MS5607_OSR_1024_REG                0x04
#define MS5607_OSR_2048_REG                0x06
#define MS5607_OSR_4096_REG                0x08

#define MS5607_READ_ADC_RESULT             0x00
/** @} */

/**
 * @name    MS5607 constants
 * @{
 */
#define MS5607_RESET_DELAY_US              2800

#define MS5607_OSR_256_DELAY_US            600
#define MS5607_OSR_512_DELAY_US            1170
#define MS5607_OSR_1024_DELAY_US           2280
#define MS5607_OSR_2048_DELAY_US           4540
#define MS5607_OSR_4096_DELAY_US           9040
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* MS5607_INTERNALS_H */
/** @} */
