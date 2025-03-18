#include <linux/can.h>
#include <fcntl.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>

#include <string>
#include <vector>
#include <cmath>
#include <cstring>
#include <iostream>

#include "frequency.h"
#include "GeelyYHFrontCornerRadar_dbc.h"

namespace devastator {
namespace common {
    enum class CAN_TYPE{
    CAN = 1,
    CANFD = 2
    };

}
}



int main() {

    devastator::common::Frequency raw_frequency;
    devastator::common::Frequency filter_frequency;
    double last_time;
    struct GeelyYHFrontCornerRadar_dbc_fsrl_safety_canfd1_frame00_t raw_frame;

    struct sockaddr_can addr;
    struct ifreq ifr;
    int can_socket_;

    std::string channel_name = "can0";
    std::vector<uint32_t> filter{0x129};
    devastator::common::CAN_TYPE can_type = devastator::common::CAN_TYPE::CANFD;
    bool block = true;

    if ((can_socket_ = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        std::cout << "Socketcan create error!" << std::endl;
        return false;
    } else {
        std::cout << "Socketcan create success!" << std::endl;
    }

    snprintf(ifr.ifr_name, channel_name.size() + 1, "%s", channel_name.c_str());

    if (ioctl(can_socket_, SIOCGIFFLAGS, &ifr) < 0) {
        std::cout << "Maybe interface %s is invalid!" <<
                    channel_name.c_str() << std::endl;
        close(can_socket_);
        return false;
    }

    if (!(ifr.ifr_flags & IFF_RUNNING)) {
        std::cout << "Maybe interface  %s is not running, please setting!" <<
                    channel_name.c_str() << std::endl;
        close(can_socket_);
        return false;
    }

    if (!filter.empty()) {
        struct can_filter *prfilter =
            (struct can_filter *)malloc(sizeof(struct can_filter) * filter.size());
        for (size_t i = 0; i < filter.size(); i++) {
        (prfilter + i)->can_id = filter[i];

        // 对相同id的拓展帧和标准帧进行区分
        if ((prfilter + i)->can_id & CAN_EFF_FLAG) {
            (prfilter + i)->can_mask = (CAN_EFF_FLAG | CAN_RTR_FLAG | CAN_EFF_MASK);
        } else {
            (prfilter + i)->can_mask = (CAN_EFF_FLAG | CAN_RTR_FLAG | CAN_SFF_MASK);
        }
        }
        setsockopt(can_socket_, SOL_CAN_RAW, CAN_RAW_FILTER, prfilter,
                filter.size() * sizeof(struct can_filter));
        free(prfilter);
    }

    /** set canfd mode */
    if (can_type == devastator::common::CAN_TYPE::CANFD) {
        int enable = 1;
        setsockopt(can_socket_, SOL_CAN_RAW, CAN_RAW_FD_FRAMES, &enable,
                sizeof(enable));
    }

    /** set no block */
    if (!block) {
        int flags = fcntl(can_socket_, F_GETFL, 0);
        fcntl(can_socket_, F_SETFL, flags | O_NONBLOCK);
    }

    ioctl(can_socket_, SIOCGIFINDEX, &ifr);

    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(can_socket_, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        std::cout <<  "Socketcan bind error." << std::endl;
        return false;
    } else {
        std::cout <<  "Socketcan bind success!" << std::endl;
    }

    struct canfd_frame frame;

    while(true) {
        int nbytes = read(can_socket_, &frame, sizeof(struct canfd_frame));
        if (nbytes > 0) {
            if (frame.can_id & CAN_EFF_FLAG) {
                frame.can_id = frame.can_id & CAN_EFF_MASK;
            } else {
                frame.can_id = frame.can_id & CAN_SFF_MASK;
            }
        } else {
            printf("read error\n");
            continue;
        }

        if (frame.can_id == 0x129) {
            GeelyYHFrontCornerRadar_dbc_fsrl_safety_canfd1_frame00_unpack(
                &raw_frame,
                frame.data,
                64
            );

            std::cout << "raw fps: " << raw_frequency.update() << std::endl;

            if (fabs(raw_frame.frnt_side_rdr_le_sts_rdr_sts_ti_stamp - last_time) < 0.00001) {
                std::cout << "filter fps: " << filter_frequency.update() << std::endl;
            }

            last_time = raw_frame.frnt_side_rdr_le_sts_rdr_sts_ti_stamp;
        }
    }

}