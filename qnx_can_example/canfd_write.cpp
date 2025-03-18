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

int main(int argc, char** argv) {
    if (argc != 2 ) {
        std::cout << "pleade use: ./example <dev_canfd_name>" << std::endl;
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
	CANFD_MSG canfd_msg_tx;
       
	canfd_msg_tx.ext.is_extended_mid = 0;     
	canfd_msg_tx.ext.is_remote_frame = 0;
	canfd_msg_tx.len = 64;
	canfd_msg_tx.mid = 0x111;
	canfd_msg_tx.dat[0] = 0x01;
	canfd_msg_tx.dat[1] = 0x02;
	canfd_msg_tx.dat[2] = 0x03;

    int count = 0;
	
	while(1) {
		char c = getchar();
		if(c == 'q') {
			break;
		}
	
		
		int ret = devctl(fd, CANFD_DEVCTL_SEND_TXDATA, (void*)(&canfd_msg_tx), sizeof(canfd_msg_tx), NULL);
        if (ret != 0) {
            std::cout << "sending failed: " << ret << std::endl;
            continue;
        }

        count++;
        std::cout << "sending: " << count << std::endl;
	}

	close(fd);
}
