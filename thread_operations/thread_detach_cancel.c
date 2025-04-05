#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void* run_loop(void *ch)
{
    char* arg = (char*)ch;
    printf("I'm in the thread now with argument <%s> and pid: %d.\n\n",arg,getpid());
    pthread_detach(pthread_self());
    for(int i = 1; i<=5; i++)
    {
        printf("The loop is running at count: %d\n",i);
        sleep(1);
    }
    printf("\nI'm exiting the thread now.\n");
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
    printf("Parent thread is exiting now.\n");
    // pthread_cancel(tid);  //Used to intentionally terminate a thread. 
    pthread_exit(0);
     
    // return 0;
}