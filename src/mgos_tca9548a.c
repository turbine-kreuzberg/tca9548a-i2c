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
#include "mgos_tca9548a.h"

struct mgos_tca9548a {
  struct mgos_i2c *i2c;
  uint8_t i2caddr;
  int reset_gpio;
};

struct mgos_tca9548a *mgos_tca9548a_create(struct mgos_i2c *i2c,
                                           uint8_t i2caddr, int reset_gpio) {
  struct mgos_tca9548a *dev = NULL;

  if (!i2c) {
    return NULL;
  }

  dev = calloc(1, sizeof(struct mgos_tca9548a));
  if (!dev) {
    return NULL;
  }

  memset(dev, 0, sizeof(struct mgos_tca9548a));
  dev->i2caddr = i2caddr;
  dev->i2c = i2c;
  dev->reset_gpio = reset_gpio;

  if (dev->reset_gpio != -1) {
    mgos_gpio_set_mode(dev->reset_gpio, MGOS_GPIO_MODE_OUTPUT);
    mgos_tca9548a_reset(dev);
  }

  if (!mgos_tca9548a_set_channels(dev, 0)) {
    free(dev);
    return 0;
  }
  LOG(LL_INFO, ("TCA9548A initialized %s at I2C 0x%02x",
                (dev->reset_gpio != -1) ? "with reset" : "", dev->i2caddr));
  return dev;
}

bool mgos_tca9548a_reset(struct mgos_tca9548a *dev) {
  if (!dev) {
    return false;
  }

  if (dev->reset_gpio == -1) {
    return false;
  }

  LOG(LL_DEBUG, ("Performing reset TCA9548A on GPIO %d", dev->reset_gpio));
  mgos_gpio_write(dev->reset_gpio, 0);
  mgos_usleep(1);  // t_W(L) min 6ns
  mgos_gpio_write(dev->reset_gpio, 1);

  return true;
}

bool mgos_tca9548a_destroy(struct mgos_tca9548a **dev) {
  if (!*dev) {
    return false;
  }

  free(*dev);
  *dev = NULL;
  return true;
}

bool mgos_tca9548a_set_channels(struct mgos_tca9548a *dev, uint8_t channels) {
  if (!dev) {
    return false;
  }

  if (!mgos_i2c_write(dev->i2c, dev->i2caddr, &channels, 1, true)) {
    LOG(LL_ERROR, ("Could not set TCA9548A channels"));
    return false;
  }

  return true;
}

bool mgos_tca9548a_get_channels(struct mgos_tca9548a *dev, uint8_t *channels) {
  if (!dev) {
    return false;
  }

  if (!mgos_i2c_read(dev->i2c, dev->i2caddr, &channels, 1, true)) {
    LOG(LL_ERROR, ("Could not read TCA9548A channels"));
    return false;
  }

  return true;
}

// Mongoose OS library initialization
bool mgos_tca9548a_i2c_init(void) {
  return true;
}