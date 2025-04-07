#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

static int value = 0;
sem_t semdummy;

void* increment_global(void *ch)
{
    int local = 0, result;

    result = sem_wait(&semdummy);
    if(result != 0)
        perror("sem_wait error");

    for(int i = 1; i<=10000; i++)
    {
        local = value;
        local++;
        value = local;
    }
    
    result = sem_post(&semdummy);
    if(result != 0)
        perror("sem_post error");

    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_t tid1, tid2, tid3;
    int result1,result2,result3;

    printf("I'm in the Parent thread now with pid %d.\n",getpid());
    if(sem_init(&semdummy,0,1)==-1)     //Values '0' & '1' indicate 'semaphore usage within process among threads' & 'semaphore value' respectively.
    {
        perror("Error in sem_init");
        exit(-1);
    }
    
    result1 = pthread_create(&tid1,NULL,increment_global,"SitaRam!");
    if(result1 != 0)
    {
        perror("Error crearing a thread1.\n");
        exit(-1);
    }
    
    result2 = pthread_create(&tid2,NULL,increment_global,"SriRam!");
    if(result1 != 0)
    {
        perror("Error crearing a thread2.\n");
        exit(-1);
    }

    result3 = pthread_create(&tid3,NULL,increment_global,"JanakiRam!");
    if(result1 != 0)
    {
        perror("Error crearing a thread3.\n");
        exit(-1);
    }

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);
    sem_destroy(&semdummy);
    printf("\nParent thread is exiting now and the final value is: %d.\n",value);
     
    return 0;
}