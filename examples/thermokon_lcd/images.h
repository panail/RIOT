/*
 * Copyright (C) 2016-2017 Bas Stottelaar <basstottelaar@gmail.com>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#ifndef IMAGES_H
#define IMAGES_H

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Image of internal temperature (16x16 pixels)
 */
const uint8_t image_preset_temperature [] = {
    0x7F, 0xFE, 0x80, 0x01, 0x81, 0x81, 0x82, 0x41, 0x82, 0x41, 0x82, 0x41,
    0x82, 0x41, 0x84, 0x21, 0x8B, 0xD1, 0x8B, 0xD1, 0x8B, 0xD1, 0x8B, 0xD1,
    0x84, 0x21, 0x83, 0xC1, 0x80, 0x01, 0x7F, 0xFE
};

/**
 * @brief   Image of temperature (16x16 pixels)
 */
const uint8_t image_temperature [] = {
    0x01, 0x80, 0x02, 0x40, 0x02, 0x40, 0x02, 0x40, 0x02, 0x40, 0x02, 0x40,
    0x02, 0x40, 0x02, 0x40, 0x02, 0x40, 0x04, 0x20, 0x0B, 0xD0, 0x0B, 0xD0,
    0x0B, 0xD0, 0x0B, 0xD0, 0x04, 0x20, 0x03, 0xC0
};

/**
 * @brief   Image of relative humidity (16x16 pixels)
 */
const uint8_t image_rh [] = {
    0x00, 0x40, 0x00, 0xE0, 0x02, 0xA0, 0x05, 0x10, 0x05, 0x08, 0x08, 0x88,
    0x10, 0x44, 0x10, 0x44, 0x20, 0x24, 0x20, 0x24, 0x28, 0x24, 0x28, 0x24,
    0x28, 0x28, 0x20, 0x30, 0x10, 0x40, 0x0F, 0x80
};

/**
 * @brief   Image of opened window (16x16 pixels)
 */
const uint8_t image_window_open [] = {
    0x3F, 0xFC, 0x30, 0x04, 0x28, 0x04, 0x24, 0x04, 0x22, 0x04, 0x21, 0x04,
    0x21, 0x04, 0x21, 0x04, 0x21, 0x04, 0x21, 0x04, 0x21, 0x04, 0x3F, 0xFC,
    0x11, 0x00, 0x09, 0x00, 0x05, 0x00, 0x02, 0x00
};

/**
 * @brief   Image of closed window (16x16 pixels)
 */
const uint8_t image_window_closed [] = {
    0x3F, 0xFC, 0x20, 0x04, 0x2F, 0xF4, 0x28, 0x14, 0x28, 0x14, 0x28, 0x14,
    0x28, 0x14, 0x28, 0x14, 0x28, 0x14, 0x2F, 0xF4, 0x20, 0x04, 0x3F, 0xFC,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#ifdef __cplusplus
}
#endif

#endif /* IMAGES_H */
