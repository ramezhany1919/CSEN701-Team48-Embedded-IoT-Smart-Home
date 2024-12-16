#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/netif.h"
#include "lwip/dhcp.h"
#include "lwip/apps/httpd.h"
#include "lwipopts.h"
#include "ssi.h"
#include "cgi.h"
#include "lcd.h"
#include "hardware/irq.h"



// WIFI Credentials - take care if pushing to GitHub!
const char WIFI_SSID[] = "Omar3";
const char WIFI_PASSWORD[] = "thinktank@3";


void init_wifi(){
    cyw43_arch_init();  // Initialize the CYW43 WiFi/BT driver
    cyw43_arch_enable_sta_mode();  // Enable station mode

    // Connect to the Wi-Fi network - loop until connected
    while (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK , 30000) != 0) {
        printf("Attempting to connect...\n");
    }
    printf("Connected!\n");

    // Access the default network interface
    struct netif* netif = netif_default;
    if (netif != NULL && netif_is_up(netif) && netif_is_link_up(netif)) {
        const ip4_addr_t* ip_address = netif_ip4_addr(netif);
        printf("IP Address: %s\n", ip4addr_ntoa(ip_address));
    } else {
        printf("Network interface is not up or link is down.\n");
    }

    // Initialize web server
    httpd_init();
    printf("HTTP server initialized\n");

    // Configure SSI and CGI handlers
    ssi_init();
    printf("SSI Handler initialized\n");
    cgi_init();
    printf("CGI Handler initialized\n");
}


void setup_compontents(){
    //LED INIT
    led_init(ENTRANCE_LED_PIN);
    led_init(FLAME_SENSOR_LED_PIN);
    //BUZZER INIT
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    //FLAME SENSOR INIT
    flameSensor_init(FLAME_SENSOR_PIN);
    //PIR SENSOR INIT
    ir_sensor_init(GARAGE_PIR_SENSOR_PIN);
    ir_sensor_init(ENTRANCE_PIR_SENSOR_PIN);
    setServo(GARAGE_SERVO_PIN_WIFI,0);
   
}




//Fire System GPIO interrupt
void gpio_isr(uint gpio, uint32_t events) {
   bool flame_detected = gpio_get(FLAME_SENSOR_PIN);
  
    if (gpio == FLAME_SENSOR_PIN) {
        bool is_fire_detected = gpio_get(FLAME_SENSOR_PIN); // Check if fire is detected
        if (!is_fire_detected) {
            // Fire detected: turn on LED and buzzer
            gpio_put(FLAME_SENSOR_LED_PIN, true);
            gpio_put(BUZZER_PIN, true);
            sleep_ms(100);
        } else {
            // No fire detected: turn off LED and buzzer
            gpio_put(FLAME_SENSOR_LED_PIN, false);
            gpio_put(BUZZER_PIN, false);
        }
    }
}

void flame_alaram(bool flame_detected_func){
  if(flame_detected_func){
    gpio_put(FLAME_SENSOR_LED_PIN, true);
    gpio_put(BUZZER_PIN, true);
  }
  else{
    gpio_put(FLAME_SENSOR_LED_PIN, false);
    gpio_put(BUZZER_PIN, false);
  }
}



int main() {
    stdio_init_all();
    //INIT-WIFI SETUP
    init_wifi();
    lcd_init();
    lcd_set_cursor(0,0);
    lcd_send_string("Welcome Home");

    setup_compontents();
    //GPIO INTERRUPT


  while (1) {
    int flame_read=flameSensor_read(FLAME_SENSOR_PIN);
    if(!flame_read){
      flame_detected_function = true;
    }
    flame_alaram(flame_detected_function);
   

    int ir_entrance = ir_sensor_detect(ENTRANCE_PIR_SENSOR_PIN);
    printf("IR Entrance sensor state: %d\n", ir_entrance);  // Print the state of the entrance sensor

    int ir_garage = ir_sensor_detect(GARAGE_PIR_SENSOR_PIN);
    printf("IR Garage sensor state: %d\n", ir_garage);  // Print the state of the garage sensor

    if (!ir_entrance) {
        printf("Entrance sensor detected no motion, turning LED on.\n");
        led_on(ENTRANCE_LED_PIN);
    } else {
        printf("Entrance sensor detected motion, turning LED off.\n");
        led_off(ENTRANCE_LED_PIN);
    }

    // Check if the garage sensor should control the door
    if (to_ms_since_boot(get_absolute_time()) - last_web_command_time > 5000) {  // No web command for the last 5 seconds
        if (!ir_garage && !garage_is_open) {
            printf("Garage sensor detected no car, opening garage door.\n");
            setServo(GARAGE_SERVO_PIN_WIFI, 300);  // Open the garage
            garage_is_open = true;
        } else if (ir_garage && garage_is_open) {
            printf("Garage sensor detected a car, closing garage door.\n");
            setServo(GARAGE_SERVO_PIN_WIFI, 1250);  // Close the garage
            garage_is_open = false;
        }
    }
}

return 0;

}
