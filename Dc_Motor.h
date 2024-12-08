#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"  


  

void motor_init(uint MOTOR_PWM_PIN,uint MOTOR_DIR_PIN1,uint MOTOR_DIR_PIN2);
void motor_control(uint16_t speed, bool forward,uint MOTOR_PWM_PIN,uint MOTOR_DIR_PIN1,uint MOTOR_DIR_PIN2);

#endif // MOTOR_CONTROL_H