/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup     drivers_m24512
 * @{
 *
 * @file
 * @brief       Device interface for M2415 connected EEPROM.
 *
 * @author      Alexander Wilhelm <alexander.wilhelm@student.hs-rm.de>
 */

#include "nvram.h"
#include "m24512.h"
#include "m24512_internals.h"
#include "m24512_params.h"
#include "periph/i2c.h"
#include "xtimer.h"

/**
 * @brief   Copy data from system memory to EEPROM.
 *
 * @param[in]  dev    Pointer to NVRAM device descriptor
 * @param[in]  src    Pointer to the first byte in the system memory address space
 * @param[in]  dst    Starting address in the NVRAM device address space
 * @param[in]  len    Number of bytes to copy
 *
 * @return            Number ob bytes written on succes
 * @return            <0 on errors
 */
static int m24512_write(nvram_t *dev, const uint8_t *src, uint32_t dst, size_t len);

/**
 * @brief   Copy data from EEPROM to system memmory.
 *
 * @param[in]  dev    Pointer to NVRAM device descriptor
 * @param[out] dst    Pointer to the first byte in the system memory address space
 * @param[in]  src    Starting address in the NVRAM device address space
 * @param[in]  len    Number of bytes to copy
 *
 * @return            Number of bytes read on success
 * @return            <0 on errors
 */
static int m24512_read(nvram_t *dev, uint8_t *dst, uint32_t src, size_t len);

/**
 * @brief   Returns the Number of bytes to fill up the current page.
 *
 * @param[in]  addr_data    Starting address in the NVRAM device address space
 *
 * @return                  Number of bytes to fill up the current page
 */
static inline unsigned int page_rollover(uint32_t addr_data)
{
    return M24512_PAGE_SIZE - (addr_data & (M24512_PAGE_SIZE - 1));
}

int m24512_init(nvram_t *dev, const m24512_params_t *params)
{
    /* Initialize NVRAM struct */
    dev->size = M24512_SIZE;
    dev->write = m24512_write;
    dev->read = m24512_read;
    dev->extra = (m24512_params_t *)params;

    /* Initialize I2C interface */
    if (i2c_init_master(((m24512_params_t *)dev->extra)->i2c_dev, I2C_SPEED_NORMAL)) {
        return M24512_ERR_I2C;
    }
    return M24512_OK;
}

static int m24512_write(nvram_t *dev, const uint8_t *src, uint32_t dst, size_t len)
{
    /* Checks if the input destination address is not greater than the NVRAM size */
    if (dst >= M24512_SIZE) {
        return M24512_ERR_SIZEOV;
    }

    /* Determines the buffer size */
    size_t buffer_size;
    if (len > M24512_PAGE_SIZE) {
        buffer_size = M24512_PAGE_SIZE;
    }
    else {
        buffer_size = len;
    }

    /* Definition and initialization of the help variables */
    size_t bytes_done = 0;
    size_t len_remain = len;
    union {
        uint32_t u32;
        uint8_t u8[4];
    } addr_data;
    addr_data.u32 = dst;
    uint8_t buffer[buffer_size + 1];
    buffer[0] = addr_data.u8[0];
    size_t buffer_fill = len_remain;

    /* Transfer begin */
    if (i2c_acquire(((m24512_params_t *)dev->extra)->i2c_dev)) {
        return M24512_ERR_I2C;
    }

    /* Checks if the page roll-over happens */
    while (len_remain) {
        if (buffer_fill > page_rollover(addr_data.u32)) {
            buffer_fill = page_rollover(addr_data.u32);
        }

        for (unsigned int i = 0; i < buffer_fill; i++) {
            buffer[i + 1] = src[i + bytes_done];
        }

        /* Writes the buffer into the EEPROM */
        if (i2c_write_regs(((m24512_params_t *)dev->extra)->i2c_dev,
                       ((m24512_params_t *)dev->extra)->i2c_addr,
                       addr_data.u8[1],
                       &buffer,
                       buffer_fill + 1) != (int)(buffer_fill + 1)) {
            return M24512_ERR_NODEV;
        }
        xtimer_usleep(M24512_WRITE_DELAY_US);

        /* Changes the values of the help variables */
        bytes_done = bytes_done + buffer_fill;
        len_remain = len_remain - buffer_fill;
        addr_data.u32 = (addr_data.u32 + buffer_fill) % M24512_SIZE;
        buffer[0] = addr_data.u8[0];
        buffer_fill = len_remain;
    }

    /* Transfer end */
    if (i2c_release(((m24512_params_t *)dev->extra)->i2c_dev)) {
        return M24512_ERR_I2C;
    }
    else {
    }

    return len;
}

static int m24512_read(nvram_t *dev, uint8_t *dst, uint32_t src, size_t len)
{
    /* Checks if the input destination address is not greater than the NVRAM size */
    if (src >= M24512_SIZE) {
        return M24512_ERR_SIZEOV;
    }

    /* Definition and initialization of the help variables */
    union {
        uint32_t u32;
        uint8_t u8[4];
    } addr_data;
    addr_data.u32 = src;

    /* Transfer begin */
    if (i2c_acquire(((m24512_params_t *)dev->extra)->i2c_dev)) {
        return M24512_ERR_I2C;
    }

    /* Reads data from EEPROM */
    if (i2c_write_reg(((m24512_params_t *)dev->extra)->i2c_dev,
                  ((m24512_params_t *)dev->extra)->i2c_addr,
                  addr_data.u8[1],
                  addr_data.u8[0]) != sizeof(addr_data.u8[0])) {
        return M24512_ERR_NODEV;
    }
    if (i2c_read_bytes(((m24512_params_t *)dev->extra)->i2c_dev,
                   ((m24512_params_t *)dev->extra)->i2c_addr,
                   dst,
                   len) <= 0) {
        return M24512_ERR_NODEV;
    }

    /* Transfer end */
    if (i2c_release(((m24512_params_t *)dev->extra)->i2c_dev)) {
        return M24512_ERR_I2C;
    }

    return len;
}

/** @} */
