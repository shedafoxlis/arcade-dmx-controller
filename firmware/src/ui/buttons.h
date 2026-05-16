#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>
#include "../config.h"

typedef void (*ButtonCallback)(uint8_t btn);

class ButtonController {
public:
    void init() {
        pinMode(BTN_SCENE_1, INPUT_PULLUP);
        pinMode(BTN_SCENE_2, INPUT_PULLUP);
        pinMode(BTN_SCENE_3, INPUT_PULLUP);
        pinMode(BTN_SCENE_4, INPUT_PULLUP);
        pinMode(BTN_SCENE_5, INPUT_PULLUP);
        
        memset(lastState, HIGH, 5);
        memset(debounceTime, 0, sizeof(debounceTime));
    }
    
    void setCallback(ButtonCallback cb) {
        callback = cb;
    }
    
    void update() {
        uint8_t pins[5] = {BTN_SCENE_1, BTN_SCENE_2, BTN_SCENE_3, BTN_SCENE_4, BTN_SCENE_5};
        unsigned long now = millis();
        
        for (uint8_t i = 0; i < 5; i++) {
            uint8_t state = digitalRead(pins[i]);
            
            if (state != lastState[i] && (now - debounceTime[i]) > 20) {
                lastState[i] = state;
                debounceTime[i] = now;
                
                if (state == LOW && callback) {
                    callback(i);
                }
            }
        }
    }
    
private:
    uint8_t lastState[5];
    unsigned long debounceTime[5];
    ButtonCallback callback = nullptr;
};

#endif // BUTTONS_H
