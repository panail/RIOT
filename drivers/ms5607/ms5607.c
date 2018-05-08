/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     drivers_ms5607
 * @{
 *
 * @file
 * @brief       Device driver implementation for the MS5607 pressure sensor.
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 *
 * @}
 */

#include "ms5607.h"
#include "ms5607_internals.h"
#include "ms5607_params.h"
#include "periph/i2c.h"
#include "xtimer.h"
#include "byteorder.h"

#include "fmt.h"

/**
 * @brief    Calculate difference between actual and reference temperature
 *
 * @param[in]  temp_value        Digital temperature value
 * @param[in]  c5                Reference temperature
 *
 * @return                       Difference between actual and reference temperature
 */
static inline int32_t calc_delta_temp(uint32_t temp_value, uint16_t c5);

/**
 * @brief    Calculate actual temperature
 *
 * @param[in]  delta_temp        Difference between actual and reference temperature
 * @param[in]  c6                Temperature coefficient of the temperature
 *
 * @return                       Actual temperature in c°C (centi)
 */
static inline int32_t calc_temp(int32_t delta_temp, uint16_t c6);

/**
 * @brief    Calculate offset at actual temperature
 *
 * @param[in]  delta_temp        Difference between actual and reference temperature
 * @param[in]  c2                Pressure offset
 * @param[in]  c4                Temperature coefficient of pressure offset
 *
 * @return                       Offset at actual temperature
 */
static inline int64_t calc_offset(int32_t delta_temp, uint16_t c2, uint16_t c4);

/**
 * @brief    Calculate sensitivity at actual temperature
 *
 * @param[in]  delta_temp        Difference between actual and reference temperature
 * @param[in]  c1                Pressure sensitivity
 * @param[in]  c3                Temperature coefficient of pressure sensitivity
 *
 * @return                       Sensitivity at actual temperature
 */
static inline int64_t calc_sensitivity(int32_t delta_temp, uint16_t c1, uint16_t c3);

/**
 * @brief    Calculate temperature compensated pressure
 *
 * @param[in]  pres_value        Digital pressure value
 * @param[in]  offset            Offset at actual temperature
 * @param[in]  sensitivity       Sensitivity at actual temperature
 *
 * @return                       Temperature compensated pressure
 */
static inline int32_t calc_pressure(uint32_t pres_value,
                                    int64_t offset,
                                    int64_t sensitivity);

/**
 * @brief    Second order temperature compensation
 *
 * @param[in]  delta_temp        Difference between actual and reference temperature
 * @param[in]  temp              Actual temperature in c°C (centi)
 * @param[in]  offset            Offset at actual temperature
 * @param[in]  sensitivity       Sensitivity at actual temperature
 */
static inline void calc_second_order(int32_t delta_temp,
                                     int32_t *temp,
                                     int64_t *offset,
                                     int64_t *sensitivity);

/*-------------------------------------------------------------------------*/

static inline int32_t calc_delta_temp(uint32_t temp_value, uint16_t c5)
{
    return (temp_value - ((uint32_t)c5 << 8));
}

static inline int32_t calc_temp(int32_t delta_temp, uint16_t c6)
{
    return (2000 + (((int64_t)delta_temp * c6) >> 23));
}

static inline int64_t calc_offset(int32_t delta_temp, uint16_t c2, uint16_t c4)
{
    return (((uint64_t)c2 << 17) + (((uint64_t)c4 * delta_temp) >> 6));
}

static inline int64_t calc_sensitivity(int32_t delta_temp, uint16_t c1, uint16_t c3)
{
    return (((uint64_t)c1 << 16) + (((uint64_t)c3 * delta_temp) >> 7));
}

static inline int32_t calc_pressure(uint32_t pres_value,
                                    int64_t offset,
                                    int64_t sensitivity)
{
    return ((((pres_value * sensitivity) >> 21) - offset) >> 15);
}

static inline void calc_second_order(int32_t delta_temp,
                                     int32_t *temp,
                                     int64_t *offset,
                                     int64_t *sensitivity)
{
    int32_t temp_2;
    int64_t offset_2;
    int64_t sensitivity_2;

    temp_2 = ((int64_t)delta_temp * delta_temp) >> 31;
    offset_2 = (61 * ((int64_t)(*temp - 2000) * (*temp - 2000))) >> 4;
    sensitivity_2 = 2 * ((int64_t)(*temp - 2000) * (*temp - 2000));

    if (*temp < 1500) {
        offset_2 = offset_2 + (15 * ((int64_t)(*temp + 1500) * (*temp + 1500)));
        sensitivity_2 = sensitivity_2 + (8 * ((int64_t)(*temp + 1500) * (*temp + 1500)));
    }

    *temp = *temp - temp_2;
    *offset = *offset - offset_2;
    *sensitivity = *sensitivity - sensitivity_2;
}

/*-------------------------------------------------------------------------*/

