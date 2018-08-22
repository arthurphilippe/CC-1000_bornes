#!/bin/python3

import socket  # for sockets
import sys  # for exit


def create():
    try:
        # create an AF_INET, STREAM socket (TCP)
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except socket.error as error:
        raise RuntimeError(error)
    return s


def connect(sock, hostname="0.0.0.0", port=4242):
    # Resolve the hostname
    try:
        remote_ip = socket.gethostbyname(hostname)

    except socket.error as error:
        raise RuntimeError(error)
    print('Resolved hostname ' + hostname + ' as being ' + remote_ip)

    # Connect to remote server
    try:
        sock.connect((remote_ip, port))
    except socket.error as error:
        raise RuntimeError(error)

    print('Socket Connected to ' + hostname + ' on ip ' + remote_ip)


def fillQueue(sock, queue):
    reply = sock.recv(2048)
    reply = reply.decode('UTF-8')
    if len(reply) is not 0:
        splitReply = reply.split('\n')
        for i in range(len(splitReply)):
            splitReply[i] = splitReply[i].strip('\r')
        for i in range(len(splitReply)):
            if len(splitReply[i]) is 0:
                splitReply.pop(i)
    else:
        splitReply = ['quit']
    return queue + splitReply


if __name__ == '__main__':
    print('tcp module: self test')
    if len(sys.argv) < 3:
        sys.exit(1)
    host = sys.argv[1]

    try:
        port = int(sys.argv[2])
    except Exception as error:
        print(error)
        sys.exit(1)

    try:
        s = create()
    except RuntimeError as error:
        print(error)
        sys.exit(1)

    try:
        connect(s, host, port)
        print('Socket Created')
    except RuntimeError as error:
        print(error)
        sys.exit(1)
    finally:
        s.close()
        print('Socket Closed')
