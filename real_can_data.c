#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "real_can_data.h"
#include "vehicle_state.h"

void parse_real_honda_can_data(struct can_frame *frame, VehicleState *car) {
    if (!frame || !car) return;
    
    switch (frame->can_id) {
        case HONDA_SPEED_ID:
            car->speed = frame->data[0];
            break;
        case HONDA_RPM_ID:
            car->rpm = (frame->data[0] << 8) | frame->data[1];
            break;
        case HONDA_STEERING_ID:
            car->steering = (int8_t)frame->data[0];
            break;
        case HONDA_BRAKE_ID:
            car->brakes = frame->data[0];
            break;
        case HONDA_LIGHTS_ID:
            car->lights = frame->data[0];
            break;
        case HONDA_DOOR_ID:
            car->doors = frame->data[0];
            break;
        case HONDA_FUEL_LEVEL_ID:
            car->fuel_level = frame->data[0];
            break;
        case HONDA_ENGINE_TEMP_ID:
            car->engine_temp = frame->data[0];
            break;
        case HONDA_TIRE_PRESSURE_ID:
            car->tire_pressure = frame->data[0];
            break;
        case HONDA_AIRBAG_ID:
            car->airbags = frame->data[0];
            break;
        default:
            printf("Unknown CAN ID: 0x%X\n", frame->can_id);
            break;
    }
}

