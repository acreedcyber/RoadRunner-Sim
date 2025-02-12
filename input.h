#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

// Input event definitions
#define INPUT_ACCELERATE 1
#define INPUT_BRAKE 2
#define INPUT_LEFT 3
#define INPUT_RIGHT 4
#define INPUT_TOGGLE_LIGHTS 5
#define INPUT_LOCK_DOORS 6
#define INPUT_UNLOCK_DOORS 7

// Initialize input system
int init_input();

// Get user input
int get_input();

#endif // INPUT_H
