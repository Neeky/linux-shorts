#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t mutex;

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
        pthread_mutex_lock(&mutex);
        write(1, p_message, len_message + 1);
        pthread_mutex_unlock(&mutex);

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
    res = pthread_mutex_init(&mutex, NULL);
    if (res != 0)
    {
        printf("init mutex failed . \n");
        return 0;
    }

    /**
     * 先让主线程持有 mutex ，这样的话其它的线程就跑不起来了，后面通过释放锁的方式把其它线程跑起来
     */
    pthread_mutex_lock(&mutex);

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
    pthread_mutex_unlock(&mutex);
    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);
    printf("all sub thread joined \n");
    pthread_mutex_destroy(&mutex);
    return 0;
}