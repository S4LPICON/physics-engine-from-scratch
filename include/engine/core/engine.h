#pragma once

#include "external/obj_loader.h"
#include "engine/tools/texture_loader.h"
#include "resources/texture.h"
#include "engine/components/renderer_component.h"

#include <SDL3/SDL.h>
#include "engine/input/input.h"
#include "engine/objects/generic/scene.h"

class Engine
{
private:
    //scena
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    Input input;

    float deltaTime;

    Scene* scene;
    
    bool profilerEnabled = false;

public:
    Engine(/* args */);
    ~Engine();
    void init();
    void run();
    void stop();
    void loadScene(Scene* scene);
    
    
};

void tempCameraController(Camera& camera, const Input& input, float deltaTime);
