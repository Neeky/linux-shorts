#include <sys/types.h>
#include <sys/socket.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
    int socketfd;
    struct sockaddr_in address;
    int len;
    int result;
    char ch = 'A';

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = 9875;
    len = sizeof(address);

    result = connect(socketfd, (struct sockaddr *)&address, len);
    if (result == -1)
    {
        perror("connect server socket failed. \n");
        exit(EXIT_FAILURE);
    }

    write(socketfd, &ch, 1);
    read(socketfd, &ch, 1);
    printf("recived ch from server %c \n", ch);
    close(socketfd);
    return 0;
}