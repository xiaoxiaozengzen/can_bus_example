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
    # bitrate表示当前can通道的波特率，当前选用500000
    bus = can.interface.Bus(bustype='socketcan', channel='can6', bitrate=500000)
    
    # 创建msg，Message用于表示can报文，详情可以参考：https://python-can.readthedocs.io/en/stable/message.html
    # arbitration_id表示can报文的id
    # data表示can报文的数据内容，一般情况下都是长度为8的char[]
    # is_extended_id表示当前can报文是否为拓展帧
    msg = can.Message(arbitration_id=0x123, data=[0, 0x25, 0x0, 1, 3, 1, 4, 1], is_extended_id=False)
    try:
        bus.send(msg)
        print("Message sent on {}".format(bus.channel_info))
    except can.CanError:print("Message NOT sent")

    # 关闭socket
    bus.shutdown()


if __name__ == '__main__':
	send_one()
