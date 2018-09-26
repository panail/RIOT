/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup      drivers_sht35
 * @{
 *
 * @file
 * @brief        Device driver implementation for sensor SHT35
 *
 * @author       Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 *
 * @}
 */

#include "sht35.h"
#include "sht35_internals.h"
#include "sht35_params.h"
#include "periph/i2c.h"
#include "xtimer.h"

/**
 * @brief    Perform termperature conversion
 *
 * @param[in] temp_raw_data      Measured temperature value
 *
 * @return                       Temperature value in centi °C
 */
static inline int16_t temperature_conversion(uint16_t temp_raw_data);

/**
 * @brief    Perform relative humidity conversion
 *
 * @param[in] hum_raw_data       Measured humidity value
 *
 * @return                       Humidity value in centi RH
 */
static inline uint16_t humidity_conversion(uint16_t hum_raw_data);

/**
 * @brief    Perform CRC check
 *
 * @param[in]  buffer            Polynomial has to be checked
 *
 * @return                       Remainder value
 */
static inline uint8_t crc_check(uint8_t *buffer);

/*--------------------------------------------------------------------------*/

static inline int16_t temperature_conversion(uint16_t temp_raw_data)
{
    return (((17500 * temp_raw_data) / 65535) - 4500);
}

static inline uint16_t humidity_conversion(uint16_t hum_raw_data)
{
    return ((10000 * hum_raw_data) / 65535);
}

static inline uint8_t crc_check(uint8_t *buffer)
{
    /* Definition of the seed value */
    uint8_t seed = SHT35_CRC_SEED;

    /* CRC-Check implementation */
    for (size_t i = 0; i < 3; i++) {
        uint16_t tmp = seed ^ buffer[i];
        for (size_t j = 0; j < 8; j++) {
            if (tmp & 0x80) {
                tmp = (tmp << 1) ^ SHT35_CRC_POLYNOMIAL;
            }
            else {
                tmp = tmp << 1;
            }
        }
        seed = tmp & 0xff;
    }

    return seed;
}

/*--------------------------------------------------------------------------*/

int sht35_init(sht35_t *dev, const sht35_params_t *params)
{
    /* Array stores the status register */
    uint8_t status[2];

    /* Copy params into device params */
    dev->params = *params;

    /* I2C initialization */
    if (i2c_init_master(dev->params.i2c_dev, I2C_SPEED_NORMAL)) {
        return SHT35_ERR_I2C;
    }

    /* Transfer begin */
    if (i2c_acquire(dev->params.i2c_dev)) {
        return SHT35_ERR_I2C;
    }

    /* Soft reset of the SHT35 sensor */
    if (i2c_write_reg(dev->params.i2c_dev,
                  dev->params.i2c_addr,
                  SHT35_SOFT_RESET_MSB,
                  SHT35_SOFT_RESET_LSB) != sizeof(uint8_t)) {
        return SHT35_ERR_NODEV;
    }
    xtimer_usleep(SHT35_SOFT_RESET_DELAY_US);

    /* Read the status register of the SHT35 sensor */
    if (i2c_write_reg(dev->params.i2c_dev,
                      dev->params.i2c_addr,
                      SHT35_STATUS_READ_OUT_MSB,
                      SHT35_STATUS_READ_OUT_LSB) != sizeof(uint8_t)) {
        return SHT35_ERR_NODEV;
    }
    if (i2c_read_bytes(dev->params.i2c_dev,
                   dev->params.i2c_addr,
                   &status, sizeof(status)) != sizeof(status)) {
        return SHT35_ERR_NODEV;
    }

    /* Transfer end */
    if (i2c_release(dev->params.i2c_dev)) {
        return SHT35_ERR_I2C;
    }

    /* Register values check */
    if (status[0] != SHT35_STATUS_DEFAULT_MSB ||
        status[1] != SHT35_STATUS_DEFAULT_LSB) {
        return SHT35_ERR_NODEV;
    }

    return SHT35_OK;
}

int16_t sht35_read_temperature(sht35_t *dev)
{
    /* Definition and initialization of the help variables */
    uint8_t repeatability;
    uint8_t raw_data[6];
    union {
        uint16_t u16;
        uint8_t u8[2];
    } raw_data_union;

    /* Determine the repeatability */
    switch (dev->params.rep) {
      case SHT35_HIGH_REP:
        repeatability = SHT35_HIGH_REPEATABILITY;
        break;
      case SHT35_MED_REP:
        repeatability = SHT35_MEDIUM_REPEATABILITY;
        break;
      default:
        repeatability = SHT35_LOW_REPEATABILITY;
        break;
    }

    /* Transfer begin */
    if (i2c_acquire(dev->params.i2c_dev)) {
        return SHT35_ERR_I2C;
    }

    /* Read the data values from the SHT35 sensor */
    if (i2c_write_reg(dev->params.i2c_dev,
                      dev->params.i2c_addr,
                      SHT35_SINGLE_SHOT_MODE,
                      repeatability) != sizeof(repeatability)) {
        return SHT35_ERR_NODEV;
    }
    if (i2c_read_bytes(dev->params.i2c_dev,
                       dev->params.i2c_addr,
                       &raw_data, sizeof(raw_data)) != sizeof(raw_data)) {
        return SHT35_ERR_NODEV;
    }

    /* Transfer end */
    if (i2c_release(dev->params.i2c_dev)) {
        return SHT35_ERR_I2C;
    }

    /* CRC-Check */
    if (crc_check(&(raw_data[0]))) {
        return SHT35_ERR_CRC;
    }
    if (crc_check(&(raw_data[3]))) {
        return SHT35_ERR_CRC;
    }

    /* Conversion into physical values and store into the SHT35 struct */
    raw_data_union.u8[0] = raw_data[1];
    raw_data_union.u8[1] = raw_data[0];
    dev->data.temperature = temperature_conversion(raw_data_union.u16);
    raw_data_union.u8[0] = raw_data[4];
    raw_data_union.u8[1] = raw_data[3];
    dev->data.humidity = humidity_conversion(raw_data_union.u16);

    return dev->data.temperature;
}

uint16_t sht35_read_humidity(const sht35_t *dev)
{
    return dev->data.humidity;
}
