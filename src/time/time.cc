#include "time/time.h"
#include <iostream>
#include <SDL3/SDL.h>

float Time::dt = 0.0f;

void Time::update()
{
    static Uint64 previousTime = SDL_GetPerformanceCounter();

    Uint64 currentTime = SDL_GetPerformanceCounter();

    Uint64 elapsed = currentTime - previousTime;
    Uint64 frequency = SDL_GetPerformanceFrequency();

    dt = static_cast<float>(elapsed) /
         static_cast<float>(frequency);

    previousTime = currentTime;
}

float Time::deltaTime()
{
    return dt;
}