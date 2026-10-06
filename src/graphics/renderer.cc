#include "graphics/renderer.h"
#include "graphics/framebuffer.h"

SDL_Renderer* createRenderer(SDL_Window* window)
{
    return SDL_CreateRenderer(window, nullptr);
}

SDL_Texture* createTexture(SDL_Renderer* renderer)
{
    SDL_Texture* texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        WIDTH,
        HEIGHT
    );

    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    return texture;
}

void updateTexture(
    SDL_Texture* texture,
    uint32_t* framebuffer
)
{
    SDL_UpdateTexture(
        texture,
        nullptr,
        framebuffer,
        WIDTH * sizeof(uint32_t)
    );
}

void drawFramebuffer(
    SDL_Renderer* renderer,
    SDL_Texture* texture
)
{
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

void destroyRenderer(
    SDL_Renderer* renderer,
    SDL_Texture* texture
)
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
}