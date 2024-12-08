#include "Dc_Motor.h"
#include <stdio.h>
uint slice_num;

void motor_init(uint MOTOR_PWM_PIN,uint MOTOR_DIR_PIN1,uint MOTOR_DIR_PIN2) {
    
    gpio_init(MOTOR_DIR_PIN1);
    gpio_set_dir(MOTOR_DIR_PIN1, GPIO_OUT);
    gpio_init(MOTOR_DIR_PIN2);
    gpio_set_dir(MOTOR_DIR_PIN2, GPIO_OUT);

    
    gpio_set_function(MOTOR_PWM_PIN, GPIO_FUNC_PWM);

    
    slice_num = pwm_gpio_to_slice_num(MOTOR_PWM_PIN);

    
    pwm_set_wrap(slice_num, 255);          
    pwm_set_clkdiv(slice_num, 4.0f);        

    
    pwm_set_enabled(slice_num, true);
}

void motor_control(uint16_t speed, bool forward,uint MOTOR_PWM_PIN,uint MOTOR_DIR_PIN1,uint MOTOR_DIR_PIN2) {
    
    if (speed > 255) speed = 255;

    // Set motor direction
    if (forward) {
        gpio_put(MOTOR_DIR_PIN1, 1);
        gpio_put(MOTOR_DIR_PIN2, 0);
    } else {
        gpio_put(MOTOR_DIR_PIN1, 0);
        gpio_put(MOTOR_DIR_PIN2, 1);
    }
printf("Speed set to %d, Forward: %d, Slice: %u\n", speed, forward,slice_num);

   
uint slice_num = pwm_gpio_to_slice_num(MOTOR_PWM_PIN);
uint channel = pwm_gpio_to_channel(MOTOR_PWM_PIN);
pwm_set_chan_level(slice_num, channel, speed);
}   