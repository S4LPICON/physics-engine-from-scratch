#include "graphics/window.h"
#include "graphics/framebuffer.h"

SDL_Window* createWindow()
{
    return SDL_CreateWindow(
        "Physics",
        WIDTH * SCALE,
        HEIGHT * SCALE,
        0
    );
}

void destroyWindow(SDL_Window* window)
{
    SDL_DestroyWindow(window);
}