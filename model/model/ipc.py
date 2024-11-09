import ctypes
from sys import exception


class IpcMessage(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ("type", ctypes.c_uint),
        ("dataLen", ctypes.c_ulong),
        ("data", ctypes.POINTER(ctypes.c_byte)),
    ]

class IpcMessagesPacker:
    def __init__(self, msgType : int, data : str):
        self.__msgType = msgType
        self.__data = data

    def pack(self) ->bytes:
        dataBytes = self.__data.encode('utf-8')
        # print(dataBytes)
        # print(self.__data)
        msg = IpcMessage()
        msg.type = self.__msgType
        msg.dataLen = len(dataBytes)
        sendBufSize = msg.dataLen + ctypes.sizeof(msg)
        sendBuf : bytes = (ctypes.c_char * sendBufSize)()
        dataStart = ctypes.addressof(getattr(msg, "data")) - ctypes.addressof(msg)
        ctypes.memmove(sendBuf, ctypes.byref(msg), ctypes.sizeof(msg))
        ctypes.memmove(ctypes.addressof(sendBuf) + dataStart, dataBytes, len(dataBytes))
        return sendBuf


class IpcMessagesParser:
    def __init__(self, binData : bytes):
        self.__msg = IpcMessage()
        try:
            msgLen = ctypes.addressof(getattr(self.__msg, "data")) - ctypes.addressof(self.__msg)
            ctypes.memmove(ctypes.addressof(self.__msg), binData, msgLen)
            # print("data type: " + str(self.__msg.type))
            # print("data len: " + str(self.__msg.dataLen))   # OK
            self.__data : bytes = (ctypes.c_char * self.__msg.dataLen)()
            ctypes.memmove(ctypes.addressof(self.__data), ctypes.addressof(self.__msg) + ctypes.sizeof(self.__msg), self.__msg.dataLen)
            # print(self.__data)
            # print("data: " + str(self.__data))
        except Exception as e:
            # print(e)
            pass

    def type(self) -> int:
        return self.__msg.type

    def dataLen(self) -> int:
        return self.__msg.dataLen

    def data(self) -> bytes:
        return self.__data

    def dataToUtf8Str(self) -> str:
        dataStr = ''
        try:
            dataStr = bytes(self.__data).decode("utf-8", errors='ignore')
        except Exception as e:
            # print(e)
            pass
        return dataStr
