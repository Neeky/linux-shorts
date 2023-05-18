#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

/**
 * 只能说 tm 这个数据结构是真的难用
 */

int main()
{
    int i;
    time_t the_time = time(NULL);
    struct tm *tmptr = gmtime(&the_time);
    /**
     * 使用年的时候要特别注意了，这个里的年是自 1900 起的年数，如果要得到当前是多少年，那么就要加上个 1900 。
     */
    printf("current year : %d \n", tmptr->tm_year + 1900);
    /**
     * 月分也是SB东西，这个 tm_mon 的范围是 [0, 11] 所以这里要加 1 ，才能得到当前的月分
     */
    printf("current month : %d \n", tmptr->tm_mon + 1);
    /**
     * 一个月中的第几天
     */
    printf("current month : %d \n", tmptr->tm_mday);
    /**
     * 东8区(北京时间)还要在小时上加个 8
     */
    printf("curent time %d:%d:%d \n", tmptr->tm_hour + 8, tmptr->tm_min, tmptr->tm_sec);
    return 0;
}