#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * 复制 /etc/hosts 文件内容到 /tmp/hosts
 * 1. 这里假设所有的系统调用都能成功
 *
 * 检查
 * md5sum /etc/hosts
 * 6ce62b457f68c002d9b62ab0690252aa  /etc/hosts
 *
 *
 * md5sum /tmp/hosts
 * 6ce62b457f68c002d9b62ab0690252aa  /tmp/hosts
 */

int main(int argc, char **argv)
{
    // 一次复制一个字符，每一个字符都需要一个系统调用，所以这里会极大的影响性能
    char c;
    int in, out;

    // 打开文件
    in = open("/etc/hosts", O_RDONLY);
    out = open("/tmp/hosts", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

    // buffer 可以是一个数组、也可以是一个字符
    while (read(in, &c, 1) == 1)
    {
        write(out, &c, 1);
    }
    return 0;

    // 这个让系统自己退出的时候去 close 文件
}