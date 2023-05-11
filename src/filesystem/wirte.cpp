#include <cstdlib>
#include <cstdio>
#include <unistd.h>

int main()
{
    if (write(1, "hell\n", 5) != 5)
    {
        write(2, "got erorr", 9);
    }
    return 0;
}