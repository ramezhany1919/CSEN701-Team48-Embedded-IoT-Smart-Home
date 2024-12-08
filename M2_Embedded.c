#include <stdio.h>
#include "pico/stdlib.h"
#include "Buzzer.h"
#include "Dc_Motor.h"
#include "Flame_Sensor.h"
#include "led.h"
#include "PIR_Sensor.h"
#include "Servo_Motor.h"
#include "Temp_Sensor.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"

/*

void setup() {
    stdio_init_all();              
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    flameSensor_init(FLAME_SENSOR_PIN);  
}
*/
int main() {
    setup();
    while (true) {
    }
    return 0;
}
