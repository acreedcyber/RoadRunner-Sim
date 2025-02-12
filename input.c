#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <stdio.h>

// Input event definitions
#define INPUT_ACCELERATE 1
#define INPUT_BRAKE 2
#define INPUT_LEFT 3
#define INPUT_RIGHT 4
#define INPUT_TOGGLE_LIGHTS 5
#define INPUT_LOCK_DOORS 6
#define INPUT_UNLOCK_DOORS 7

// Initialize input system
int init_input() {
    if (SDL_Init(SDL_INIT_EVENTS) < 0) {
        printf("SDL input initialization failed: %s\n", SDL_GetError());
        return -1;
    }
    return 0;
}

// Get user input
int get_input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return -1;
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    return INPUT_ACCELERATE;
                case SDLK_DOWN:
                    return INPUT_BRAKE;
                case SDLK_LEFT:
                    return INPUT_LEFT;
                case SDLK_RIGHT:
                    return INPUT_RIGHT;
                case SDLK_l:
                    return INPUT_TOGGLE_LIGHTS;
                case SDLK_d:
                    return INPUT_LOCK_DOORS;
                case SDLK_u:
                    return INPUT_UNLOCK_DOORS;
            }
        }
    }
    return 0;
}

#endif // INPUT_H
