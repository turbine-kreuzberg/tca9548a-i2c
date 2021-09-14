/*
 * Copyright 2021 Turbine Kreuzberg
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "mgos.h"
#include "mgos_i2c.h"

#define MGOS_TCA9548A_I2C_ADDR0 (0x70)
#define MGOS_TCA9548A_I2C_ADDR1 (0x71)
#define MGOS_TCA9548A_I2C_ADDR2 (0x72)
#define MGOS_TCA9548A_I2C_ADDR3 (0x73)
#define MGOS_TCA9548A_I2C_ADDR4 (0x74)
#define MGOS_TCA9548A_I2C_ADDR5 (0x75)
#define MGOS_TCA9548A_I2C_ADDR6 (0x76)
#define MGOS_TCA9548A_I2C_ADDR7 (0x77)

#define MGOS_TCA9548_CHANNEL0 (0x01)
#define MGOS_TCA9548_CHANNEL1 (0x02)
#define MGOS_TCA9548_CHANNEL2 (0x04)
#define MGOS_TCA9548_CHANNEL3 (0x08)
#define MGOS_TCA9548_CHANNEL4 (0x10)
#define MGOS_TCA9548_CHANNEL5 (0x20)
#define MGOS_TCA9548_CHANNEL6 (0x40)
#define MGOS_TCA9548_CHANNEL7 (0x80)

#ifdef __cplusplus
extern "C" {
#endif

struct mgos_tca9548a;

/**
 * Initialize a TCA9548A on the I2C bus `i2c` at address specified in `i2caddr`,
 * upon success a new `struct mgos_tca9548a` is allocated and returned. 
 * If the device could not be initialized, NULL is returned.
 * 
 * If `reset_gpio` is not -1 it will configure the pin as output and use it to reset the device.
 * After reset all channels are set to off
 */

struct mgos_tca9548a *mgos_tca9548a_create(struct mgos_i2c *i2c, uint8_t i2caddr, int reset_gpio);

/**
 * Reset TCA9548A if reset_gpio is configured
 */
bool mgos_tca9548a_reset(struct mgos_tca9548a *dev);

/**
 * Destroy the data structure associated with a TCA9548A device. The reference
 * to the pointer of the `struct mgos_tca9548a` has to be provided, and upon
 * successful destruction, its associated memory will be freed and the pointer
 * set to NULL.
 */
bool mgos_tca9548a_destroy(struct mgos_tca9548a **dev);

/**
 * Set TCA9548A channels to `channels` state. Each bit on `channels` will set the 
 * corresponding channel to on(1) or off(0).
 */
bool mgos_tca9548a_set_channels(struct mgos_tca9548a *dev, uint8_t channels);

/**
 * Get TCA9548A channels current state
 */
bool mgos_tca9548a_get_channels(struct mgos_tca9548a *dev, uint8_t *channels);

#ifdef __cplusplus
}
#endif