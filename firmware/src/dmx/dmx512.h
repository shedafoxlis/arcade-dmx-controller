#ifndef DMX512_H
#define DMX512_H

#include <Arduino.h>
#include "../config.h"

class DMX512 {
public:
    static constexpr uint16_t CHANNELS = 512;
    
    void init() {
        Serial.println("[DMX] Initializing...");
        Serial2.begin(DMX_BAUD, SERIAL_8N2, DMX_RX, DMX_TX);
        pinMode(DMX_DE, OUTPUT);
        digitalWrite(DMX_DE, HIGH);
    }
    
    void send() {
        digitalWrite(DMX_DE, HIGH);
        delayMicroseconds(100);
        // Send DMX break (low for 88-200 microseconds)
        Serial2.write(0);
        delayMicroseconds(100);
        // Send 512 channels
        for (int i = 0; i < CHANNELS; i++) {
            Serial2.write(buffer[i]);
        }
    }
    
    void setChannel(uint16_t channel, uint8_t value) {
        if (channel < CHANNELS) {
            buffer[channel] = value;
        }
    }
    
    uint8_t getChannel(uint16_t channel) {
        if (channel < CHANNELS) return buffer[channel];
        return 0;
    }
    
    void setGroup(uint8_t group, const uint8_t* values, uint16_t len) {
        uint16_t offset = group * CHANNELS_PER_GROUP;
        for (uint16_t i = 0; i < len && (offset + i) < CHANNELS; i++) {
            buffer[offset + i] = values[i];
        }
    }
    
    uint8_t* getBuffer() { return buffer; }
    void clearBuffer() { memset(buffer, 0, CHANNELS); }
    
private:
    uint8_t buffer[CHANNELS] = {0};
};

#endif // DMX512_H
