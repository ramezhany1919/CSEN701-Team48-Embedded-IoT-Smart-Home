#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include "pico/stdlib.h"
//


void temperature_sensor_init(void);
float read_temperature(void);

#endif
