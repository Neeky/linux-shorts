#include <cstdio>
#include <cstdlib>
#include <sys/time.h>

int main()
{
    struct timeval tv;
    // 这个 gettimeofday 函数还没有学会用。
    printf("gettimeofday = %d \n", gettimeofday(&tv, NULL)); // start tzname = 0
    return 0;
}