#include <unistd.h>
#include <cstdlib>
#include <cstdio>

int main(int argc, char **argv)
{
    int opt;
    printf("argc = %d \n", argc);
    for (int i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s \n", i, argv[i]);
    }
    puts("//////////////////////////////////");

    while (true)
    {
        /**
         * 可以使用如下方式接收短选项参数
         * linux-shorts-getopt -h 127.0.0.1 -P 3306
         * 按 linux 的规范来说 -P 3306 这样的形式是对的，也就是“选项”与“值”之间不能用 “=” 号
         */
        opt = getopt(argc, argv, "h:P:");

        /**
         * 返回 -1 说明已经搞完了
         */
        if (opt == -1)
        {
            break;
        }

        /**
         * opt 对应选项名
         * optarg 对应的是选项值
         */
        printf("current opt = %c \n", opt);
        printf("current optarg = %s \n", optarg);
    }
}