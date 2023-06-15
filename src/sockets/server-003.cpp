#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
    using namespace std;
    /**
     * 第一步 创建 socket 文件
     */

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        cerr << "create socket fail ." << endl;
        perror("socket:");
        return 1;
    }
    cout << "server-socket created ." << endl;
    int reuse = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (void *)&reuse, sizeof(reuse));
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEPORT, (void *)&reuse, sizeof(reuse));
    /**
     * 配置 server-socket 的地址信息
     */
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(9875);

    /**
     * 第二步执行 bind
     */
    int bind_res = bind(server_socket, (sockaddr *)&server_address, sizeof(server_address));
    if (bind_res == -1)
    {
        cerr << "bind socket fail ." << endl;
        perror("bind:");
        return 2;
    }
    cout << "server-socket bind ." << endl;

    /**
     * 第三步 listen
     */
    int listen_res = listen(server_socket, 521);
    if (listen_res == -1)
    {
        cerr << "socket listen fail ." << endl;
        return 3;
    }
    cout << "server-socket listen ." << endl;

    sockaddr_in client_address;
    socklen_t addrlen = sizeof(client_address);
    while (true)
    {
        int client_socket = accept(server_socket, (sockaddr *)&client_address, &addrlen);
        if (client_socket == -1)
        {
            cerr << "sock accept fail ." << endl;
            close(client_socket);
            return 4;
        }
        cout << "accept new cleint fd: %d " << client_socket << endl;
        /**
         * 先读一个字符，然后再写一个新字符回去
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
         * 写一个字符回 client
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

        close(client_socket);
        cout << "client socket close ." << endl;
        /** end while */
    }

    close(server_socket);
    cout << "server-socket close ." << endl;

    return 0;
}