import os
import socket
import threading
import socketserver
from concurrent.futures import ThreadPoolExecutor

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
            pass

        print("read: " + str(binData))
        # 发送响应
        try:
            self.request.sendall(bytes(binData))
        except Exception as e:
            pass


class UnixSocketServer(socketserver.ThreadingMixIn, socketserver.UnixStreamServer):
    def __init__(self, addr, RequestHandlerClass):
        super().__init__(addr, RequestHandlerClass)
        # 创建线程池
        self.executor = ThreadPoolExecutor(100)

    def process_request(self, request, clientAddress):
        # 使用线程池处理请求
        print("new thread")
        # self.executor.submit(self.finish_request, request, clientAddress)
        self.executor.submit(self.process_request_thread, request, clientAddress)

    def shutdown(self):
        # 关闭线程池
        self.executor.shutdown(wait=True)
        super().shutdown()