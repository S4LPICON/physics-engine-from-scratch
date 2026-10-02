#pragma once

#include <SDL3/SDL.h>

enum class Key {
    W,
    A,
    S,
    D,
    Space,
    Escape
};

class Input {
public:
    bool isKeyDown(Key key) const;

private:
    SDL_Scancode toSDLScancode(Key key) const;
};