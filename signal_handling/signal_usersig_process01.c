#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

void Signal_Handler(int signal_number)
{
    if(signal_number == SIGUSR1)
    {
        printf("Parent process received SIGUSR1\n");
    }
}

int main(void)
{
    pid_t cpid;
    int status;

    printf("The pid of Parent process is: %d\n", getpid());
    cpid = fork();

    if(cpid == -1)
    {
        printf("Parent process cannot fork a child process due to %d.\n", errno);
        perror("ERROR: ");
        return -1;
    }
    if(cpid == 0)
    {
        printf("Execution of child process with pid:%d started.\n",getpid());
        execl("signal_process02","arg1","arg2","arg3",NULL);
        printf("This line from child process will not be printed.\n");
    }
    else
    {
        signal(SIGUSR1,Signal_Handler);
        sleep(9);
        printf("Parent process sending SIGUSR2 to child process.\n");
        kill(cpid,SIGUSR2);
        wait(&status);
        printf("Parent process about to terminate and its child process with pid:%d exited with status:%d.\n", cpid,status);
    }
    
    return 0;
}