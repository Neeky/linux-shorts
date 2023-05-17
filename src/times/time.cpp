#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

int main()
{
    int i;
    time_t the_time;
    for (i = 0; i < 3; i++)
    {
        /**
         * 以下两种写法都可以取得当前系统以秒计的时间值(timestamp)
         * the_time = time((time_t *)0);
         * the_time = time(NULL);
         */
        the_time = time((time_t *)0);
        printf("current time = %ld \n", the_time);
        sleep(1);
    }

    /**
     * 这里已经是 8 字节的时间了
     * this size of time_t = 8
     */
    printf("this size of time_t = %d \n", sizeof(time_t));
    return 0;
}