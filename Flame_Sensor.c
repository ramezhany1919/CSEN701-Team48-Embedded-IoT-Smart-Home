#include "Flame_Sensor.h"

static uint adc_channel;

void flameSensor_init(uint gpio_pin) {
    gpio_init(gpio_pin);
    gpio_set_dir(gpio_pin, GPIO_IN);
   gpio_pull_up(gpio_pin); // Explicitly ensure the pull-up is enabled if needed

}

int flameSensor_read(uint gpio_pin) {
    return gpio_get(gpio_pin);
}