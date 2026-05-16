#ifndef PROGRAM_H
#define PROGRAM_H

#include <Arduino.h>
#include "../config.h"

enum class EffectType {
    RAINBOW_CHASE,
    PULSE,
    STROBE_WHITE,
    STROBE_COLOR,
    DJ_MIX,
    SLOW_FADE
};

struct Program {
    uint8_t id;
    char name[32];
    EffectType type;
};

class ProgramManager {
public:
    static constexpr uint8_t NUM_PROGRAMS = 6;
    
    ProgramManager() {
        programs[0] = {0, "Rainbow Chase", EffectType::RAINBOW_CHASE};
        programs[1] = {1, "Pulse", EffectType::PULSE};
        programs[2] = {2, "Strobe White", EffectType::STROBE_WHITE};
        programs[3] = {3, "Strobe Color", EffectType::STROBE_COLOR};
        programs[4] = {4, "DJ Mix", EffectType::DJ_MIX};
        programs[5] = {5, "Slow Fade", EffectType::SLOW_FADE};
    }
    
    void updateEffect(uint8_t groupId, uint8_t programId, uint16_t bpm, uint8_t* dmxBuffer) {
        if (programId >= NUM_PROGRAMS) return;
        
        Program& prog = programs[programId];
        unsigned long now = millis();
        
        switch (prog.type) {
            case EffectType::RAINBOW_CHASE: {
                uint8_t hue = (now / 10) % 256;
                uint8_t offset = groupId * CHANNELS_PER_GROUP;
                // Update DMX for rainbow chase
                break;
            }
            case EffectType::PULSE: {
                uint8_t brightness = 128 + 127 * sin(now / 500.0f);
                // Update brightness
                break;
            }
            case EffectType::STROBE_WHITE: {
                uint16_t strobeSpeed = (300 * bpm) / 120;  // Adjust for BPM
                bool strobeOn = (now % strobeSpeed) < (strobeSpeed / 2);
                // Update strobe
                break;
            }
            default:
                break;
        }
    }
    
    Program* getProgram(uint8_t id) {
        if (id < NUM_PROGRAMS) return &programs[id];
        return nullptr;
    }
    
    Program* getPrograms() { return programs; }
    
private:
    Program programs[NUM_PROGRAMS];
};

#endif // PROGRAM_H
