#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include "vehicle_state.h"

extern SDL_Renderer *renderer;

void init_sdl_graphics();
void update_dashboard(SDL_Renderer *renderer, VehicleState *car);
void close_sdl_graphics();

#endif
