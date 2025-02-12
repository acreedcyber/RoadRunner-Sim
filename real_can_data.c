#include "real_can_data.h"
#include <stdio.h>
#include <string.h>

void parse_real_honda_can_data(struct can_frame *frame, VehicleState *car) {
    switch (frame->can_id) {
        case 0x158: // Speed
            car->speed = frame->data[0];
            printf("Speed updated: %d mph\\n", car->speed);
            break;
        case 0x17C: // RPM
            car->rpm = frame->data[0] * 100;
            printf("RPM updated: %d\\n", car->rpm);
            break;
        case 0x123: // Steering
            car->steering = frame->data[0] - 30;
            printf("Steering angle: %d\\n", car->steering);
            break;
        case 0x1FA: // Brakes
            car->brakes = frame->data[0];
            printf("Brakes: %s\\n", car->brakes ? "Engaged" : "Released");
            break;
        case 0x3D0: // Lights
            car->lights = frame->data[0];
            printf("Lights: %s\\n", car->lights ? "On" : "Off");
            break;
        case 0x3E9: // Doors
            car->doors = frame->data[0];
            printf("Doors: %s\\n", car->doors ? "Locked" : "Unlocked");
            break;
        default:
            printf("Unknown CAN ID: 0x%X\\n", frame->can_id);
            break;
    }
}

