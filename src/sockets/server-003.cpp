#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main()
{
    /**
     * 第一步
     */
    int server_socket, client_socket;
    socklen_t server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    int result;
    fd_set readfds, testfds;

    /**
     * 第二步 创建 socket 文件
     */
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    /**
     * 第三步 配置地址信息
     */
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(9875);
    server_len = sizeof(server_address);
    int reuse = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuse, sizeof(int));
    int bind_res = bind(server_socket, (sockaddr *)&server_address, server_len);
    if (bind_res == -1)
    {
        printf("bind faild .\n");
        perror("bind:");
        close(server_socket);
        return 0;
    }
    printf("bind .\n");

    int listen_res = listen(server_socket, 127);
    if (listen_res == -1)
    {
        printf("listen fail .\n");
        perror("listen");
        close(server_socket);
        return 0;
    }
    printf("listen .\n");

    FD_ZERO(&readfds);
    FD_SET(server_socket, &readfds);

    while (true)
    {
        char ch;
        int fd;
        int nread;

        testfds = readfds;
        printf("server waiting \n");

        result = select(FD_SETSIZE, &testfds, (fd_set *)NULL, (fd_set *)NULL, (struct timeval *)NULL);

        if (result < 1)
        {
            perror("server");
            exit(1);
        }

        // 因为最多就只能是有 FD_SETSIZE 个
        for (fd = 0; fd < FD_SETSIZE; fd++)
        {
            if (FD_ISSET(fd, &testfds))
            {
                if (fd == server_socket)
                {
                    client_len = sizeof(client_address);
                    client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_len);
                    FD_SET(client_socket, &readfds);
                    printf("adding client fd %d \n", client_socket);
                }
                else
                {
                    ioctl(fd, FIONREAD, &nread);
                    if (nread == 0)
                    {
                        close(fd);
                        FD_CLR(fd, &readfds);
                        printf("removing client on fd %d \n", fd);
                    }
                    else
                    {
                        read(fd, &ch, 1);
                        printf("server client on fd %d \n", fd);
                        ch++;
                        write(fd, &ch, 1);
                    }
                }
            }
        }
    }

    return 0;
}