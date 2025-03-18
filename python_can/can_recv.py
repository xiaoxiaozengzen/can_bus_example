#!/usr/bin/env python
# coding: utf-8

"""
This example shows how receive a single message works.
"""

from __future__ import print_function

import can

def recv_one():

	# 创建bus，Bus用于处理具体can接口，详情可以参考：https://python-can.readthedocs.io/en/stable/bus.html
    # bustype表示接口类型，这里使用socketcan
    # channel表示具体的通道名字，这里使用机器上的can6
    # bitrate表示当前can通道的波特率，当前选用500000
    bus = can.interface.Bus(bustype='socketcan', channel='can6', bitrate=500000)

    # 设置filter，只有符合filter条件的报文才会被程序接受。参数为None或者空的list，表示任何报文都会被接受
    # 参数为filter的列表。
    # 对于单个filter，其大致架构为{"can_id", "can_mask"}。例如，当想接受id为A的报文的时候，只有A & can_mask == can_id & can_mask时，报文A才会被接受
    bus.set_filters([{"can_id": 0x123, "can_mask": 0x7FF}]) # 这样设置filter的话，只有0x123的报文会被接受
    
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
	recv_one()
