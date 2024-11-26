#ifndef FLAME_SENSOR_H
#define FLAME_SENSOR_H

#include "pico/stdlib.h"
#include "hardware/adc.h"

void flameSensor_init(uint gpio_pin); 
int flameSensor_read(); 

#endif 