/*
 * Copyright (C) 2016-2017 Bas Stottelaar <basstottelaar@gmail.com>
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
 * @brief       Sensor values displayed on the low-power memory LCD. The RTT
 *              is used to wakeup the MCU from EM2 (sleep mode).
 *
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

#include <stdio.h>

#include "board.h"
#include "xtimer.h"

#include "u8g2.h"
#include "sht35.h"
#include "sht35_params.h"

#include "periph/gpio.h"
#include "periph/adc.h"

#include "msg.h"

#include "images.h"

#define INTERVAL (10U)                          /**< Wakeup interval (in seconds) */
#define TEMP_MIN 0                              /**< in centi °C */
#define TEMP_MAX 4000                           /**< in centi °C */
#define TEMP_PRESET 2000                        /**< in centi °C */
#define TEMP_STEP 100                           /**< in centi °C */
#define DEBOUNCE_DELAY 150000                   /**< in microseconds */
#define CYCLETIME 10000000                      /*+< in microseconds */

static volatile int32_t preset_temperature = TEMP_PRESET;
static volatile int state = 0;
static volatile kernel_pid_t pid = 0;

/**
 * @brief   RIOT-OS pin maping of U8g2 pin numbers to RIOT-OS GPIO pins.
 */
static gpio_t pins[] = {
    [U8X8_PIN_CS] = LCD_CS_PIN,
};

/**
 * @brief   Bit mapping to indicate which pins are set.
 */
static uint32_t pins_enabled = (
    (1 << U8X8_PIN_CS)
);

/**
 * @brief   Decreases the preset temperature
 */
static void dec_temp(void) {
    xtimer_t timer;
    msg_t msg;

    gpio_irq_disable(BTN1_PIN);
    if (preset_temperature > TEMP_MIN) {
        preset_temperature -= TEMP_STEP;
    }
    xtimer_set_msg(&timer, 0, &msg, pid);
    xtimer_usleep(DEBOUNCE_DELAY);
    gpio_irq_enable(BTN1_PIN);
}

/**
 * @brief   Increases the preset temperature
 */
static void inc_temp(void) {
    xtimer_t timer;
    msg_t msg;

    gpio_irq_disable(BTN2_PIN);
    if (preset_temperature < TEMP_MAX) {
        preset_temperature += TEMP_STEP;
    }
    xtimer_set_msg(&timer, 0, &msg, pid);
    xtimer_usleep(DEBOUNCE_DELAY);
    gpio_irq_enable(BTN2_PIN);
}

int main(void)
{
    char buffer[3][16];
    int32_t temperature;
    int32_t humidity;

    u8g2_t u8g2;
    sht35_t dev;

    msg_t msg;

    /* store the actual PID into global pid variable */
    pid = thread_getpid();

    /* prepare buttons */
    gpio_init_int(BTN1_PIN, GPIO_IN_PU, GPIO_FALLING, (gpio_cb_t)dec_temp, NULL);
    gpio_init_int(BTN2_PIN, GPIO_IN_PU, GPIO_FALLING, (gpio_cb_t)inc_temp, NULL);

    /* prepare display */
    gpio_init(LCD_EXTCOMIN_PIN, GPIO_OUT);

    gpio_set(LCD_EXTCOMIN_PIN);

    u8g2_Setup_ls013b7dh03_128x128_1(&u8g2,
                                     U8G2_R0,
                                     u8x8_byte_riotos_hw_spi,
                                     u8x8_gpio_and_delay_riotos);

    u8x8_SetPins(u8g2_GetU8x8(&u8g2), pins, pins_enabled);
    u8x8_SetDevice(u8g2_GetU8x8(&u8g2), SPI_DEV(0));
    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);

    sht35_init(&dev, &sht35_params[0]);

    while (1) {
        /* measure temperature via Si7021 */
        temperature = sht35_read_temperature(&dev);
        humidity = sht35_read_humidity(&dev);

        /* display results */
        snprintf(buffer[0], 16, "%ld.%02ld C",
            preset_temperature / 100, preset_temperature % 100);
        snprintf(buffer[1], 16, "%ld.%02ld C", temperature / 100, temperature % 100);
        snprintf(buffer[2], 16, "%ld.%02ld %%", humidity / 100, humidity % 100);

        u8g2_FirstPage(&u8g2);

        do {
            u8g2_SetDrawColor(&u8g2, 1);
            u8g2_SetFont(&u8g2, u8g2_font_helvB12_tf);

            /* preset temperaure */
            u8g2_DrawBitmap(&u8g2, 2, 20 - 16 + 2, 2, 16, image_preset_temperature);
            u8g2_DrawStr(&u8g2, 25, 20, buffer[0]);

            /* actual temperature */
            u8g2_DrawBitmap(&u8g2, 2, 60 - 16 + 2, 2, 16, image_temperature);
            u8g2_DrawStr(&u8g2, 25, 60, buffer[1]);

            /* actual humidity */
            u8g2_DrawBitmap(&u8g2, 2, 80 - 16 + 2, 2, 16, image_rh);
            u8g2_DrawStr(&u8g2, 25, 80, buffer[2]);

            /* actual window state */
            // TODO the state should be 1, if the window is open, 0 - if it is closed */
            if (state) {
                u8g2_DrawBitmap(&u8g2, 56, 110 - 16 + 2, 2, 16, image_window_open);
            } else {
                u8g2_DrawBitmap(&u8g2, 56, 110 - 16 + 2, 2, 16, image_window_closed);
            }

        } while (u8g2_NextPage(&u8g2));

        /* go to sleep */
        xtimer_msg_receive_timeout(&msg, CYCLETIME);
    }

    return 0;
}
