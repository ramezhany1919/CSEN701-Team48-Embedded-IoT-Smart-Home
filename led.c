#include "led.h"


void led_init(uint pin) {               
    gpio_init(pin);             
    gpio_set_dir(pin, GPIO_OUT); 
}


void led_on(uint pin) {
    gpio_put(pin, true); 
   
}


void led_off(uint pin) {
    gpio_put(pin, false);
    
}


void led_toggle(uint pin) {
    gpio_put(pin, !gpio_get(pin));  
    
}
