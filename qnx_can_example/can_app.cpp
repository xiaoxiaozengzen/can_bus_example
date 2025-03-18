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
    if (argc != 3 ) {
        std::cout << "pleade use: ./can_app <dev_canfd_name> <cmd>" << std::endl;
		exit(-1);
    }

    std::string dev_name = argv[1];
    std::string cmd = argv[2];
    std::cout << "dev name: " << dev_name << ", cmd: " << cmd << std::endl;

	int fd = open(dev_name.c_str(), O_RDWR);
	if (fd < 0) {
        std::cout << dev_name << " may be not existed!" << std::endl;
		exit(-1);
	}

	
	if (cmd == "debug") {
		int ret = devctl(fd, CAN_DEVCTL_DEBUG_INFO, NULL, 0, NULL);
		if (ret != 0) {
			std::cout << "devctl CAN_DEVCTL_DEBUG_INFO failed!" << strerror(errno) << std::endl;
            close(fd);
			exit(-1);
		}
    } else if (cmd == "debug2") {
		int ret = devctl(fd, CAN_DEVCTL_DEBUG_INFO2, NULL, 0, NULL);
		if (ret != 0) {
			std::cout << "devctl CAN_DEVCTL_DEBUG_INFO2 failed!" << strerror(errno) << std::endl;
            close(fd);
			exit(-1);
		}
    } else if (cmd == "error") {
        struct can_devctl_error derror;
		int ret = devctl(fd, CAN_DEVCTL_ERROR, &derror, sizeof(can_devctl_error), NULL);
		if (ret != 0) {
			std::cout << "devctl CAN_DEVCTL_ERROR failed!" << strerror(errno) << std::endl;
            close(fd);
			exit(-1);
		} else {
            printf("ERROR drvr1 = 0x%X\n", derror.drvr1);
            printf("ERROR drvr2 = 0x%X\n", derror.drvr2);
            printf("ERROR drvr3 = 0x%X\n", derror.drvr3);
            printf("ERROR drvr4 = 0x%X\n", derror.drvr4);
        }
    } else if (cmd == "get_info") {
        struct can_devctl_info devinfo;
		int ret = devctl(fd, CAN_DEVCTL_GET_INFO, &devinfo, sizeof(can_devctl_info), NULL);
		if (ret != 0) {
			std::cout << "devctl CAN_DEVCTL_GET_INFO failed!" << strerror(errno) << std::endl;
            close(fd);
			exit(-1);
		} else {
            printf("description: %s\n", devinfo.description);
            printf("msgq_size: %d\n", devinfo.msgq_size);
            printf("waitq_size: %d\n", devinfo.waitq_size);
            printf("mode: %s\n", (devinfo.mode == CANDEV_MODE::CANDEV_MODE_IO)?"IO":"RAW");
            printf("bit_rate: %d\n", devinfo.bit_rate);
            printf("bit_rate_prescaler: %d\n", devinfo.bit_rate_prescaler);
            printf("sync_jump_width: %d\n", devinfo.sync_jump_width);
            printf("time_segment_1: %d\n", devinfo.time_segment_1);
            printf("time_segment_2: %d\n", devinfo.time_segment_2);
            printf("num_tx_mboxes: %d\n", devinfo.num_tx_mboxes);
            printf("num_rx_mboxes: %d\n", devinfo.num_rx_mboxes);
            printf("loopback_external: %d\n", devinfo.loopback_external);
            printf("loopback_internal: %d\n", devinfo.loopback_internal);
            printf("autobus_on: %d\n", devinfo.autobus_on);
            printf("silent: %d\n", devinfo.silent);

        }
    } else if (cmd == "get_filter") {
        uint32_t filter_num = 0;
		int ret = devctl(fd, CAN_DEVCTL_GET_MFILTER, &filter_num, sizeof(uint32_t), NULL);
		if (ret != 0) {
			std::cout << "devctl CAN_DEVCTL_GET_MFILTER failed!" << strerror(errno) << std::endl;
            close(fd);
			exit(-1);
		} else {
            printf("GET_MFILTER = 0x%X\n", filter_num);
        }
    } else if (cmd == "get_mid") {
        uint32_t message_id = 0;
		int ret = devctl(fd, CAN_DEVCTL_GET_MID, &message_id, sizeof(uint32_t), NULL);
		if (ret != 0) {
			std::cout << "devctl CAN_DEVCTL_GET_MID failed!" << strerror(errno) << std::endl;
            close(fd);
			exit(-1);
		} else {
            printf("GET_MID = 0x%X\n", message_id);
        }
    } else if (cmd == "get_pri") {
        uint32_t prio_value = 0;
		int ret = devctl(fd, CAN_DEVCTL_GET_PRIO, &prio_value, sizeof(uint32_t), NULL);
		if (ret != 0) {
			std::cout << "devctl CAN_DEVCTL_GET_PRIO failed!" << strerror(errno) << std::endl;
            close(fd);
			exit(-1);
		} else {
            printf("GET_PRO = 0x%X\n", prio_value);
        }
    } else if (cmd == "get_status") {
        struct can_devctl_stats status_value;
		int ret = devctl(fd, CAN_DEVCTL_GET_STATS, &status_value, sizeof(can_devctl_stats), NULL);
		if (ret != 0) {
			std::cout << "devctl CAN_DEVCTL_GET_STATS failed!" << strerror(errno) << std::endl;
            close(fd);
			exit(-1);
		} else {
            printf("transmitted_frames: %d\n",status_value.transmitted_frames);
            printf("received_frames: %d\n",status_value.received_frames);
            printf("missing_ack: %d\n",status_value.missing_ack);
            printf("total_frame_errors: %d\n",status_value.total_frame_errors);
            printf("stuff_errors: %d\n",status_value.stuff_errors);
            printf("form_errors: %d\n",status_value.form_errors);
            printf("dom_bit_recess_errors: %d\n",status_value.dom_bit_recess_errors);
            printf("recess_bit_dom_errors: %d\n",status_value.recess_bit_dom_errors);
            printf("parity_errors: %d\n",status_value.parity_errors);
            printf("crc_errors: %d\n",status_value.crc_errors);
            printf("hw_receive_overflows: %d\n",status_value.hw_receive_overflows);
            printf("sw_receive_q_full: %d\n",status_value.sw_receive_q_full);
            printf("error_warning_state_count: %d\n",status_value.error_warning_state_count);
            printf("error_passive_state_count: %d\n",status_value.error_passive_state_count);
            printf("bus_off_state_count: %d\n",status_value.bus_off_state_count);
            printf("bus_idle_count: %d\n",status_value.bus_idle_count);
            printf("power_down_count: %d\n",status_value.power_down_count);
            printf("wake_up_count: %d\n",status_value.wake_up_count);
            printf("rx_interrupts: %d\n",status_value.rx_interrupts);
            printf("tx_interrupts: %d\n",status_value.tx_interrupts);
            printf("total_interrupts: %d\n",status_value.total_interrupts);
        }
    } else if (cmd == "get_timestamp") {
        uint32_t time_value = 0;
		int ret = devctl(fd, CAN_DEVCTL_GET_TIMESTAMP, &time_value, sizeof(uint32_t), NULL);
		if (ret != 0) {
			std::cout << "devctl CAN_DEVCTL_GET_TIMESTAMP failed!" << strerror(errno) << std::endl;
            close(fd);
			exit(-1);
		} else {
            printf("GET_TIMESTAMP = 0x%X\n", time_value);
        }
    } else if (cmd == "set_filter") {
        uint32_t set_filter = 0x1FF;
		int ret = devctl(fd, CAN_DEVCTL_SET_MFILTER, &set_filter, sizeof(uint32_t), NULL);
		if (ret != 0) {
			std::cout << "devctl CAN_DEVCTL_SET_MFILTER failed!" << strerror(errno) << std::endl;
            close(fd);
			exit(-1);
		} else {
            printf("SET_FILTER = 0x%X\n", set_filter);
        }
    } else if (cmd == "set_timming") {
        struct can_devctl_timing set_timming;
        set_timming.ref_clock_freq = 0;
        set_timming.bit_rate_prescaler = 0x14;
        set_timming.sync_jump_width = 0x2;
        set_timming.time_segment_1 = 0xd;
        set_timming.time_segment_2 = 0x4;
		int ret = devctl(fd, CAN_DEVCTL_SET_MFILTER, &set_timming, sizeof(can_devctl_timing), NULL);
		if (ret != 0) {
			std::cout << "devctl CAN_DEVCTL_SET_MFILTER failed!" << strerror(errno) << std::endl;
            close(fd);
			exit(-1);
		} else {
            
        }
    } else {
        std::cout << "cmd is not supported!" << std::endl;
    }

	close(fd);
    return 0;
}
