import sys
from Translator import Translator
from Server import UnixSocketServer, IPC_SOCKET_PATH, RequestHandler

if __name__ == '__main__':
    if len(sys.argv) != 2:
        sys.exit(-1)

    modelBaseDir = sys.argv[1]
    Translator.setModelBaseDir(modelBaseDir)

    with UnixSocketServer(IPC_SOCKET_PATH, RequestHandler) as server:
        server.serve_forever()
    exit(0)

