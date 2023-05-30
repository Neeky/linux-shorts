#!/usr/bin/env python3

import socket
import logging

logging.basicConfig(level=logging.DEBUG)


def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind(("127.0.0.1", 9875))
        s.listen(128)
        while True:
            logging.info("ready to accept connection .")
            conn, addr = s.accept()
            with conn:
                logging.info("got client connection from {} .".format(addr))
                data = conn.recv(1)
                # 现在已经是 str 了
                data = data.decode("utf-8")
                logging.info("we got '{}' from client .".format(data))
                # 把刚才收到的字符 + 1 之后写回到 client
                code = ord(data) + 1
                res = chr(code)
                logging.info("we well send '{}' to client .".format(res))
                conn.send("{}".format(res).encode("utf8"))


if __name__ == "__main__":
    main()
