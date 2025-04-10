#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void* run_loop(void *ch)
{
    char* arg = (char*)ch;
    printf("I'm in the thread now with argument <%s> and pid: %d.\n\n",arg,getpid());
    for(int i = 1; i<=5; i++)
    {
        printf("The loop is running at count: %d\n",i);
        sleep(1);
    }
    printf("\nI'm exiting the thread now.\n");
    
    return (void*)"Thread successfully executed!";
}

int main(int argc, char* argv[])
{
    pthread_t tid;
    int result1,result2;
    void* returnValue;
    printf("I'm in the Parent thread now with pid %d.\n",getpid());
    result1 = pthread_create(&tid,NULL,run_loop,"SitaRam!");

    if(result1 != 0)
    {
        perror("Error crearing a thread.\n");
        exit(-1);
    }
    // sleep(6);
    // printf("Parent thread is exiting now.\n");

    // pthread_exit(0);   // Makes main thread exit without stopping the child threads. Otherwise, sleep(6); instruction has to be used to wait for child thread to
                          // finish its execution.
    result2 = pthread_join(tid,&returnValue);   // This is a blocked call, which means main thread is blocked until the child thread completes it's execution.
    printf("Parent thread is exiting now with the return value from thread: <%s>.\n",(char*)returnValue);
     
    return 0;
}