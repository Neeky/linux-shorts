#include <cstdlib>
#include <cstdio>
#include <unistd.h>

int main()
{
    char buffer[128];
    int nreads = 0;

    // 读取标准输入
    nreads = read(0, buffer, 128);
    if (nreads == -1)
    {
        write(2, "got faile on read.", 18);
    }

    // 把读取到的输入打印到标准输出
    if (write(1, buffer, nreads) != nreads)
    {
        write(2, "got faile on write.", 19);
    }
    return 0;
}