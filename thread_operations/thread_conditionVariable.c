#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

static int value = 0;
int cond_set = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cnd = PTHREAD_COND_INITIALIZER;

void* increment_functionA(void *ch)
{
    printf("Thread-A scheduled first\n");
    pthread_mutex_lock(&mtx);
    printf("Critical section of Thread-A started.\n");
    value = 54;
    cond_set = 1;
    pthread_cond_signal(&cnd);
    pthread_mutex_unlock(&mtx);
}

void* increment_functionB(void *ch)
{
    printf("Thread-B scheduled first\n");
    pthread_mutex_lock(&mtx);
    if(cond_set == 0)
       pthread_cond_wait(&cnd,&mtx);
    printf("Critical section of Thread-B started.\n");
    printf("The value sent from Thread-A to Thread-B is: %d.\n", value);
    pthread_mutex_unlock(&mtx);
}

int main(int argc, char* argv[])
{
    pthread_t tid1, tid2;
    int result1,result2;
    void* returnValue;
    printf("I'm in the Parent thread now with pid %d.\n",getpid());
    
    result1 = pthread_create(&tid1,NULL,increment_functionA,"SitaRam!");
    if(result1 != 0)
    {
        perror("Error crearing a threadA.\n");
        exit(-1);
    }
    
    result2 = pthread_create(&tid2,NULL,increment_functionB,"SriRam!");
    if(result1 != 0)
    {
        perror("Error crearing a threadB.\n");
        exit(-1);
    }

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
     
    return 0;
}