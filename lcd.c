#include "lcd.h"
#include "pico/stdlib.h"
#include <string.h>

// Helper function to send a nibble
static void lcd_send_nibble(uint8_t nibble) {
    gpio_put(LCD_D4, nibble & 0x01);
    gpio_put(LCD_D5, (nibble >> 1) & 0x01);
    gpio_put(LCD_D6, (nibble >> 2) & 0x01);
    gpio_put(LCD_D7, (nibble >> 3) & 0x01);
    gpio_put(LCD_E, 1);
    sleep_us(1);  // Enable pulse width
    gpio_put(LCD_E, 0);
    sleep_us(100);  // Wait for LCD to process
}

void lcd_send_command(uint8_t cmd) {
    gpio_put(LCD_RS, 0);  // Command mode
    lcd_send_nibble(cmd >> 4);  // Send higher nibble
    lcd_send_nibble(cmd & 0x0F);  // Send lower nibble
}

void lcd_send_data(uint8_t data) {
    gpio_put(LCD_RS, 1);  // Data mode
    lcd_send_nibble(data >> 4);  // Send higher nibble
    lcd_send_nibble(data & 0x0F);  // Send lower nibble
}

void lcd_clear(void) {
    lcd_send_command(0x01);  // Clear display
    sleep_ms(2);  // Wait for LCD to clear
}

void lcd_set_cursor(uint8_t row, uint8_t col) {
    uint8_t address = col;
    if (row == 1) address += 0x40;
    lcd_send_command(0x80 | address);
}

void lcd_send_string(const char *str) {
    while (*str) {
        lcd_send_data(*str++);
    }
}

void lcd_init(void) {
    gpio_init(LCD_RS);
    gpio_init(LCD_E);
    gpio_init(LCD_D4);
    gpio_init(LCD_D5);
    gpio_init(LCD_D6);
    gpio_init(LCD_D7);

    gpio_set_dir(LCD_RS, GPIO_OUT);
    gpio_set_dir(LCD_E, GPIO_OUT);
    gpio_set_dir(LCD_D4, GPIO_OUT);
    gpio_set_dir(LCD_D5, GPIO_OUT);
    gpio_set_dir(LCD_D6, GPIO_OUT);
    gpio_set_dir(LCD_D7, GPIO_OUT);

    // Initialization sequence
    sleep_ms(15);  // Wait for LCD to power up
    lcd_send_nibble(0x03);
    sleep_ms(5);
    lcd_send_nibble(0x03);
    sleep_us(100);
    lcd_send_nibble(0x03);
    lcd_send_nibble(0x02);  // Set to 4-bit mode

    // Function set: 2 lines, 5x8 font
    lcd_send_command(0x28);
    // Display on, cursor off
    lcd_send_command(0x0C);
    // Clear display
    lcd_clear();
    // Entry mode: Increment cursor
    lcd_send_command(0x06);
}