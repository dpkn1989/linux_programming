#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

static int value = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* increment_global(void *ch)
{
    int local = 0, result;

    result = pthread_mutex_lock(&mtx);

    if(result != 0)
        perror("Error locking mutex");

    for(int i = 1; i<=100000; i++)
    {
        local = value;
        local++;
        value = local;
    }
    
    result = pthread_mutex_unlock(&mtx);
}

int main(int argc, char* argv[])
{
    pthread_t tid1, tid2;
    int result1,result2;
    void* returnValue;
    printf("I'm in the Parent thread now with pid %d.\n",getpid());
    
    result1 = pthread_create(&tid1,NULL,increment_global,"SitaRam!");
    if(result1 != 0)
    {
        perror("Error creating thread1.\n");
        exit(-1);
    }
    
    result2 = pthread_create(&tid2,NULL,increment_global,"SriRam!");
    if(result2 != 0)
    {
        perror("Error crearing thread2.\n");
        exit(-1);
    }

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    printf("\nParent thread is exiting now and the final value is: %d.\n",value);
     
    return 0;
}