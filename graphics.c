#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include "graphics.h"
#include "vehicle_state.h"

// Load UI textures
SDL_Texture *ic_texture;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Joystick *joystick = NULL;

SDL_Texture *load_texture(SDL_Renderer *renderer, const char *file) {
    SDL_Surface *image = IMG_Load(file);
    if (!image) {
        printf("Failed to load image %s: %s\n", file, IMG_GetError());
        return NULL;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return texture;
}

void init_sdl_graphics() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {  // ✅ Enable Joystick Support
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! IMG_Error: %s\n", IMG_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("Honda ICSim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    // ✅ Initialize Joystick
    if (SDL_NumJoysticks() > 0) {
        joystick = SDL_JoystickOpen(0);
        if (joystick) {
            printf("Joystick detected: %s\n", SDL_JoystickName(joystick));
        } else {
            printf("Warning: Joystick found but could not be opened!\n");
        }
    } else {
        printf("No joystick detected. Running in keyboard mode.\n");
    }

    ic_texture = load_texture(renderer, "assets/ic.svg");
    if (!ic_texture) {
        printf("Error: Failed to load UI texture (assets/ic.svg). Make sure the file exists!\n");
        exit(1);
    }
}

void draw_texture(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h) {
    if (!texture) {
        printf("Error: Attempted to draw NULL texture.\n");
        return;
    }
    SDL_Rect dest = { x, y, w, h };
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void draw_rotated_texture(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, double angle) {
    SDL_Rect dest = { x, y, 200, 200 };
    SDL_RenderCopyEx(renderer, texture, NULL, &dest, angle, NULL, SDL_FLIP_NONE);
}

void draw_dashboard(SDL_Renderer *renderer, VehicleState *car) {
    draw_texture(renderer, ic_texture, 50, 50, 600, 400);  // Render ICSim-style UI
    draw_rotated_texture(renderer, ic_texture, 250, 180, car->speed * 1.5); // Speedometer Needle
    draw_rotated_texture(renderer, ic_texture, 400, 300, car->steering * 2); // Steering Wheel
    if (car->doors) draw_texture(renderer, ic_texture, 500, 350, 50, 50); // Door Status
}

void update_dashboard(SDL_Renderer *renderer, VehicleState *car) {
    SDL_RenderClear(renderer);
    draw_dashboard(renderer, car);
    SDL_RenderPresent(renderer);
}

void close_sdl_graphics() {
    if (joystick) {
        SDL_JoystickClose(joystick);
    }
    SDL_DestroyTexture(ic_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
