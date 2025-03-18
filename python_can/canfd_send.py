#!/usr/bin/env python
# coding: utf-8

"""
This example shows how sending a single message works.
"""

from __future__ import print_function

import can

def send_one():

	# 创建bus，Bus用于处理具体can接口，详情可以参考：https://python-can.readthedocs.io/en/stable/bus.html
    # bustype表示接口类型，这里使用socketcan
    # channel表示具体的通道名字，这里使用机器上的can6
    # fd表示是否启用canfd，true表示启动canfd
    bus = can.interface.Bus(bustype='socketcan', channel='can6', fd=True)
    
    # 创建msg，Message用于表示can报文，详情可以参考：https://python-can.readthedocs.io/en/stable/message.html
    # arbitration_id表示canfd报文的id
    # dlc表示data参数的长度，canfd一般都为64
    # data表示canfd报文的数据内容，一般情况下都是长度为64的char[]
    # is_extended_id表示当前can报文是否为拓展帧
    # is_fd表示当前报文是否是canfd报文，true表示是canfd报文
    msg = can.Message(arbitration_id=0x123, dlc=64, data=[0, 0x25, 0x0, 1, 3, 1, 4, 1, 0x12], is_extended_id=False, is_fd=True)
    try:
        bus.send(msg)
        print("Message sent on {}".format(bus.channel_info))
    except can.CanError:print("Message NOT sent")


if __name__ == '__main__':
	send_one()
