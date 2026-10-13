#pragma once

#include <SDL3/SDL.h>
#include <cstdint>

SDL_Renderer* createRenderer(SDL_Window* window);

SDL_Texture* createTexture(SDL_Renderer* renderer);

void updateTexture(
    SDL_Texture* texture,
    uint32_t* framebuffer
);

void drawFramebuffer(
    SDL_Renderer* renderer,
    SDL_Texture* texture
);

void destroyRenderer(
    SDL_Renderer* renderer,
    SDL_Texture* texture
);