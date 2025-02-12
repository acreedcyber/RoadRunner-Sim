#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Initialize SDL graphics
int init_sdl_graphics();

// Clear the screen
void sdl_clear_screen();

// Refresh the screen
void sdl_refresh_screen();

// Draw speedometer
void draw_speedometer_sdl(int speed);

// Draw RPM gauge
void draw_rpm_gauge_sdl(int rpm);

// Draw steering wheel status
void draw_steering_wheel_sdl(int angle);

// Draw brake indicator
void draw_brake_indicator_sdl(int status);

// Draw lights indicator
void draw_light_status_sdl(int status);

// Draw door status
void draw_door_status_sdl(int status);

// Draw infotainment status
void draw_infotainment_status_sdl(int status);

// Draw airbag status
void draw_airbag_status_sdl(int status);

// Draw tire pressure status
void draw_tire_pressure_sdl(int pressure);

// Draw engine temperature
void draw_engine_temp_sdl(int temp);

// Draw fuel level
void draw_fuel_level_sdl(int fuel);

#endif // GRAPHICS_H
