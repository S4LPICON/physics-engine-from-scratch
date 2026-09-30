#pragma once

constexpr int SCALE = 2;

#include <SDL3/SDL.h>

SDL_Window* createWindow();
void destroyWindow(SDL_Window* window);