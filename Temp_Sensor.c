#include "Temp_Sensor.h"
#include "hardware/adc.h"
#include "pico/stdlib.h"

 
void sensor_init(uint ADC_PIN) {
    adc_init();
    adc_gpio_init(ADC_PIN);
    adc_select_input(0);  
}

float sensor_read_temperature() {
    const float conversion_factor = 3.3f / (1 << 12);  
    uint16_t result = adc_read();
    float voltage = result * conversion_factor;
    float temperature = (voltage - 0.5) * 100.0;
    return temperature;
}
