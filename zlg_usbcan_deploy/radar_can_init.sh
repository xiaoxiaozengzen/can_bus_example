#!/bin/bash

set -xe

# 设置canfd
function set_canfd_channel()
{
        sudo ip link set can$1 down
        sudo ip link set can$1 type can bitrate 500000 sample-point 0.8 dbitrate 2000000 dsample-point 0.8 restart-ms 100 fd on
        sudo ip link set can$1 up
}

# 设置can
function set_can_channel()
{
        sudo ip link set can$1 down
        sudo ip link set can$1 type can bitrate 500000
        sudo ip link set can$1 up
}

# wait for pcan device ready
sleep 2

# 检查是否有zlg usbcan设备
zlg_usb="ZLG"
usb_ret=`lsusb`
if [[ ${usb_ret} =~ ${zlg_usb} ]];then
        echo "zlg usbcan device is exist"
else
        echo "zlg usbcan device is not exist"
        exit 1
fi

# 检查是否内核加载zlg usbcan模块
mod_ret=`lsmod | grep can`
zlg_usbcan_mod="~/usbcanfd200_400u/usbcanfd.ko"
if [[ ${mod_ret} =~ "usbcan" ]];then
        echo "zlg usbcan module is loaded"
else
        echo "zlg usbcan module is not loaded"
        if [ -f ${zlg_usbcan_mod} ];then
                echo "load zlg usbcan module"
                sudo insmod ${zlg_usbcan_mod}
        else
                echo "zlg usbcan module is not exist: ${zlg_usbcan_mod}"
                exit 1
        fi
fi

# 设置can通道
# 此处因为can0是系统默认的can通道，所以从can1开始设置
can_channel_num=`ip addr | grep -E " can[0-9]*:" | wc -l`
for (( i=1; i<${can_channel_num}; i++ ));do
        can_class=`ls -la /sys/class/net/can${i}`
        if [[ ${can_class} =~ "mttcan" ]];then
                echo "set mttcan can channel: "
                set_canfd_channel ${i}
        elif [[ ${can_class} =~ "usb" ]];then
                echo "set usb can channel:"
                set_canfd_channel ${i}
        else
                echo "other can channel"
                set_canfd_channel ${i}
        fi
done
