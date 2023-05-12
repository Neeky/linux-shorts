#include <cstdio>
#include <cstdlib>
#include <iostream>

int main(int argc, char **argv)
{
    int i;
    for (i = 0; i < argc; i++)
    {
        // std::cout << i << std::endl;
        std::cout << "argv[" << i << "]=" << argv[i] << std::endl;

        // /data/repos/linux-shorts/build/linux-shorts-getoption001 --user=mysql --port=3306 -u
        // argv[0]=/data/repos/linux-shorts/build/linux-shorts-getoption001
        // argv[1]=--user=mysql
        // argv[2]=--port=3306
        // argv[3]=-u
    }

    return 0;
}