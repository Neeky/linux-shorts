#include <iostream>
#include <arpa/inet.h>  // inet_addr
#include <sys/socket.h> // socket
#include <unistd.h>     // close

int main(int argc, char **argv)
{
    /**
     * 第一步 创建 client-socket
     */
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        std::cerr << "create socket fail ." << std::endl;
        exit(1);
    }

    /**
     * 第二步 指定 server-addr
     */
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    /**
     * 设置地址时有两种方法，目前看来都不是特别优雅
     * 1. server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
     * 2. inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);
     */
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(9875);

    /**
     * 第三步 连接到服务端口
     */
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) != 0)
    {
        std::cerr << "connect to server fail ." << std::endl;
        exit(2);
    }

    /**
     * 第四步 发送\接收\关闭 socket
     */
    // 准备数据
    char buff[1];
    buff[0] = 'A';

    /**
     * 4.1 发送一个字节到服务端口
     */
    int send_len = send(client_socket, buff, 1, 0);
    if (send_len == -1)
    {
        std::cerr << "send to server fail ." << std::endl;
        exit(3);
    }
    std::cout << "send-len: " << send_len << std::endl;

    /**
     * 4.2 返回收到的字节数
     */
    int recv_len = recv(client_socket, buff, 1, 0);
    if (recv_len == -1)
    {
        std::cerr << "revc from server fail ." << std::endl;
        exit(3);
    }
    std::cout << "recv-len: " << recv_len << std::endl;

    /**
     * 4.3 正常关闭的话会返回 0
     */
    int close_result = close(client_socket);
    if (close_result != 0)
    {
        std::cerr << "close client socket fail ." << std::endl;
        exit(3);
    }
    std::cout << "close function return value : " << close_result << std::endl;
    return 0;
}