#ifndef I2C_HELPER_H
#define I2C_HELPER_H

#include "hardware/i2c.h"

#define I2C_PORT i2c0         // Default I2C port
#define SDA_PIN 5            // Default SDA pin
#define SCL_PIN 21             // Default SCL pin

void i2c_init_custom();

#endif
