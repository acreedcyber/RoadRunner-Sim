#include "graphics.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

// SDL variables
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

// Initialize SDL graphics
int init_sdl_graphics() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Initialization failed: %s\n", SDL_GetError());
        return -1;
    }
    window = SDL_CreateWindow("Honda ICSim Dashboard", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return -1;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        return -1;
    }
    return 0;
}

// Clear screen
void sdl_clear_screen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

// Refresh screen
void sdl_refresh_screen() {
    SDL_RenderPresent(renderer);
}

// Draw speedometer
void draw_speedometer_sdl(int speed) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect speed_rect = {50, 50, speed * 2, 20};
    SDL_RenderFillRect(renderer, &speed_rect);
}

// Draw RPM gauge
void draw_rpm_gauge_sdl(int rpm) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rpm_rect = {50, 100, rpm / 100, 20};
    SDL_RenderFillRect(renderer, &rpm_rect);
}

// Draw steering wheel status
void draw_steering_wheel_sdl(int angle) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect steer_rect = {50, 150, angle * 2, 20};
    SDL_RenderFillRect(renderer, &steer_rect);
}

// Draw brake indicator
void draw_brake_indicator_sdl(int status) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    if (status) {
        SDL_Rect brake_rect = {50, 200, 50, 20};
        SDL_RenderFillRect(renderer, &brake_rect);
    }
}

// Draw lights indicator
void draw_light_status_sdl(int status) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    if (status) {
        SDL_Rect light_rect = {50, 250, 50, 20};
        SDL_RenderFillRect(renderer, &light_rect);
    }
}

// Draw door status
void draw_door_status_sdl(int status) {
    SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
    if (status) {
        SDL_Rect door_rect = {50, 300, 50, 20};
        SDL_RenderFillRect(renderer, &door_rect);
    }
}

// Draw infotainment status
void draw_infotainment_status_sdl(int status) {
    SDL_SetRenderDrawColor(renderer, 75, 0, 130, 255);
    if (status) {
        SDL_Rect info_rect = {50, 350, 50, 20};
        SDL_RenderFillRect(renderer, &info_rect);
    }
}

// Draw airbag status
void draw_airbag_status_sdl(int status) {
    SDL_SetRenderDrawColor(renderer, 255, 69, 0, 255);
    if (status) {
        SDL_Rect airbag_rect = {50, 400, 50, 20};
        SDL_RenderFillRect(renderer, &airbag_rect);
    }
}

// Draw tire pressure status
void draw_tire_pressure_sdl(int pressure) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_Rect tire_rect = {50, 450, pressure, 20};
    SDL_RenderFillRect(renderer, &tire_rect);
}

// Draw engine temperature
void draw_engine_temp_sdl(int temp) {
    SDL_SetRenderDrawColor(renderer, 139, 0, 0, 255);
    SDL_Rect temp_rect = {50, 500, temp, 20};
    SDL_RenderFillRect(renderer, &temp_rect);
}

// Draw fuel level
void draw_fuel_level_sdl(int fuel) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect fuel_rect = {50, 550, fuel * 2, 20};
    SDL_RenderFillRect(renderer, &fuel_rect);
}
