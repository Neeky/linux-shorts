#include <cstdlib>
#include <unistd.h>
#include <cstdio>

#define _GUN_SOURCE
#include <getopt.h>

int main(int argc, char **argv)
{
    int opt = 0;
    struct option longopts[] = {
        /**
         * 长选项名，选项是否有值1表示有，0 表示没有, NULL, 短选项名
         */
        {"host", 1, NULL, 'h'},
        {"port", 1, NULL, 'P'}};

    while (true)
    {
        opt = getopt_long(argc, argv, "h:P:", longopts, NULL);
        if (opt == -1)
        {
            return 0;
        }
        printf("current opt = %c, optarg = %s \n", opt, optarg);
    }

    return 0;
}