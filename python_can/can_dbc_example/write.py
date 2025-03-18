#!/usr/bin/env python
# coding: utf-8

"""
This example shows how sending a single message works.
"""

from __future__ import print_function

import can
import canmatrix

# dbc文件路径
dbc_file = "./dbc/MCS1FMR.dbc"

# load matrix
db = canmatrix.formats.loadp_flat(dbc_file)

def read_signal_value_from_user(signal, p_value):
    if signal.is_float:
        return float(p_value)
    else:
        return int(p_value)

def send_one():

	# 创建bus，Bus用于处理具体can接口，详情可以参考：https://python-can.readthedocs.io/en/stable/bus.html
    # bustype表示接口类型，这里使用socketcan
    # channel表示具体的通道名字，这里使用机器上的can6
    # bitrate表示当前can通道的波特率，当前选用500000
    bus = can.interface.Bus(bustype='socketcan', channel='can1', bitrate=500000)

    # 生成要发送的msg的id。需要坐下转化，Message对象中的id到canmatrix中的id
    arbitration_id = canmatrix.ArbitrationId(int(hex(0x551), 16), extended = False)
    print("arbitration_id: %x"%arbitration_id.id)

    # 基于message id找到对应的message的报文，即其结构体
    frame = db.frame_by_id(arbitration_id)
    print (frame.name)

    # 信号
    signalDict = dict()
    
    # go through all signals
    for signal in frame.signals:
        if signal.name == "detNumEntries":
            signalDict[signal.name] = read_signal_value_from_user(signal, 10)
        elif signal.name == "numTxdets":
            signalDict[signal.name] = read_signal_value_from_user(signal, 0)
        elif signal.name == "objNumEntries":
            signalDict[signal.name] = read_signal_value_from_user(signal, 20)
        elif signal.name == "numTxObjs":
            signalDict[signal.name] = read_signal_value_from_user(signal, 15)
        else:
            print("signal name not found: {}".format(signal.name))

    # encode 
    frame_data = frame.encode(signalDict)

    # 创建msg，Message用于表示can报文，详情可以参考：https://python-can.readthedocs.io/en/stable/message.html
    # arbitration_id表示can报文的id
    # data表示can报文的数据内容，一般情况下都是长度为8的char[]
    # is_extended_id表示当前can报文是否为拓展帧
    msg = can.Message(arbitration_id=arbitration_id.id, data=frame_data, is_extended_id=arbitration_id.extended)
    try:
        bus.send(msg)
        print("Message sent on {}".format(bus.channel_info))
    except can.CanError:print("Message NOT sent")

    # 关闭socket
    bus.shutdown()


if __name__ == '__main__':
	send_one()
