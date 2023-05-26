#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <pthread.h>

int run_now = 1;

void *print_count_function(void *arg)
{
    int print_count = 0;
    while (print_count < 5)
    {
        if (run_now == 2)
        {
            // printf("2");
            write(1, "1", 1);
            run_now = 1;
            print_count++;
        }
        else
        {
            sleep(1);
        }
    }
    return (void *)NULL;
}

int main()
{
    int print_count = 0;
    pthread_t thread_a;

    printf("start sub thread ....\n");
    pthread_create(&thread_a, NULL, print_count_function, NULL);

    printf("main thread start counting ....\n");
    while (print_count < 5)
    {
        if (run_now == 1)
        {
            // printf("1");
            write(1, "2", 1);
            run_now = 2;
            print_count++;
        }
        else
        {
            sleep(1);
        }
    }
    pthread_join(thread_a, NULL);
    printf("\nsub thread joined ....\n");

    return 0;
}