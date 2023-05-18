#include <cstdio>
#include <cstdlib>

int main(int argc, int argv)
{
    char *name = tmpnam(NULL);
    /**
     * 返回 /tmp/ 目录下一个绝对不会重复的文件名
     *
     * 如: /tmp/fileC0yerh
     */
    printf("temp-name : %s \n", name);
    return 0;
}