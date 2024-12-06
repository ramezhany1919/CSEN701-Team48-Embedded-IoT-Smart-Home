#include <stdio.h>
#include "pico/stdlib.h"
#include "Flame_Sensor.h"

#define FLAME_SENSOR_PIN 26  
#define LED_PIN 4            
#define THRESHOLD 512        

void setup() {
    stdio_init_all();              
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    flameSensor_init(FLAME_SENSOR_PIN);  
}

int main() {
    setup();
    while (true) {
    }
    return 0;
}
