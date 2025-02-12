#ifndef CANLIB_H
#define CANLIB_H

#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/socket.h>
#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// CAN socket descriptor
extern int can_socket;

// Initialize CAN bus
int can_init(const char *interface);

// Send CAN message
int can_send(struct can_frame *frame);

// Receive CAN message
int can_receive(struct can_frame *frame);

#endif // CANLIB_H
