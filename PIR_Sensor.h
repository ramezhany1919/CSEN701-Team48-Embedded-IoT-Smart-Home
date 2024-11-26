#ifndef ir_sensor_h
#define ir_sensor_h
#include <stdio.h>
#include "pico/stdlib.h"

// Define the IR sensor pin
#define IR_SENSOR_PIN 4

// Function prototypes
void ir_sensor_init(void);
bool ir_sensor_detect(void);

#endif