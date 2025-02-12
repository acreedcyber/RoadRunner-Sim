#include "canlib.h"
#include <stdio.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int can_socket;

int can_init(const char *interface) {
    struct ifreq ifr;
    struct sockaddr_can addr;

    can_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (can_socket < 0) {
        perror("Error creating CAN socket");
        return -1;
    }

    strncpy(ifr.ifr_name, interface, IFNAMSIZ);
    if (ioctl(can_socket, SIOCGIFINDEX, &ifr) < 0) {
        perror("Error getting interface index");
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

void send_can_message(int can_id, int value) {
    struct can_frame frame;
    frame.can_id = can_id;
    frame.can_dlc = sizeof(value);
    memcpy(frame.data, &value, sizeof(value));
    
    if (write(can_socket, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
        perror("Error sending CAN message");
    }
}

int can_receive(struct can_frame *frame) {
    int nbytes = read(can_socket, frame, sizeof(struct can_frame));
    if (nbytes < 0) {
        perror("Error reading CAN message");
    }
    return nbytes;
}

void close_can() {
    close(can_socket);
}
