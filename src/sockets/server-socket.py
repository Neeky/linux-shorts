#!/usr/bin/env python3

import socket


def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind(("127.0.0.1", 9875))
        s.listen(128)
        conn, addr = s.accept()
        with conn:
            print("got client connection .\n")
            while True:
                data = conn.recv(1)
                if data:
                    break
                else:
                    print("data = '{}' \n".format(data))
                    conn.send("Q")
                    break


if __name__ == "__main__":
    main()
