#include <cstdlib>
#include <cstdio>
// #include <unistd.h>
// #include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

int main()
{

    /**
     * 打开一个不存在的文件会报错
     */
    int file_des = open("/tmp/uuuu.xxx", O_RDONLY);
    if (file_des == -1)
    {
        /**
         * 这个函数可以方便的打印出错误日志 open file fail error-message ->: No such file or directory
         * 也就是说它会把 errno 对应的错误信息给打印出来
         */
        perror("open file fail error-message ->");
        /**
         * errno: 2
         */
        printf("errno: %d \n", errno);
    }
    return 0;
}