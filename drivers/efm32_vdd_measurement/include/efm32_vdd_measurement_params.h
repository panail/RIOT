/*
 * Copyright (C) 2018 Hochschule RheinMain
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup      drivers_efm32_vdd_measurement
 *
 * @{
 * @file
 * @brief        Default configuration for EFM32 VDD Measurement
 *
 * @author       Alexander Wihlelm <alexander.wilhelm@student.hs-rm.de>
 */

#ifndef EFM32_VDD_MEASUREMENT_PARAMS_H
#define EFM32_VDD_MEASUREMENT_PARAMS_H

#include "board.h"
#include "efm32_vdd_measurement.h"
#include "saul_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    Set default configuration parameters for the EFM32 VDD Measurement
 * @{
 */
#ifndef EFM32_VDD_MEASUREMENT_PARAM_ADC_LINE
#define EFM32_VDD_MEASUREMENT_PARAM_ADC_LINE           ADC_LINE(VDD_MEASS_LINE)
#endif

/* Defaults for Voltage Monitoring */
#define EFM32_VDD_MEASUREMENT_PARAMS_DEFAULT {                   \
    .adc_line = EFM32_VDD_MEASUREMENT_PARAM_ADC_LINE,            \
}
/** @} */

/**
 * @brief    Configure EFM32 VDD Measurement
 */
static const efm32_vdd_measurement_params_t efm32_vdd_measurement_params[] = {
#ifdef EFM32_VDD_MEASUREMENT_PARAMS_BOARD
    EFM32_VDD_MEASUREMENT_PARAMS_BOARD,
#else
    EFM32_VDD_MEASUREMENT_PARAMS_DEFAULT
#endif
};

/**
 * @brief    The number of configured sensors
 */
#define EFM32_VDD_MEASUREMENT_NUMOF     (sizeof(efm32_vdd_measurement_params) /       \
                                         sizeof(efm32_vdd_measurement_params[0]))

/**
 * @brief    Configuration details of SAUL registry entries
 */
static const saul_reg_info_t efm32_vdd_measurement_reg_info[EFM32_VDD_MEASUREMENT_NUMOF] = {
    { .name = "efm32_vdd_measurement" }
};

#ifdef __cplusplus
}
#endif

#endif /* EFM32_VDD_MEASUREMENT_PARAMS_H */
