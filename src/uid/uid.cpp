#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

int main()
{
    uid_t uid = getuid();
    printf("current uid = %d \n", uid);
    return 0;
}