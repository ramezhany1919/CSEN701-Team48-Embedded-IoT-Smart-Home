#ifndef SERVO_H
#define SERVO_H

#include "pico/stdlib.h"

void setMillis(uint servoPin , float millis);
void setServo(uint servoPin, float startMillis);

#endif