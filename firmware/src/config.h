#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>

// ===== DISPLAY PINS (TFT ILI9341) =====
#define TFT_CS     34   // D5
#define TFT_DC     35   // D6
#define TFT_MOSI   32   // SPI1_D7
#define TFT_MISO   37   // SPI1_D4
#define TFT_CLK    36   // SPI1_CLK
#define TFT_RST    33   // D9
#define TFT_BL     26   // Backlight PWM

// ===== TOUCH PINS (XPT2046) =====
#define TOUCH_CS   39   // D7
#define TOUCH_MOSI 11   // SPI2_D0
#define TOUCH_MISO 9    // SPI2_D1
#define TOUCH_CLK  10   // SPI2_CLK
#define TOUCH_IRQ  40   // D8 (optional)

// ===== DMX PINS (MAX485) =====
#define DMX_TX     4    // UART1_TX
#define DMX_RX     3    // UART1_RX (not used in output mode)
#define DMX_DE     5    // Direction Enable (HIGH=TX, LOW=RX)
#define DMX_BAUD   250000

// ===== BUTTON PINS =====
#define BTN_SCENE_1  13
#define BTN_SCENE_2  14
#define BTN_SCENE_3  38
#define BTN_SCENE_4  41
#define BTN_SCENE_5  42

// ===== DISPLAY CONFIG =====
#define SCREEN_WIDTH   320
#define SCREEN_HEIGHT  240  // or 480 for 3.2"
#define TFT_ROTATION   1    // 0-3

// ===== DMX CONFIG =====
#define DMX_CHANNELS     512
#define DMX_GROUPS       5
#define CHANNELS_PER_GROUP 102  // ~512/5

// ===== WIFI CONFIG =====
#define WIFI_SSID      "ARCADE_DMX"
#define WIFI_PASSWORD  "12345678"
#define WIFI_MODE      1  // 0=STA, 1=AP

// ===== STORAGE =====
#define SPIFFS_MOUNT_PATH "/spiffs"
#define CONFIG_FILE_PATH  "/spiffs/config.json"
#define SCENES_PATH       "/spiffs/scenes/"
#define SHOWS_PATH        "/spiffs/shows/"

// ===== TIMING =====
#define DMX_UPDATE_RATE 40    // Hz (25ms)
#define UI_UPDATE_RATE  30    // Hz (33ms)
#define WEB_PORT        80

// ===== FEATURES =====
#define ENABLE_TOUCH    1
#define ENABLE_BUTTONS  1
#define ENABLE_DMX      1
#define ENABLE_WEB      1
#define ENABLE_RECORDER 1

// ===== DEBUG =====
#define DEBUG_SERIAL    1
#define DEBUG_LEVEL     3  // 0=off, 3=verbose

#endif // CONFIG_H
