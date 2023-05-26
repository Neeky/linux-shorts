#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t bin_sem;

void *print_count_function(void *arg)
{
    int print_count = 0;
    char *p_message = (char *)arg;
    int len_message = strlen(p_message);

    while (print_count < 5)
    {
        /**
         * 临界区加锁
         */
        sem_wait(&bin_sem);
        write(1, p_message, len_message + 1);
        sem_post(&bin_sem);

        /**
         * 每一轮循环都要 sleep 1
         */
        sleep(1);

        /**
         * 计数器加 1 、推动循环结束
         */
        print_count++;
    }

    return (void *)NULL;
}

int main(int argc, char **argv)
{
    int res;
    pthread_t thread_a, thread_b;

    /**
     * 初始化信号量
     */
    res = sem_init(&bin_sem, 0, 0);
    if (res != 0)
    {
        printf("init sem failed . \n");
        return 0;
    }

    /**
     * 创建线程
     */
    res = pthread_create(&thread_a, NULL, print_count_function, (void *)"thread - a \n");
    if (res != 0)
    {
        printf("create thread a failed .\n");
        return 0;
    }

    res = pthread_create(&thread_b, NULL, print_count_function, (void *)"thread - b \n");
    if (res != 0)
    {
        printf("create thread b failed .\n");
        return 0;
    }

    /**
     * 信息号加 1 、让 thread-a, thread-b 可以启动起来
     */
    printf("main thread trigger bootstrap \n");
    sem_post(&bin_sem);
    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);
    printf("all sub thread joined \n");
    sem_destroy(&bin_sem);
    return 0;
}