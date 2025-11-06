#include "input.h"
#include <SDL.h>

InputFrame Input::poll() {
    InputFrame f{};
    SDL_Event e{};
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) { f.action = Action::PauseToggle; } // app can interpret as quit
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE: f.action = Action::PauseToggle; break;
                case SDLK_r:      f.action = Action::Reset;       break;
                case SDLK_UP:     f.action = Action::Up;          break;
                case SDLK_DOWN:   f.action = Action::Down;        break;
                case SDLK_LEFT:   f.action = Action::Left;        break;
                case SDLK_RIGHT:  f.action = Action::Right;       break;
            }
        }
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            f.clicked = true;
    }
    Uint32 mask = SDL_GetMouseState(&f.mouseX, &f.mouseY);
    f.mouseDown = (mask & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
    return f;
}
