#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    //
    FILE *filp;
    char content[] = "this fread & fwrite function";
    char buffer[32];
    int reads = 0;

    // 打开文件
    if ((filp = fopen("/tmp/a.txt", "r+")) == NULL)
    {
        cout << "open file error" << endl;
        cout << "errno:" << errno << endl;
        return 0;
    }

    //
    reads = fread(buffer, 1, strlen(content) + 1, filp);
    fclose(filp);

    // 所有数据都读出来了，因为后面我们要把它当成字符串来用，所以这里要在后面加一个 '\0'
    buffer[reads] = '\0';
    printf("content of file /tmp/a.txt = '%s'.", buffer);

    return 0;
}