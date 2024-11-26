#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"  


#define MOTOR_PWM_PIN 29       
#define MOTOR_DIR_PIN1 6      
#define MOTOR_DIR_PIN2 7      

void motor_init(void);
void motor_control(uint16_t speed, bool forward);

#endif // MOTOR_CONTROL_H