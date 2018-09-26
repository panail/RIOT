/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    drivers_sht35 SHT35 temperature and humidity sensor
 * @ingroup     drivers_sensors
 * @brief       Device driver interface for the Sensirion SHT35 sensor.
 *
 * SHT35 measure temperature in centi °C and relative humidity in centi RH.
 *
 * @{
 * @file
 * @brief       Device driver interface for the Sensirion SHT35 sensor.
 *
 * @details     There are two sensor values that can be read: temperature
 *              and humidity. THE SHT35 device usually measures them all
 *              at once. The driver is written in such a way that a
 *              measurement is only started from the function that reads
 *              the temperature. In other words, you always have to call
 *              sht35_read_temperature, and then optionally you can call
 *              the sht35_read_humidity.
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 */

#ifndef SHT35_H
#define SHT35_H

#include "saul.h"
#include "periph/i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Temperature and relative humidity values struct
 */
typedef struct {
    int16_t temperature;
    uint16_t humidity;
} sht35_data_t;

/**
 * @brief   Values for repeatability settings
 **/
typedef enum {
    SHT35_HIGH_REP = 0,
    SHT35_MED_REP  = 1,
    SHT35_LOW_REP  = 2
} sht35_repeatability_t;

/**
 * @brief   Parameters for the SHT35 sensor
 *
 * These parameters are needed to configure the device at startup.
 */
typedef struct {
    /* I2C details */
    i2c_t i2c_dev;                      /**< I2C device which is used */
    uint8_t i2c_addr;                   /**< I2C address */

    /* Config Register */
    sht35_repeatability_t rep;          /**< Repeatability mode */
} sht35_params_t;

/**
 * @brief    Device descriptor for the SHT35 sensor
 */
typedef struct {
    sht35_params_t params;              /**< Device parameters */
    sht35_data_t data;                  /**< Temperature and humidity data */
} sht35_t;

/**
 * @brief    Status and error return codes
 */
enum {
    SHT35_OK           =  0,            /**< everything was fine */
    SHT35_ERR_I2C      = -1,            /**< error initializing the I2C bus */
    SHT35_ERR_NODEV    = -2,            /**< did not detect SHT35 sensor */
    SHT35_ERR_CRC      = -3,            /**< crc-check failure */
};

/**
 * @brief    Initialize the given SHT35 device
 *
 * @param[out] dev          Initialized device descriptor of SHT35 device
 * @param[in]  params       The parameters for the SHT35 device (sampling rate, etc)
 *
 * @return                  SHT35_OK on success
 * @return                  SHT35_ERR_I2C
 * @return                  SHT35_ERR_NODEV
 */
int sht35_init(sht35_t *dev, const sht35_params_t *params);

/**
 * @brief    Read temperature value from the given SHT35 device,
 *           returned in centi °C
 *
 * @param[in]  dev          Device descriptor of SHT35 device to read from
 *
 * @returns                 The temperature in centi Celsius.
 */
int16_t sht35_read_temperature(sht35_t *dev);

/**
 * @brief    Read relarive humidity value from the given SHT35 device,
 *           returned in centi RH.
 *
 * @details  This function should only be called after doing
 *           sht35_read_temperature first.
 * 
 * @param[in]  dev          Device descriptor of SHT35 device to read from
 *
 * @returns                 Humidity in centi RH
 */
uint16_t sht35_read_humidity(const sht35_t *dev);

#ifdef __cplusplus
}
#endif

#endif /* SHT35_H */
/** @} */
