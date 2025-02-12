#include <SDL2/SDL.h>
#include "input.h"

int get_input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            exit(0);
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP: return INPUT_ACCELERATE;
                case SDLK_DOWN: return INPUT_BRAKE;
                case SDLK_LEFT: return INPUT_LEFT;
                case SDLK_RIGHT: return INPUT_RIGHT;
                case SDLK_l: return INPUT_TOGGLE_LIGHTS;
                case SDLK_d: return INPUT_LOCK_DOORS;
                case SDLK_u: return INPUT_UNLOCK_DOORS;
                case SDLK_ESCAPE: exit(0);
            }
        }
        if (event.type == SDL_JOYAXISMOTION || event.type == SDL_JOYBUTTONDOWN) {
            // Handle joystick input if available
        }
    }
    return 0;
}
