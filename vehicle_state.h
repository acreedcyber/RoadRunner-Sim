#ifndef VEHICLE_STATE_H
#define VEHICLE_STATE_H

typedef struct {
    int speed;
    int rpm;
    int steering;
    int brakes;
    int lights;
    int doors;
    int infotainment;
    int airbags;
    int tire_pressure;
    int engine_temp;
    int fuel_level;
} VehicleState;

// Define Honda CAN IDs
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

#endif
