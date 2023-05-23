#include <iostream>
#include <stdio.h>
int main(int, char **)
{
    /**
     * 这里的 05 用于限定宽度
     */
    printf("%05ld\n", 8);
    printf("%05ld\n", 160);
    std::cout << "Hello, world!\n";
}
