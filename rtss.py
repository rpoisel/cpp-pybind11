from rts import *

import struct

class MyNotifyDT:
    FORMAT = 'NH2xI32sI4x'

    def __init__(self, rawData):
        self.__rawData = rawData
        self.__data = list(struct.unpack(MyNotifyDT.FORMAT, rawData.data))
        if struct.calcsize(MyNotifyDT.FORMAT) != self.__data[0]:
            raise ValueError("Given size does not match expected.")

    def __update(self):
        self.__rawData.data = struct.pack(MyNotifyDT.FORMAT, *self.__data)

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


def __notify(pScheduler, pNotId, pServiceId, pNotifyData):
    try:
        print(pScheduler.getConfig().someMethod() + " ... " + str(pNotId) + "," + str(pServiceId))
        pScheduler.setMember(23)
        notifyData = MyNotifyDT(pNotifyData)
        print("0x%04x" % notifyData.data1 + " ... 0x%08x" % notifyData.data2)
        notifyData.data3 = 'Hello, World!'
        notifyData.data4 = 0xaabbccdd
    except Exception as e:
        print(e)

def rt_dll_initterm():
    return __notify
