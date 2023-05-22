#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>
#include <cmath>

int fib(int n)
{
    if (n == 1 || n == 2)
    {
        return 1;
    }
    else
    {
        return fib(n - 1) + fib(n - 2);
    }
}

void worker(int n)
{
    int j = 0;
    for (int i = 1; i < n; i++)
    {
        j = fib(i);
        printf("fib(%d) = %ld \n", i, j);
    }
}

int main()
{

    struct rusage r_usage;
    struct rlimit r_limit;
    int priority;
    puts("enter woker");
    worker(32);
    puts("exit woker");
    getrusage(RUSAGE_SELF, &r_usage);
    printf("cpu usage: User = %ld.%06ld, System = %ld.%06ld \n",
           r_usage.ru_utime.tv_sec, r_usage.ru_utime.tv_usec,
           r_usage.ru_stime.tv_sec, r_usage.ru_stime.tv_usec);

    return 0;
}