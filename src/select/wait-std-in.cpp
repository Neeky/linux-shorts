#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main()
{
    char buffer[128];
    int result, nread;

    /**
     * fd_set 是一个 struct
     */
    fd_set inputs, testfds;
    struct timeval timeout;

    printf("FD_SETSIZE: %d \n", FD_SETSIZE);

    /**
     * 把 inputs 设置为空集
     */
    FD_ZERO(&inputs);
    /**
     * 把标准输入加入到 inputs 集合中
     */
    FD_SET(0, &inputs);

    while (1)
    {
        /**
         * struct 可以看成是标量
         */
        testfds = inputs;
        timeout.tv_sec = 60;
        timeout.tv_usec = 500000;

        /**
         * select 的返回值是已经处理 ready 状态的文件描述符的个数，由于我们只加了一个 stdin ，所以“如果有键盘输入”那么
         * result 的值一定会是 1
         */
        result = select(FD_SETSIZE, &testfds, (fd_set *)NULL, (fd_set *)NULL, &timeout);
        printf("select return value : %d \n", result);
        switch (result)
        {
        case 0:
            printf("timeout\n");
            break;

        case -1:
            perror("select");
            break;

        case 1:
            if (FD_ISSET(0, &testfds))
            {
                /**
                 * 每次读之前要检查一下有多少字节可以读取
                 */
                ioctl(0, FIONREAD, &nread);
                /**
                 * 是不太可能为 0 的，返回 0 是一个异常情况
                 */
                if (nread == 0)
                {
                    printf("keyboard done .");
                    exit(1);
                }
                nread = read(0, buffer, nread);
                buffer[nread] = 0;
                printf("read %d from keyboard: %s", nread, buffer);
            }
            break;
        default:
            /**
             * 理论上是不可能执行到这里的，遇到这种情况就直接退出
             * 原因见 select 的注释
             */
            break;
        }
    }
    return 0;
}