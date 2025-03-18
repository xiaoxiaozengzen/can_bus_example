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
        std::cout << "pleade use: ./canfd_read <dev_canfd_name>" << std::endl;
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

    canfd_package package;
	
	while(1) {
        static int loop_num = 0;
        loop_num++;
        printf("++++++++++++++++++++++++++++loop_num : %d\n", loop_num);

        // memset(static_cast<void*>(&buf), 0, sizeof(CANFD_MSG));
        int read_len = read(fd, &package.canfd_rx_data, sizeof(CANFD_MSG) * FRAME_COUNT);
        if(read_len < 0) {
            printf("read error: %s\n", strerror(errno));
            continue;
        }

        printf("------------------------------------------read_len: %d\n", read_len);
        printf("------------------------------------------read_len/ sizeof: %d\n", read_len / sizeof(CANFD_MSG));
        for(int i = 0; i < read_len / sizeof(CANFD_MSG); i++) {
            printf("------------------------------------------\n");
            printf("mid: %x\n", package.canfd_rx_data[i].mid);
            printf("len: %d\n", package.canfd_rx_data[i].len);
            for(int j = 0; j < 64; j++) {
                printf("%02x", package.canfd_rx_data[i].dat[j]);
            }
            printf("\n");
        }

	}

	close(fd);
    return 0;
}


// 这种方式的读取，会一直打印0，不能正常的使用
// CANFD_MSG buf;
// int dev_ret = devctl(fd, CANFD_DEVCTL_GET_RXDATA, static_cast<void*>(&buf), sizeof(CANFD_MSG), NULL);
// if (dev_ret != 0) {
//     printf("devctl error: %s\n", strerror(errno));
//     continue;
// }

// count++;
// printf("------------------------------------------\n");
// printf("count: %d\n", count);
// printf("mid: %x\n", buf.mid);
// printf("len: %d\n", buf.len);
// for(int i = 0; i < 64; i++) {
//     printf("%02x", buf.dat[i]);
// }
// printf("\n");