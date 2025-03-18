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
    
    # msg，Message用于表示can报文，详情可以参考：https://python-can.readthedocs.io/en/stable/message.html
    while True:
        try:
            # 返回值msg，Message用于表示can报文，详情可以参考：https://python-can.readthedocs.io/en/stable/message.html
            # arbitration_id表示can报文的id
            # data表示can报文的数据内容，一般情况下都是长度为8的char[]
            msg = bus.recv() # 当然也可以使用recv(2)，其中2表示超时时间，单位s
            if msg is None:
                print("Message NOT received")
            print(msg)
        except can.CanError:print("Message Recv Failed")

    # 关闭socket
    bus.shutdown()


if __name__ == '__main__':
	send_one()
