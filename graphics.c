#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include "graphics.h"
#include "vehicle_state.h"

// Load UI texture from ICSim's ic.svg
SDL_Texture *ic_texture;

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

void init_ui(SDL_Renderer *renderer) {
    ic_texture = load_texture(renderer, "assets/ic.svg");  // Use ICSim UI
}

void draw_texture(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h) {
    SDL_Rect dest = { x, y, w, h };
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void draw_rotated_texture(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, double angle) {
    SDL_Rect dest = { x, y, 200, 200 };
    SDL_RenderCopyEx(renderer, texture, NULL, &dest, angle, NULL, SDL_FLIP_NONE);
}

void draw_dashboard(SDL_Renderer *renderer, VehicleState *car) {
    // Render ICSim-style dashboard
    draw_texture(renderer, ic_texture, 50, 50, 600, 400);  // Full ICSim UI
    
    // Animate speedometer needle
    draw_rotated_texture(renderer, ic_texture, 250, 180, car->speed * 1.5);

    // Animate steering wheel movement from ic.svg
    draw_rotated_texture(renderer, ic_texture, 400, 300, car->steering * 2);

    // Show doors status from ic.svg
    if (car->doors)
        draw_texture(renderer, ic_texture, 500, 350, 50, 50);
}

void update_dashboard(SDL_Renderer *renderer, VehicleState *car) {
    SDL_RenderClear(renderer);
    draw_dashboard(renderer, car);
    SDL_RenderPresent(renderer);
}
