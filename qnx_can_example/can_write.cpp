#include <iostream>

/* For "devctl()" */
#include <devctl.h>
// #include <sys/dcmd_chr.h>
#include <sys/can_dcmd.h>
#include "canfd_dcmd.h"

/* For "open()" */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* For "strerror()" */
#include <string.h>

/* For Errors */
#include <stdlib.h>
#include <stdio.h>

#define MAX_READ_LEN 100
// CAN_MSG buf[MAX_READ_LEN]

int main(int argc, char** argv) {
    if (argc != 2 ) {
        std::cout << "pleade use: ./can_read <dev_canfd_name>" << std::endl;
		exit(-1);
    }

	std::cout << "starting" << std::endl;
    std::string dev_name = argv[1];

    std::cout << "dev name: " << dev_name << std::endl;

	int fd = open(dev_name.c_str(), O_RDWR);
	if (fd < 0) {
        std::cout << dev_name << " may be not existed!" << std::endl;
		exit(-1);
	}

    int count = 0;
	
	while(1) {
		char c = getchar();
		if(c == 'q') {
			break;
		}

        CAN_MSG buf;
        memset(static_cast<void*>(&buf), 0, sizeof(CAN_MSG));

        buf.mid = 0x123;
        buf.len = 8;
        buf.dat[0] = 0x12;
        buf.dat[1] = 0x34;
        buf.dat[2] = 0x56;

        int dev_ret = devctl(fd, CAN_DEVCTL_WRITE_CANMSG_EXT, static_cast<void*>(&buf), sizeof(CAN_MSG), NULL);
        if (dev_ret != 0) {
            printf("devctl error: %s\n", strerror(errno));
            continue;
        }
        count++;

        std::cout << "sending: " << count << std::endl;

	}

	close(fd);
    return 0;
}
