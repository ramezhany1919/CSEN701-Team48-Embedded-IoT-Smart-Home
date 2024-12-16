/* lcd.h - Header file */

#ifndef LCD_H
#define LCD_H

#include <stdint.h>
#include "pico/stdlib.h"

// Define GPIO pins for LCD
#define LCD_RS 4  // Register Select pin
#define LCD_E  26  // Enable pin
#define LCD_D4 27  // Data pin 4
#define LCD_D5 28  // Data pin 5
#define LCD_D6 29  // Data pin 6
#define LCD_D7 12  // Data pin 7

// Function prototypes
void lcd_init(void);
void lcd_clear(void);
void lcd_send_command(uint8_t cmd);
void lcd_send_data(uint8_t data);
void lcd_send_string(const char *str);
void lcd_set_cursor(uint8_t row, uint8_t col);

#endif