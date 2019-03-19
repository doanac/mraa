/*
 * Author: Andy Doan <andy@foundries.io>
 * Copyright (c) 2019 Foundries.io
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <mraa/common.h>
#include <mraa_internal_types.h>

#include "common.h"

#define PLATFORM_NAME_APALIS "Apalis"

static int GPIOS[][2] = {
    { 2, 4 }, //GPIO2_IO4
    { 2, 5 },
    { 2, 6 },
    { 2, 7 },
    { 6, 10 },  //GPIO6_IO10
};

mraa_board_t*
mraa_apalis()
{
    mraa_board_t* b = (mraa_board_t*) calloc(1, sizeof(mraa_board_t));
    if (b == NULL) {
        return NULL;
    }
    b->platform_name = PLATFORM_NAME_APALIS;
    b->phy_pin_count = sizeof(GPIOS) / (2 * sizeof(int));

    b->pins = (mraa_pininfo_t*) calloc(b->phy_pin_count, sizeof(mraa_pininfo_t));
    if (b->pins == NULL) {
        free(b);
        return NULL;
    }

    b->gpio_count = 0;
    int i;
    for (i = 0; i < b->phy_pin_count; i++) {
        snprintf(b->pins[i].name, MRAA_PIN_NAME_SIZE, "GPIO%d_IO%d", GPIOS[i][0], GPIOS[i][1]);
        b->pins[i].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 0 };
        b->pins[i].gpio.pinmap = ((GPIOS[i][0] - 1) * 32) + GPIOS[i][1];
        b->gpio_count++;
    }

    return b;
}
