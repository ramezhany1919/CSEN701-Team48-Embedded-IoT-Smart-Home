#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "Servo_Motor.h"
#include "led.h"
#include "Dc_Motor.h"
#include "Buzzer.h"
#include "Dc_Motor.h"
#include "Flame_Sensor.h"
#include "lcd.h"
#include "led.h"
#include "PIR_Sensor.h"
#include "Servo_Motor.h"


//ALL SERVO MOTORS
#define GARAGE_SERVO_PIN_WIFI 27  // Replace 15 with the actual GPIO pin number you are using
#define WINDOW_SERVO_PIN_WIFI 0  // Replace 15 with the actual GPIO pin number you are using
//ALL LEDS
#define FLAME_SENSOR_LED_PIN 16  // Replace 15 with the actual GPIO pin number you are using
#define ENTRANCE_LED_PIN 14
//DC MOTOR PINS
#define DC_MOTOR_DIR_PIN1_WIFI 6
#define DC_MOTOR_DIR_PIN2_WIFI 7
#define DC_MOTOR_PWM_PIN_WIFI 1

//BUZZER PIN
#define BUZZER_PIN 28

//ALL PIR SENSORS
#define GARAGE_PIR_SENSOR_PIN 17
#define ENTRANCE_PIR_SENSOR_PIN 2

//ALL FLAME SENSORS
#define FLAME_SENSOR_PIN 3

// Global variables
bool garage_is_open = false;
uint64_t last_web_command_time = 0;

//Boolean FireSystem
bool flame_detected_function = false;

// CGI handler which is run when a request for /led.cgi is detected

// CGI handler for controlling the garage door
const char * cgi_garage_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) {
    setServo(GARAGE_SERVO_PIN_WIFI,800);
    last_web_command_time = to_ms_since_boot(get_absolute_time());  // Update the last command time
    for (int i = 0; i < iNumParams; i++) {
        if (strcmp(pcParam[i], "garage") == 0) {
            if (strcmp(pcValue[i], "1") == 0) {
                garage_is_open = true;
                setMillis(GARAGE_SERVO_PIN_WIFI,300); // Example position to open
            } else if (strcmp(pcValue[i], "0") == 0) {
                garage_is_open = false;
                setMillis(GARAGE_SERVO_PIN_WIFI,1250);  // Example position to close
            }
        }
    }
    return "/index.shtml";  // Redirect to home page after action
}

const char * cgi_window_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) {
    setServo(WINDOW_SERVO_PIN_WIFI,800);
    for (int i = 0; i < iNumParams; i++) {
        if (strcmp(pcParam[i], "window") == 0) {
            if (strcmp(pcValue[i], "1") == 0) {
                setMillis(WINDOW_SERVO_PIN_WIFI,1250); // Example position to open
            } else if (strcmp(pcValue[i], "0") == 0) {
                setMillis(WINDOW_SERVO_PIN_WIFI,500);  // Example position to close
            }
        }
    }
    return "/index.shtml";  // Redirect to home page after action
}

// CGI handler for turning the LED on
// CGI handler for controlling the LED
const char * cgi_led_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) {
    led_init(ENTRANCE_LED_PIN);  // Initialize the LED
    // Loop through each parameter
    for (int i = 0; i < iNumParams; i++) {
        if (strcmp(pcParam[i], "led") == 0) {  // Check if the parameter name is "led"
            if (strcmp(pcValue[i], "1") == 0) {
                led_on(ENTRANCE_LED_PIN);  // Turn LED on
            } else if (strcmp(pcValue[i], "0") == 0) {
                led_off(ENTRANCE_LED_PIN);  // Turn LED off
            }
            break;  // Exit the loop after processing the "led" parameter
        }
    }
    return "/index.shtml";  // Redirect to home page after action
}


const char * cgi_fan_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) {
   motor_init(DC_MOTOR_PWM_PIN_WIFI,DC_MOTOR_DIR_PIN1_WIFI,DC_MOTOR_DIR_PIN2_WIFI);
    // Loop through each parameter
    for (int i = 0; i < iNumParams; i++) {
        if (strcmp(pcParam[i], "fan") == 0) {  // Check if the parameter name is "led"
            if (strcmp(pcValue[i], "1") == 0) {
                motor_control(100,true,DC_MOTOR_PWM_PIN_WIFI,DC_MOTOR_DIR_PIN1_WIFI,DC_MOTOR_DIR_PIN2_WIFI); //level-1-fan
            } else if (strcmp(pcValue[i], "2") == 0) {
                motor_control(160,true,DC_MOTOR_PWM_PIN_WIFI,DC_MOTOR_DIR_PIN1_WIFI,DC_MOTOR_DIR_PIN2_WIFI); //level-2-fan
            }
            else if (strcmp(pcValue[i], "3") == 0) {
                motor_control(255,true,DC_MOTOR_PWM_PIN_WIFI,DC_MOTOR_DIR_PIN1_WIFI,DC_MOTOR_DIR_PIN2_WIFI); //level-3-fan
            }
            else if (strcmp(pcValue[i], "0") == 0) {
                motor_control(0,true,DC_MOTOR_PWM_PIN_WIFI,DC_MOTOR_DIR_PIN1_WIFI,DC_MOTOR_DIR_PIN2_WIFI); //level-0-fan
            }
            break;  // Exit the loop after processing the "led" parameter
        }
    }
    return "/index.shtml";  // Redirect to home page after action
}

const char * cgi_safe_mode_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) {
    for (int i = 0; i < iNumParams; i++) {
        if (strcmp(pcParam[i], "safeMode") == 0) {
            if (strcmp(pcValue[i], "1") == 0) {
              flame_detected_function=false; // Example position to open
            } 
        }
    }
    return "/index.shtml";  // Redirect to home page after action
}



// tCGI Struct
// Fill this with all of the CGI requests and their respective handlers
static const tCGI cgi_handlers[] = {
    { "/led.cgi", cgi_led_handler },
    { "/garage.cgi", cgi_garage_handler },
    { "/window.cgi", cgi_window_handler },
    { "/fan.cgi", cgi_fan_handler } ,
    { "/safeMode.cgi", cgi_safe_mode_handler }

    
};


void cgi_init(void)
{
    http_set_cgi_handlers(cgi_handlers,5);
}