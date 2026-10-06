#include "input/input.h"

bool Input::isKeyDown(Key key) const {
    const bool* keyboardState = SDL_GetKeyboardState(nullptr);

    return keyboardState[toSDLScancode(key)];
}

SDL_Scancode Input::toSDLScancode(Key key) const {
    switch (key) {
        case Key::W:      return SDL_SCANCODE_W;
        case Key::A:      return SDL_SCANCODE_A;
        case Key::S:      return SDL_SCANCODE_S;
        case Key::D:      return SDL_SCANCODE_D;
        case Key::Space:  return SDL_SCANCODE_SPACE;
        case Key::Escape: return SDL_SCANCODE_ESCAPE;
        case Key::Q:       return SDL_SCANCODE_Q;
    }

    return SDL_SCANCODE_UNKNOWN;
}