import sys
import server

if __name__ == '__main__':
    # if len(sys.argv) != 2:
    #     sys.exit(-1)

    # baseDir = sys.argv[1]

    with server.UnixSocketServer(server.IPC_SOCKET_PATH, server.RequestHandler) as server:
        server.serve_forever()
    exit(0)

