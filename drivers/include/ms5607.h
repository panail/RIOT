/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    drivers_ms5607 MS5607 Barometric pressure sensore
 * @ingroup     drivers_sensors
 * @brief       Device driver interface for the MS5607 sensor.
 * @{
 *
 * @file
 * @brief       Device driver interface for the MS5607 sensor.
 * 
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 */

#ifndef MS5607
#define MS5607

#include "saul.h"
#include "periph/i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief    Temperature and deltaTemp values struct
 */
typedef struct {
    int32_t delta_temp;
    int32_t temp;
} ms5607_data_t;

/**
 * @brief    Calibration struct for the MS5607 sensor
 */
typedef struct {
    uint16_t c1;                   /**< pressure sensivity */
    uint16_t c2;                   /**< pressure offset */
    uint16_t c3;                   /**< temperature coefficient of pressure sensivity */
    uint16_t c4;                   /**< temperature coefficient of pressure offset */
    uint16_t c5;                   /**< reference temperature */
    uint16_t c6;                   /**< temperature coefficient of the temperature */
} ms5607_calibration_t;

/**
 * @brief    Values for oversampling settings
 */
typedef enum {
    MS5607_OSR_4096 = 0,
    MS5607_OSR_2048 = 1,
    MS5607_OSR_1024 = 2,
    MS5607_OSR_512  = 3,
    MS5607_OSR_256  = 4
} ms5607_osr_t;


/**
 * @brief    Device initialization parameters
 */
typedef struct {
    i2c_t i2c_dev;                 /**< I2C device which is used */
    uint8_t i2c_addr;              /**< I2C address */
    ms5607_osr_t temp_osr;         /**< Oversampling mode for temperature */
    ms5607_osr_t pres_osr;         /**< Oversampling mode for pressure */
} ms5607_params_t;

/**
 * @brief    Device descriptor for the MS5607 sensor
 */
typedef struct {
    ms5607_params_t params;                  /**< Device initialization parameters */
    ms5607_calibration_t calibration;        /**< Device calibration */
    ms5607_data_t data;                      /**< Temperature and deltaTemp values */
} ms5607_t;

/**
 * @brief    Status and error return codes
 */
enum {
    MS5607_OK        =  0,                   /**< everything was fine */
    MS5607_ERR_I2C   = -1,                   /**< error initializing the I2C bus */
    MS5607_ERR_NODEV = -2,                   /**< did not detect MS5607 */
    MS5607_ERR_NOCAL = -3,                   /**< error when reading calibraion values */
};

/**
 * @brief    Initialize the given MS5607 device
 *
 * @param[out] dev        Initialized device descriptor of the MS5607 device
 * @parma[in]  params     Initialization parameters
 *
 * @return                MS5607_OK on success
 * @return                MS5607_ERR_NO2IC if given I2C is not enabled
 * @return                MS5607_ERR_NODEV if not a MS5607 at given address
 * @return                MS5607_ERR_NOCAL if an error when reading calibration values
 */
int ms5607_init(ms5607_t *dev, const ms5607_params_t *params);

/**
 * @brief    Read temperature value from the given MS5607 device, return in centi °C
 *
 * @details  This function should only be called after doing ms5607_read_temperature
 *           first.
 *
 * TODO --> CRC-Check not implemented
 *
 * @param[in]  dev        Device descriptor of the Ms5607 device to read from
 *
 * @return                Temperature in centi °C
 */
int32_t ms5607_read_temperature(ms5607_t *dev);

/**
 * @brief    Read pressure value from the given MS5607 device, return in Pa
 *
 * TODO --> CRC-Check not implemented
 *
 * @param[in]  dev        Device descriptor of the MS5607 device to read from
 *
 * @return                Pressure in Pa
 */
int32_t ms5607_read_pressure(ms5607_t *dev);

#ifdef __cplusplus
}
#endif

#endif /* MS5607_H */
/** @} */
