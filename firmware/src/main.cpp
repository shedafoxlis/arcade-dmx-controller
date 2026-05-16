#include <Arduino.h>
#include "config.h"

// Forward declarations
class DMX512 {
public:
    static constexpr uint16_t CHANNELS = 512;
    uint8_t buffer[CHANNELS] = {0};
    
    void init() {
        Serial.println("[DMX] Initializing UART1...");
        Serial2.begin(DMX_BAUD, SERIAL_8N2, DMX_RX, DMX_TX);
        pinMode(DMX_DE, OUTPUT);
        digitalWrite(DMX_DE, HIGH);
        Serial.println("[DMX] UART1 initialized");
    }
    
    void send() {
        digitalWrite(DMX_DE, HIGH);
        // Send DMX break
        Serial2.write(0);
        delay(1);
        // Send channel data
        for (int i = 0; i < CHANNELS; i++) {
            Serial2.write(buffer[i]);
        }
    }
    
    void setChannel(uint16_t ch, uint8_t val) {
        if (ch < CHANNELS) buffer[ch] = val;
    }
    
    uint8_t* getBuffer() { return buffer; }
};

DMX512 dmx;

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("\n\n=== ARCADE DMX Controller v0.1.0 ===");
    Serial.println("ESP32-S2 Mini Firmware");
    Serial.println("Loading...");
    
    // Initialize storage
    Serial.println("[SETUP] Initializing SPIFFS...");
    // SPIFFS mount code here
    
    // Initialize display
    Serial.println("[SETUP] Initializing TFT display...");
    // Display init code here
    
    // Initialize touch
    Serial.println("[SETUP] Initializing touch screen...");
    // Touch init code here
    
    // Initialize DMX
    Serial.println("[SETUP] Initializing DMX512...");
    dmx.init();
    
    // Initialize buttons
    Serial.println("[SETUP] Initializing buttons...");
    pinMode(BTN_SCENE_1, INPUT_PULLUP);
    pinMode(BTN_SCENE_2, INPUT_PULLUP);
    pinMode(BTN_SCENE_3, INPUT_PULLUP);
    pinMode(BTN_SCENE_4, INPUT_PULLUP);
    pinMode(BTN_SCENE_5, INPUT_PULLUP);
    
    // Initialize Web Server
    Serial.println("[SETUP] Starting Web Server...");
    // Web server init code here
    
    Serial.println("\n[SETUP] All systems initialized!");
    Serial.printf("[INFO] Free heap: %d bytes\n", ESP.getFreeHeap());
    delay(2000);
}

unsigned long lastDMXUpdate = 0;
unsigned long lastUIUpdate = 0;

void loop() {
    unsigned long now = millis();
    
    // Update buttons
    if (!digitalRead(BTN_SCENE_1)) {
        Serial.println("[BTN] Scene 1 pressed");
        // Set scene 1
        dmx.setChannel(0, 255);
        delay(200);
    }
    
    // Update DMX (40Hz)
    if (now - lastDMXUpdate >= 25) {
        dmx.send();
        lastDMXUpdate = now;
    }
    
    // Update UI (30Hz)
    if (now - lastUIUpdate >= 33) {
        // Update display, buttons, etc
        lastUIUpdate = now;
    }
    
    delay(1);
}
