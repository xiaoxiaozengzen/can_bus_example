#ifndef __CANFD_DCMD_H_INCLUDED
#define __CANFD_DCMD_H_INCLUDED

#include <stdint.h>

#ifndef _DEVCTL_H_INCLUDED
    #include <devctl.h>
#endif

#define CANFD_MSG_DATA_MAX        0x40

typedef struct canfd_msg_ext {
    uint32_t        timestamp;         /* CANFD message timestamp */
    uint32_t        is_extended_mid;   /* 1=29-bit MID, 0=11-bit MID */
    uint32_t        is_remote_frame;   /* 1=remote frame request, 0=data frame */
} CANFD_MSG_EXT;

typedef struct canfd_msg {
    /* Pre-allocate CAN messages to the max data size */
    uint8_t         dat[CANFD_MSG_DATA_MAX];  /* CANFD message data */
    uint8_t         len;                    /* Actual CAN message data length */
    uint32_t        mid;                    /* CANFD message identifier */
    CANFD_MSG_EXT     ext;                    /* Extended CANFD message info */
} CANFD_MSG;


#define FRAME_COUNT 100
struct canfd_package
{
        struct canfd_msg canfd_rx_data[FRAME_COUNT];
        uint32_t cnt;
};

typedef union
{
    CANFD_MSG canfd;
 
} DCMD_FD_DATA;


#define CANFD_CMD_CODE                      1
#define CANFD_DEVCTL_SET_TXDATA        __DIOT(_DCMD_MISC, CANFD_CMD_CODE + 1,   struct canfd_msg)
#define CANFD_DEVCTL_SET_RXDATA        __DIOT(_DCMD_MISC, CANFD_CMD_CODE + 2,   struct canfd_msg)
#define CANFD_DEVCTL_GET_RXDATA        __DIOF(_DCMD_MISC, CANFD_CMD_CODE + 3,   struct canfd_msg)
#define CANFD_DEVCTL_SEND_TXDATA       __DIOT(_DCMD_MISC, CANFD_CMD_CODE + 4,   struct canfd_msg)

#endif