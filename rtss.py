from rts import *

import os
import platform
import struct
import sys
import threading

class MyNotifyDT:
    def __init__(self, rawData):
        self.__rawData = rawData
        if sys.maxsize > 2**32:  # 64-bit
            self.structFormat = 'NH2xI32sI4x'
        else:  # 32-bit
            self.structFormat = 'NH2xI32sI'

        self.__data = list(struct.unpack(self.structFormat, rawData.data))
        if struct.calcsize(self.structFormat) != self.__data[0]:
            raise ValueError("Given size does not match expected.")

    def __update(self):
        self.__rawData.data = struct.pack(self.structFormat, *self.__data)

    @property
    def data1(self):
        return self.__data[1]

    @property
    def data2(self):
        return self.__data[2]

    @property
    def data3(self):
        return self.__data[3]

    @data3.setter
    def data3(self, data3):
        self.__data[3] = bytearray(data3[:32], 'utf-8')
        self.__update()

    @property
    def data4(self):
        return self.__data[4]

    @data4.setter
    def data4(self, data4):
        self.__data[4] = data4
        self.__update()


def rt_ss_trace(message):
    thrId = (threading.get_ident() + 2**32) & 0xffffffff
    sys.stdout.write("TID%08x: " % thrId + message + os.linesep)
    sys.stdout.flush()

cnt = 0
def __notify(pScheduler, pNotId, pServiceId, pNotifyData):
    global cnt
    rt_ss_trace(pScheduler.getConfig().someMethod() + " ... " + "0x%08x" % pNotId + "," + "0x%08x" % pServiceId)
    pScheduler.setMember(23 + cnt)
    notifyData = MyNotifyDT(pNotifyData)
    rt_ss_trace("0x%04x" % notifyData.data1 + " ... 0x%08x" % notifyData.data2)
    notifyData.data3 = 'Hello, World!'
    notifyData.data4 = notifyData.data1 + notifyData.data2
    cnt += 1

def rt_dll_initterm():
    return __notify
