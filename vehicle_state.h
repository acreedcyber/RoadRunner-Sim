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

#endif // VEHICLE_STATE_H
