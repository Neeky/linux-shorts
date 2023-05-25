#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <pthread.h>

int x = 100;
int y = 200;

void redirect_point(int **p)
{
    *p = &x;
}

int main()
{
    int *p;
    /**
     * 把 p 指针指向 x ,所以最后的 printf 会打印出 100 来
     */
    redirect_point(&p);
    printf("*p = %d \n", *p);
    return 0;
}