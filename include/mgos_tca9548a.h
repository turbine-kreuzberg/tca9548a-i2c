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

#define MGOS_TCA9548_CHANNEL0 (1 << 0)
#define MGOS_TCA9548_CHANNEL1 (1 << 1)
#define MGOS_TCA9548_CHANNEL2 (1 << 2)
#define MGOS_TCA9548_CHANNEL3 (1 << 3)
#define MGOS_TCA9548_CHANNEL4 (1 << 4)
#define MGOS_TCA9548_CHANNEL5 (1 << 5)
#define MGOS_TCA9548_CHANNEL6 (1 << 6)
#define MGOS_TCA9548_CHANNEL7 (1 << 7)

#ifdef __cplusplus
extern "C" {
#endif

struct mgos_tca9548a;

struct mgos_tca9548a *mgos_tca9548a_create(struct mgos_i2c *i2c,
                                           uint8_t i2caddr, int reset_gpio);
bool mgos_tca9548a_reset(struct mgos_tca9548a *dev);
bool mgos_tca9548a_destroy(struct mgos_tca9548a **dev);

bool mgos_tca9548a_set_channels(struct mgos_tca9548a *dev, uint8_t channels);
bool mgos_tca9548a_get_channels(struct mgos_tca9548a *dev, uint8_t *channels);

#ifdef __cplusplus
}
#endif