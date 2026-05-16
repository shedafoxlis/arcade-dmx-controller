#ifndef SCENE_H
#define SCENE_H

#include <Arduino.h>
#include "../config.h"

struct Scene {
    uint8_t id;
    char name[32];
    uint8_t colors[DMX_GROUPS][3];  // RGB for each group
};

class SceneManager {
public:
    static constexpr uint8_t NUM_SCENES = 10;
    
    SceneManager() {
        // Initialize default scenes
        scenes[0] = {0, "Red",      {{255,0,0},   {255,0,0},   {255,0,0},   {255,0,0},   {255,0,0}}};
        scenes[1] = {1, "Green",    {{0,255,0},   {0,255,0},   {0,255,0},   {0,255,0},   {0,255,0}}};
        scenes[2] = {2, "Blue",     {{0,0,255},   {0,0,255},   {0,0,255},   {0,0,255},   {0,0,255}}};
        scenes[3] = {3, "White",    {{255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}}};
        scenes[4] = {4, "Cyan",     {{0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}}};
        scenes[5] = {5, "Magenta",  {{255,0,255}, {255,0,255}, {255,0,255}, {255,0,255}, {255,0,255}}};
        scenes[6] = {6, "Yellow",   {{255,255,0}, {255,255,0}, {255,255,0}, {255,255,0}, {255,255,0}}};
        scenes[7] = {7, "Orange",   {{255,165,0}, {255,165,0}, {255,165,0}, {255,165,0}, {255,165,0}}};
        scenes[8] = {8, "Purple",   {{128,0,128}, {128,0,128}, {128,0,128}, {128,0,128}, {128,0,128}}};
        scenes[9] = {9, "Blackout", {{0,0,0},     {0,0,0},     {0,0,0},     {0,0,0},     {0,0,0}}};
    }
    
    Scene* getScene(uint8_t id) {
        if (id < NUM_SCENES) return &scenes[id];
        return nullptr;
    }
    
    Scene* getScenes() { return scenes; }
    
private:
    Scene scenes[NUM_SCENES];
};

#endif // SCENE_H
