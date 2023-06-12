#include <iostream>
#include <arpa/inet.h>  // inet_addr
#include <sys/socket.h> // socket
#include <unistd.h>     // close

int main(int argc, char **argv)
{
    using namespace std;
    /**
     * 第一步 创建出 server-socket
     */
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        cerr << "create socket fail ." << endl;
        return 1;
    }

    /**
     * 第二步 配置地址信息+bind
     */
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9875);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    int reuse = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuse, sizeof(int));
    int bind_res = bind(server_socket, (sockaddr *)&server_address, sizeof(server_address));
    if (bind_res == -1)
    {
        cerr << "bind server-address fail ." << endl;
        close(server_socket);
        return 2;
    }

    /**
     * 第三步 listen
     */
    int listen_res = listen(server_socket, 255);
    if (listen_res == -1)
    {
        cerr << "listen fail ." << endl;
        close(server_socket);
        return 2;
    }

    /**
     * 第四小 accept
     */
    struct sockaddr_in client_address;
    socklen_t addrlen = sizeof(client_address);
    int client_socket = accept(server_socket, (struct sockaddr *)&client_socket, &addrlen);
    if (client_socket == -1)
    {
        cerr << "accept fail ." << endl;
        close(server_socket);
        return 2;
    }

    /**
     * 第五步 接收数据
     */
    char buff[1024] = {0};
    int recv_len = recv(client_socket, buff, 1024, 0);
    if (recv_len == -1)
    {
        cerr << "recv-len: " << recv_len << " fail ." << endl;
        close(client_socket);
        close(server_socket);
        return 2;
    }
    cout << "revc from client : " << buff << endl;

    /**
     * 第六步 发送数据(只发一个字节)
     * 发送回 client 的字符是，收到的字符+1 ，如收到 A 发一个 B ，收到 C 发一个 D 。
     */
    buff[0]++;
    int send_len = send(client_socket, buff, 1, 0);
    if (send_len == -1)
    {
        cerr << "send fail ." << endl;
        close(client_socket);
        close(server_socket);
        return 2;
    }
    cout << "send " << buff << " to client ." << endl;
    cout << "server going to exit ." << endl;

    close(client_socket);
    close(server_socket);
    cout << "bye bye ." << endl;
    return 0;
}