int ms5607_init(ms5607_t *dev, const ms5607_params_t *params)
{
    /* Definition and initialization of the help variables */
    union {
        uint32_t u16;
        uint8_t u8[2];
    } raw_data;

    /* Copy params into device params */
    dev->params = *params;

    /* I2C initialization */
    if (i2c_init_master(dev->params.i2c_dev, I2C_SPEED_NORMAL)) {
        return MS5607_ERR_I2C;
    }

    /* Transfer begin */
    if (i2c_acquire(dev->params.i2c_dev)) {
        return MS5607_ERR_I2C;
    }

    /* Reset of the MS5607 sensor */
    if (i2c_write_byte(dev->params.i2c_dev,
                       dev->params.i2c_addr,
                       MS5607_RESET) != sizeof(uint8_t)) {
        return MS5607_ERR_NODEV;
    }
    xtimer_usleep(MS5607_RESET_DELAY_US);

    /* Read calibration values */
    if (i2c_write_byte(dev->params.i2c_dev,
                       dev->params.i2c_addr,
                       MS5607_READ_PROM_C1) != sizeof(uint8_t)) {
        return MS5607_ERR_NODEV;
    }
    if (i2c_read_bytes(dev->params.i2c_dev,
                       dev->params.i2c_addr,
                       raw_data.u8,
                       sizeof(raw_data.u8)) != sizeof(raw_data.u8)) {
        return MS5607_ERR_NOCAL;
    }
    dev->calibration.c1 = ntohs(raw_data.u16);
    if (i2c_write_byte(dev->params.i2c_dev,
                       dev->params.i2c_addr,
                       MS5607_READ_PROM_C2) != sizeof(uint8_t)) {
        return MS5607_ERR_NODEV;
    }
    if (i2c_read_bytes(dev->params.i2c_dev,
                       dev->params.i2c_addr,
                       raw_data.u8,
                       sizeof(raw_data.u8)) != sizeof(raw_data.u8)) {
        return MS5607_ERR_NOCAL;
    }
    dev->calibration.c2 = ntohs(raw_data.u16);
    if (i2c_write_byte(dev->params.i2c_dev,
                       dev->params.i2c_addr,
                       MS5607_READ_PROM_C3) != sizeof(uint8_t)) {
        return MS5607_ERR_NODEV;
    }
    if (i2c_read_bytes(dev->params.i2c_dev,
                       dev->params.i2c_addr,
                       raw_data.u8,
                       sizeof(raw_data.u8)) != sizeof(raw_data.u8)) {
        return MS5607_ERR_NODEV;
    }
    dev->calibration.c3 = ntohs(raw_data.u16);
    if (i2c_write_byte(dev->params.i2c_dev,
                       dev->params.i2c_addr,
                       MS5607_READ_PROM_C4) != sizeof(uint8_t)) {
        return MS5607_ERR_NODEV;
    }
    if (i2c_read_bytes(dev->params.i2c_dev,
                       dev->params.i2c_addr,
                       raw_data.u8,
                       sizeof(raw_data.u8)) != sizeof(raw_data.u8)) {
        return MS5607_ERR_NOCAL;
    }
    dev->calibration.c4 = ntohs(raw_data.u16);
    if (i2c_write_byte(dev->params.i2c_dev,
                       dev->params.i2c_addr,
                       MS5607_READ_PROM_C5) != sizeof(uint8_t)) {
        return MS5607_ERR_NODEV;
    }
    if (i2c_read_bytes(dev->params.i2c_dev,
                       dev->params.i2c_addr,
                       raw_data.u8,
                       sizeof(raw_data.u8)) != sizeof(raw_data.u8)) {
        return MS5607_ERR_NOCAL;
    }
    dev->calibration.c5 = ntohs(raw_data.u16);
    if (i2c_write_byte(dev->params.i2c_dev,
                       dev->params.i2c_addr,
                       MS5607_READ_PROM_C6) != sizeof(uint8_t)) {
        return MS5607_ERR_NODEV;
    }
    if (i2c_read_bytes(dev->params.i2c_dev,
                       dev->params.i2c_addr,
                       raw_data.u8,
                       sizeof(raw_data.u8)) != sizeof(raw_data.u8)) {
        return MS5607_ERR_NODEV;
    }
    dev->calibration.c6 = ntohs(raw_data.u16);

    /* Transfer end */
    if (i2c_release(dev->params.i2c_dev)) {
        return MS5607_ERR_I2C;
    }

    return MS5607_OK;
}

