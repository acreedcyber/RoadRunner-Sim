#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>
#include "canlib.h"
#include "graphics.h"
#include "input.h"
#include "real_can_data.h"
#include "vehicle_state.h"

// Vehicle state
VehicleState *car;

int main() {
    init_sdl_graphics();
    
    car = malloc(sizeof(VehicleState));
    if (!car) {
        printf("Memory allocation failed for VehicleState\n");
        return 1;
    }
    
    pthread_t ui_thread;
    pthread_create(&ui_thread, NULL, (void *)update_dashboard, (void *)renderer);

    while (1) {
        int input = get_input();
        switch (input) {
            case INPUT_ACCELERATE:
                car->speed = (car->speed < 120) ? car->speed + 5 : 120;
                send_can_message(HONDA_SPEED_ID, car->speed);
                break;
            case INPUT_BRAKE:
                car->speed = (car->speed > 0) ? car->speed - 5 : 0;
                send_can_message(HONDA_BRAKE_ID, 1);
                break;
            case INPUT_LEFT:
                car->steering = (car->steering > -30) ? car->steering - 5 : -30;
                send_can_message(HONDA_STEERING_ID, car->steering);
                break;
            case INPUT_RIGHT:
                car->steering = (car->steering < 30) ? car->steering + 5 : 30;
                send_can_message(HONDA_STEERING_ID, car->steering);
                break;
        }
        update_dashboard(renderer, car);
    }

    close_sdl_graphics();
    free(car);
    return 0;
}
