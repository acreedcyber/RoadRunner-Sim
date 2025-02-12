#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>   // ✅ Added for ioctl()
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>       // ✅ Added for struct ifreq
#include "canlib.h"

int can_socket;

// Initialize CAN bus
int can_init(const char *interface) {
    struct ifreq ifr;
    struct sockaddr_can addr;

    can_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (can_socket < 0) {
        perror("Error opening CAN socket");
        return -1;
    }

    strcpy(ifr.ifr_name, interface);
    if (ioctl(can_socket, SIOCGIFINDEX, &ifr) < 0) {
        perror("Error getting CAN interface index");
        return -1;
    }

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(can_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Error binding CAN socket");
        return -1;
    }
    
    return 0;
}

// Send CAN message
int can_send(struct can_frame *frame) {
    if (write(can_socket, frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
        perror("Error sending CAN message");
        return -1;
    }
    return 0;
}

// Receive CAN message
int can_receive(struct can_frame *frame) {
    int bytes_read = read(can_socket, frame, sizeof(struct can_frame));
    if (bytes_read < 0) {
        perror("Error receiving CAN message");
        return -1;
    }
    return bytes_read;
}
