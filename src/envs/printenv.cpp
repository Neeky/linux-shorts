#include <cstdio>
#include <cstdlib>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc <= 1 || argc >= 3)
    {
        printf("usage: printenv envname .\n");
        return 0;
    }

    char *envname = argv[1];
    printf("%s=%s \n", envname, getenv(envname));
    return 0;
}