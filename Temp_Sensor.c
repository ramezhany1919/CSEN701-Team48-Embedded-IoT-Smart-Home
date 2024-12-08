#include "Temp_Sensor.h"
#include "hardware/adc.h"

void temperature_sensor_init(void) {
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);
}

float read_temperature(void) {
    uint16_t result = adc_read();
    float voltage = result * 3.3f / (1 << 12); // Convert ADC value to voltage
    float temperature = 27 - (voltage - 0.706) / 0.001721; // Simplified formula to calculate temperature
    return temperature;
}