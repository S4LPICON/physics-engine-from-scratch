#include "events/events.h"

#include <SDL3/SDL.h>

bool processEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
            return false;
    }

    return true;
}