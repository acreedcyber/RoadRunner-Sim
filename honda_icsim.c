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

// Honda-specific CAN IDs
#define HONDA_SPEED_ID 0x158
#define HONDA_RPM_ID 0x17C
#define HONDA_STEERING_ID 0x123
#define HONDA_BRAKE_ID 0x1FA
#define HONDA_LIGHTS_ID 0x3D0
#define HONDA_DOOR_ID 0x3E9
#define HONDA_INFOTAINMENT_ID 0x42A
#define HONDA_AIRBAG_ID 0x500
#define HONDA_TIRE_PRESSURE_ID 0x5A0
#define HONDA_ENGINE_TEMP_ID 0x610
#define HONDA_FUEL_LEVEL_ID 0x620

// Vehicle State
VehicleState *car;

// Function to send CAN messages
void send_can_message(int can_id, int value) {
    struct can_frame frame;
    frame.can_id = can_id;
    frame.can_dlc = sizeof(value);
    memcpy(frame.data, &value, sizeof(value));
    can_send(&frame);
}

// Function to update dashboard
void update_dashboard() {
    sdl_clear_screen();
    draw_speedometer_sdl(car->speed);
    draw_rpm_gauge_sdl(car->rpm);
    draw_steering_wheel_sdl(car->steering);
    draw_brake_indicator_sdl(car->brakes);
    draw_light_status_sdl(car->lights);
    draw_door_status_sdl(car->doors);
    draw_infotainment_status_sdl(car->infotainment);
    draw_airbag_status_sdl(car->airbags);
    draw_tire_pressure_sdl(car->tire_pressure);
    draw_engine_temp_sdl(car->engine_temp);
    draw_fuel_level_sdl(car->fuel_level);
    sdl_refresh_screen();
}

// Background thread for continuous CAN simulation
void *simulate_ecu_behavior(void *arg) {
    while (1) {
        car->rpm = 800 + (rand() % 50);
        car->engine_temp = 90 + (rand() % 5);
        car->fuel_level -= 0.01;
        if (car->fuel_level < 5) car->fuel_level = 50;

        send_can_message(HONDA_RPM_ID, car->rpm);
        send_can_message(HONDA_ENGINE_TEMP_ID, car->engine_temp);
        send_can_message(HONDA_FUEL_LEVEL_ID, car->fuel_level);
        send_can_message(HONDA_TIRE_PRESSURE_ID, 32 + (rand() % 3));
        sleep(1);
    }
    return NULL;
}

// Thread function to handle CAN input
void *can_listener(void *arg) {
    struct can_frame frame;
    while (1) {
        if (can_receive(&frame) > 0) {
            parse_real_honda_can_data(&frame, car);
            update_dashboard();
        }
        send_can_message(HONDA_STEERING_ID, car->steering);
        send_can_message(HONDA_BRAKE_ID, car->brakes);
        sleep(1);
    }
    return NULL;
}

// Main function
int main() {
    car = malloc(sizeof(VehicleState));
    if (!car) {
        printf("Memory allocation failed for VehicleState\n");
        return 1;
    }
    car->speed = 0;
    car->rpm = 800;
    car->steering = 0;
    car->brakes = 0;
    car->lights = 0;
    car->doors = 0;
    car->infotainment = 0;
    car->airbags = 0;
    car->tire_pressure = 32;
    car->engine_temp = 90;
    car->fuel_level = 50;

    if (can_init("vcan0") < 0) {
        printf("Error initializing CAN bus.\n");
        return 1;
    }
    
    init_sdl_graphics();
    
    pthread_t can_thread, ecu_thread;
    pthread_create(&can_thread, NULL, can_listener, NULL);
    pthread_create(&ecu_thread, NULL, simulate_ecu_behavior, NULL);
    
    while (1) {
        int input = get_input();
        switch (input) {
            case INPUT_ACCELERATE:
                car->speed = (car->speed < 120) ? car->speed + 5 : 120;
                car->rpm = 800 + (car->speed * 50);
                send_can_message(HONDA_SPEED_ID, car->speed);
                send_can_message(HONDA_RPM_ID, car->rpm);
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
            case INPUT_TOGGLE_LIGHTS:
                car->lights = !car->lights;
                send_can_message(HONDA_LIGHTS_ID, car->lights);
                break;
            case INPUT_LOCK_DOORS:
                car->doors = 1;
                send_can_message(HONDA_DOOR_ID, car->doors);
                break;
            case INPUT_UNLOCK_DOORS:
                car->doors = 0;
                send_can_message(HONDA_DOOR_ID, car->doors);
                break;
        }
        update_dashboard();
    }
    free(car);
    return 0;
}
