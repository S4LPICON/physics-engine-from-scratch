#include <SDL3/SDL.h>

#include "graphics/framebuffer.h"
#include "graphics/window.h"
#include "graphics/renderer.h"
#include "events/events.h"
int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = createWindow();
    SDL_Renderer* renderer = createRenderer(window);
    SDL_Texture* texture = createTexture(renderer);

    while (processEvents())
    {
        clearFramebuffer(0x000000FF);

        putPixel(
            WIDTH / 2,
            HEIGHT / 2,
            0xFF0000FF
        );

        updateTexture(texture, framebuffer);
        drawFramebuffer(renderer, texture);
    }

    destroyRenderer(renderer, texture);
    destroyWindow(window);

    SDL_Quit();
}