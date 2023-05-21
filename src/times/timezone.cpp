#include <cstdio>
#include <cstdlib>
#include <ctime>

extern char *tzname[2];

int main()
{
    printf("start tzname = %d \n", timezone); // start tzname = 0
    tzset();
    printf("start tzname = %d \n", timezone); // start tzname = -28800
    return 0;
}