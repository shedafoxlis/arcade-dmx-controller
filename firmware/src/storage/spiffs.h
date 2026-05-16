#ifndef SPIFFS_H
#define SPIFFS_H

#include <Arduino.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include "../config.h"

class SPIFFSStorage {
public:
    bool init() {
        if (!SPIFFS.begin(true)) {
            Serial.println("[SPIFFS] Mount failed");
            return false;
        }
        Serial.println("[SPIFFS] Mounted successfully");
        return true;
    }
    
    bool saveConfig(const char* configJson) {
        File file = SPIFFS.open(CONFIG_FILE_PATH, "w");
        if (!file) {
            Serial.println("[SPIFFS] Failed to open config file");
            return false;
        }
        file.print(configJson);
        file.close();
        return true;
    }
    
    bool loadConfig(char* buffer, size_t maxLen) {
        File file = SPIFFS.open(CONFIG_FILE_PATH, "r");
        if (!file) {
            Serial.println("[SPIFFS] Config file not found");
            return false;
        }
        size_t len = file.readBytes(buffer, maxLen - 1);
        buffer[len] = '\0';
        file.close();
        return true;
    }
    
    bool saveScene(uint8_t sceneId, const uint8_t* data, uint16_t len) {
        char path[64];
        snprintf(path, sizeof(path), "%sscene_%d.bin", SCENES_PATH, sceneId);
        File file = SPIFFS.open(path, "w");
        if (!file) return false;
        file.write(data, len);
        file.close();
        return true;
    }
    
    bool loadScene(uint8_t sceneId, uint8_t* data, uint16_t maxLen) {
        char path[64];
        snprintf(path, sizeof(path), "%sscene_%d.bin", SCENES_PATH, sceneId);
        File file = SPIFFS.open(path, "r");
        if (!file) return false;
        size_t len = file.readBytes((char*)data, maxLen);
        file.close();
        return len > 0;
    }
    
    uint32_t getFreeSpace() {
        return SPIFFS.totalBytes() - SPIFFS.usedBytes();
    }
};

#endif // SPIFFS_H
