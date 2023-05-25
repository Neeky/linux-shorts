#include <iostream>
#include <stdio.h>
int main(int, char **)
{
    /**
     * 这里的 05 用于限定宽度
     */
    // printf("%05ld\n", 8);
    // printf("%05ld\n", 160);

    printf("sizeof(char *) = %d \n", sizeof(char *));
    printf("sizeof(int *) = %d \n", sizeof(int *));
    std::cout << "Hello, world!\n";
}
