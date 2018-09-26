/*
 * Copyright (C) 2017 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    boards_TK-MPRS01-A 
 * @ingroup     boards
 * @brief       
 * @{
 *
 * @file
 * @brief       Board specific definitions for the radio transceicer of the 
 * TK-MPRS01-A
 *
 * @author      Kai Beckmann <kai.beckmann@hs-rm.de>
 **/

#ifndef RADIO_H
#define RADIO_H

#include <stdint.h>

#include "cpu.h"

#include "periph_conf.h"
#include "periph/gpio.h"
#include "periph/spi.h"

#ifdef __cplusplus
extern "C" {
#endif

// posible values, 2400, 868, 915
#define RAIL_RADIO_BAND 2400

// voltage of the radio PA in mV
// depends on the module TODO
#define RAIL_RADIO_PA_VOLTAGE 1800

// Packet Trace interface
#ifndef RAIL_PTI_ENABLED
#define RAIL_PTI_ENABLED     (1)
#endif

// c&p from gecko-sdk BSP for EFR32MG1_BRD4154A
#if !defined(RAIL_PTI_CONFIG)
#define RAIL_PTI_CONFIG                                                    \
  {                                                                        \
    RAIL_PTI_MODE_UART,    /* Simplest output mode is UART mode */        \
    1600000,                /* Choose 1.6 MHz for best compatibility */    \
    10,                      /* mprs01 uses location 10 for DOUT */            \
    gpioPortC,              /* Get the port for this loc */                \
    6,                     /* Get the pin, location should match above */ \
    0,                      /* DCLK not used for UART mode */              \
    0,                      /* DCLK not used for UART mode */              \
    0,                      /* DCLK not used for UART mode */              \
    10,                      /* mprs01 uses location 10 for DFRAME */          \
    gpioPortC,              /* Get the port for this loc */                \
    7,                     /* Get the pin, location should match above */ \
  }
#endif


#ifdef __cplusplus
}
#endif

#endif /* RADIO_H */
/** @} */
