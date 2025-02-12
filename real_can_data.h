#ifndef REAL_CAN_DATA_H
#define REAL_CAN_DATA_H

#include <linux/can.h>
#include "honda_icsim.h"

// Function to parse real Honda CAN data
void parse_real_honda_can_data(struct can_frame *frame, VehicleState *car);

#endif // REAL_CAN_DATA_H
