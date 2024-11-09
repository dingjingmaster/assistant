import os
import socket
import threading
import socketserver
from concurrent.futures import ThreadPoolExecutor

from Translator import translatorInstance
from ipc import IpcMessagesParser
from model.ipc import IpcMessagesPacker

IPC_TYPE_TRANSLATOR                     = 1

IPC_SOCKET_PATH = '/tmp/assistant-translator.sock'

if os.path.exists(IPC_SOCKET_PATH):
    os.remove(IPC_SOCKET_PATH)

class RequestHandler(socketserver.BaseRequestHandler):
    def handle(self):
        # 接收数据
        self.request.setblocking(False)
        binData = b""
        try:
            while True:
                data = self.request.recv(1024)
                if not data:
                    break
                binData += data
        except Exception as e:
            # print(e)
            pass

        # print(binData.decode('utf8', 'ignore'))

        # msg = IpcMessagesParser(binData)
        englishStr = binData.decode('utf-8', errors='ignore') # msg.dataToUtf8Str()
        if len(englishStr) < 0:
            return
        chineseStr = translatorInstance().englishToChinese(englishStr=englishStr)
        # packer = IpcMessagesPacker(msgType=IPC_TYPE_TRANSLATOR, data=chineseStr)
        # print("src: " + englishStr)
        # print("dst: " + chineseStr)
        chineseBytes = chineseStr.encode('utf-8') # packer.pack()
        try:
            # 发送响应
            self.request.sendall(chineseBytes)
        except Exception as e:
            pass


class UnixSocketServer(socketserver.ThreadingMixIn, socketserver.UnixStreamServer):
    def __init__(self, addr, RequestHandlerClass):
        super().__init__(addr, RequestHandlerClass)
        # 创建线程池
        self.executor = ThreadPoolExecutor(100)

    def process_request(self, request, clientAddress):
        # 使用线程池处理请求
        self.executor.submit(self.process_request_thread, request, clientAddress)

    def shutdown(self):
        # 关闭线程池
        self.executor.shutdown(wait=True)
        super().shutdown()