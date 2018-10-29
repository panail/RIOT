/*
 * Copyright (C) 2016 Patrick Naili <stpanail@stud.h-da.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       firmware update
 *
 * @author      Patrick Naili <stpanail@stud.h-da.de>
 * @}
 */


#ifndef WAKAAMA_FIRMWARE_UPDATE_H_
#define WAKAAMA_FIRMWARE_UPDATE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "net/sock/udp.h"
#include "firmware/simple.h"
#include "liblwm2m.h"


#define URI_MAX_LENGTH 256


void firmware_update_download(char* uri);


#ifdef __cplusplus
}
#endif
#endif /* WAKAAMA_FIRMWARE_UPDATE_H_ */
