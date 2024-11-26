#include "hardware/i2c.h"
#include "pico/stdlib.h"

#define I2C_PORT i2c0
#define SDA_PIN 5
#define SCL_PIN 21

void i2c_init_custom() {
    i2c_init(I2C_PORT, 100000); // Initialize I2C with 100 kHz frequency
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C); // Set SDA pin
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C); // Set SCL pin
    gpio_pull_up(SDA_PIN); // Enable pull-up resistor for SDA
    gpio_pull_up(SCL_PIN); // Enable pull-up resistor for SCL
}
