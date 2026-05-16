#ifndef TFT_DISPLAY_H
#define TFT_DISPLAY_H

#include <Arduino.h>
#include "../config.h"

class TFTDisplay {
public:
    void init() {
        // Initialize SPI and TFT display
        // Using TFT_eSPI library
    }
    
    void showBootscreen() {
        // Display splash screen
    }
    
    void clearScreen(uint16_t color = 0x0000) {
        // Clear display
    }
    
    void drawPixel(int16_t x, int16_t y, uint16_t color) {
        // Draw single pixel
    }
    
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
        // Draw rectangle outline
    }
    
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
        // Draw filled rectangle
    }
    
    void drawText(int16_t x, int16_t y, const char* text, uint16_t fg, uint16_t bg) {
        // Draw text
    }
    
    void setBacklight(uint8_t brightness) {
        // PWM backlight control (0-255)
        analogWrite(TFT_BL, brightness);
    }
    
    uint16_t color565(uint8_t r, uint8_t g, uint8_t b) {
        return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    }
};

// Color constants (RGB565)
#define BLACK   0x0000
#define WHITE   0xFFFF
#define RED     0xF800
#define GREEN   0x07E0
#define BLUE    0x001F
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define ORANGE  0xFD20
#define PURPLE  0x8010

#endif // TFT_DISPLAY_H
