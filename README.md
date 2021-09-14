# TCA9548A I2C Driver

A Mongoose OS library for TI TCA9548A Low-Voltage 8-Channel I2C Switch with Reset.

## Example application
Two NAU7802 with fixed i2c address share the i2c bus:

```
#include "mgos.h"
#include "mgos_tca9548a.h"
#include "mgos_nau7802.h"

#define I2CMUX_RST_PIN 14

struct mgos_tca9548a *i2cmux;
struct mgos_nau7802 *dev[2];

static void timer_cb(void *user_data) {
  //read nau7802 connected to channel 0
  mgos_tca9548a_set_channels(i2cmux, MGOS_TCA9548_CHANNEL0);
  LOG(LL_INFO, ("channel0 reading=%d", mgos_nau7802_read(dev[0])));

  //read nau7802 connected to channel 1
  mgos_tca9548a_set_channels(i2cmux, MGOS_TCA9548_CHANNEL1);
  LOG(LL_INFO, ("channel 1 reading=%d", mgos_nau7802_read(dev[1])));

  (void) user_data;
}


enum mgos_app_init_result mgos_app_init(void) {
  i2cmux = mgos_tca9548a_create(mgos_i2c_get_global(), MGOS_TCA9548A_I2C_ADDR0, I2CMUX_RST_PIN);

  //init nau7802 connected to channel 0
  mgos_tca9548a_set_channels(i2cmux, MGOS_TCA9548_CHANNEL0);
  dev[0] = mgos_nau7802_create(mgos_i2c_get_global());
  if (dev[0] == NULL) {
    LOG(LL_ERROR, ("Could not create NAU7802 device on channel 0"));
    
    return MGOS_APP_INIT_ERROR;
  }

  //init nau7802 connected to channel 1
  mgos_tca9548a_set_channels(i2cmux, MGOS_TCA9548_CHANNEL1);
  dev[1] = mgos_nau7802_create(mgos_i2c_get_global());
  if (dev[1] == NULL) {
    LOG(LL_ERROR, ("Could not create NAU7802 device on channel 1"));
    
    return MGOS_APP_INIT_ERROR;
  }

  mgos_set_timer(1000, true, timer_cb, 0);

  return MGOS_APP_INIT_SUCCESS;
}
```