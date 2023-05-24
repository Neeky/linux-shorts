#include <cstdlib>
#include <cstdio>
#include <unistd.h>

int main()
{
    int size = 8;
    int *number = nullptr;
    number = (int *)malloc(size);
    if (number == nullptr)
    {
        printf("malloc fail .\n");
        return 0;
    }
    *number = 200;
    printf("number = %d \n", *number);

    return 0;
}