int32_t ms5607_read_temperature(ms5607_t *dev)
{
    /* Definition and initialization of the help variables */
    uint8_t osr;
    int delay;
    uint32_t value;
    union {
        uint32_t u32;
        uint8_t u8[4];
    } raw_data;

    /* Determine the oversampling rate of the temperature measurement */
    switch (dev->params.temp_osr) {
      case MS5607_OSR_256:
        osr = MS5607_OSR_256_REG;
        delay = MS5607_OSR_256_DELAY_US;
        break;
      case MS5607_OSR_512:
        osr = MS5607_OSR_512_REG;
        delay = MS5607_OSR_512_DELAY_US;
        break;
      case MS5607_OSR_1024:
        osr = MS5607_OSR_1024_REG;
        delay = MS5607_OSR_1024_DELAY_US;
        break;
      case MS5607_OSR_2048:
        osr = MS5607_OSR_2048_REG;
        delay = MS5607_OSR_2048_DELAY_US;
        break;
      default:
        osr = MS5607_OSR_4096_REG;
        delay = MS5607_OSR_4096_DELAY_US;
        break;
    }

    /* Transfer begin */
    if (i2c_acquire(dev->params.i2c_dev)) {
        return MS5607_ERR_I2C;
    }

    /* Read the temperature value from the MS5607 sensor */
    if (i2c_write_byte(dev->params.i2c_dev,
                       dev->params.i2c_addr,
                       MS5607_TEMPERATURE_CONVERSION | osr) != sizeof(uint8_t)) {
        return MS5607_ERR_NODEV;
    }
    xtimer_usleep(delay);
    if (i2c_write_byte(dev->params.i2c_dev,
                       dev->params.i2c_addr,
                       MS5607_READ_ADC_RESULT) != sizeof(uint8_t)) {
        return MS5607_ERR_NODEV;
    }
    if (i2c_read_bytes(dev->params.i2c_dev,
                       dev->params.i2c_addr,
                       raw_data.u8,
                       sizeof(raw_data.u8) - 1) != sizeof(raw_data.u8) - 1) {
        return MS5607_ERR_NODEV;
    }
    value = ntohl(raw_data.u32) >> 8;

    /* Transfer end */
    if (i2c_release(dev->params.i2c_dev)) {
        return MS5607_ERR_I2C;
    }

    /* Calculate difference between actual and reference temperature */
    dev->data.delta_temp = calc_delta_temp(value, dev->calibration.c5);

    /* Calculate actual temperature */
    dev->data.temp = calc_temp(dev->data.delta_temp, dev->calibration.c6);

    return dev->data.temp;
}

int32_t ms5607_read_pressure(ms5607_t *dev)
{
    /* Definition and initialization of the help variables */
    uint8_t osr;
    int delay;
    uint32_t value;
    union {
        uint32_t u32;
        uint8_t u8[4];
    } raw_data;
    int64_t offset;
    int64_t sensitivity;

    /* Determine the oversampling rate of the pressure measurement */
    switch (dev->params.pres_osr) {
      case MS5607_OSR_256:
        osr = MS5607_OSR_256_REG;
        delay = MS5607_OSR_256_DELAY_US;
        break;
      case MS5607_OSR_512:
        osr = MS5607_OSR_512_REG;
        delay = MS5607_OSR_512_DELAY_US;
        break;
      case MS5607_OSR_1024:
        osr = MS5607_OSR_1024_REG;
        delay = MS5607_OSR_1024_DELAY_US;
        break;
      case MS5607_OSR_2048:
        osr = MS5607_OSR_2048_REG;
        delay = MS5607_OSR_2048_DELAY_US;
        break;
      default:
        osr = MS5607_OSR_4096_REG;
        delay = MS5607_OSR_4096_DELAY_US;
        break;
    }

    /* Transfer begin */
    if (i2c_acquire(dev->params.i2c_dev)) {
        return MS5607_ERR_I2C;
    }

    /* Read the temperature value from the MS5607 sensor */
    if (i2c_write_byte(dev->params.i2c_dev,
                       dev->params.i2c_addr,
                       MS5607_PRESSURE_CONVERSION | osr) != sizeof(uint8_t)) {
        return MS5607_ERR_NODEV;
    }
    xtimer_usleep(delay);
    if (i2c_write_byte(dev->params.i2c_dev,
                       dev->params.i2c_addr,
                       MS5607_READ_ADC_RESULT) != sizeof(uint8_t)) {
        return MS5607_ERR_NODEV;
    }
    if (i2c_read_bytes(dev->params.i2c_dev,
                       dev->params.i2c_addr,
                       raw_data.u8,
                       sizeof(raw_data.u8) - 1) != sizeof(raw_data.u8) - 1) {
        return MS5607_ERR_NODEV;
    }
    value = ntohl(raw_data.u32) >> 8;

    /* Transfer end */
    if (i2c_release(dev->params.i2c_dev)) {
        return MS5607_ERR_I2C;
    }

    /* Calculate offset at actual temperature */
    offset = calc_offset(dev->data.delta_temp, dev->calibration.c2, dev->calibration.c4);

    /* Calculate sensitivity at actual temperature */
    sensitivity = calc_sensitivity(dev->data.delta_temp,
                                   dev->calibration.c1,
                                   dev->calibration.c3);

    /* Calculate second order temperature compensation, if temperature is smallel
     * than 20°C */
    if (dev->data.temp < 2000) {
        calc_second_order(dev->data.delta_temp,
                          &(dev->data.temp),
                          &offset,
                          &sensitivity);
    }

    /* Calculate temperature compensated pressure */
    return (calc_pressure(value, offset, sensitivity));
}
