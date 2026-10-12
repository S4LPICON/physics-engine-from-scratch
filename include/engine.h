#pragma once

#include <SDL3/SDL.h>
#include "input/input.h"
#include "engine/scene.h"

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

public:
    Engine(/* args */);
    ~Engine();
    void init();
    void run();
    void stop();
    void loadScene(Scene* scene);
    
    
};

