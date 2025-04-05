#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

void Signal_Handler(int signal_number)
{
    if(signal_number == SIGUSR2)
    {
        printf("Child process received SIGUSR2\n");
    }
}

int main(void)
{
    printf("The pid of Child process is: %d\n", getpid());
    signal(SIGUSR2,Signal_Handler);

    int waitTime = 18;
    while(waitTime > 0)
    {
        waitTime = sleep(waitTime);
    }
    
    printf("Child process sending SIGUSR1 to Parent process.\n");
    kill(getppid(),SIGUSR1);
    printf("Child process about to get terminated.\n");
    
    return 5;
}