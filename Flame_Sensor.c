#include "Flame_Sensor.h"

static uint adc_channel;

void flameSensor_init(uint gpio_pin) {
    adc_init(); 
    adc_gpio_init(gpio_pin); 
    adc_channel = gpio_pin - 26; 
    adc_select_input(adc_channel); 
}

int flameSensor_read() {
    return adc_read(); 
}