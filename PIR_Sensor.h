#ifndef ir_sensor_h
#define ir_sensor_h
#include <stdio.h>
#include "pico/stdlib.h"





void ir_sensor_init(uint IR_SENSOR_PIN);
bool ir_sensor_detect(uint IR_SENSOR_PIN);

#endif