#!/usr/bin/env python3

import socket


def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect(("127.0.0.1", 9875))
        s.send("A".encode("utf8"))
        data = s.recv(1)
        print("got data form server ~{}~ \n".format(data))


if __name__ == "__main__":
    main()
