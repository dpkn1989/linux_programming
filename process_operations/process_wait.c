#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
    pid_t child1pid, child2pid;
    int status1, status2;

    child1pid = fork();

    if(child1pid == -1)
    {
        printf("PARENT: Child1 cannot be created. Fork failed.\n");
        exit(-1);
    }
    if(child1pid > 0)
    {
        printf("PARENT: Child1 process is created, but I'm in Parent process now with pid: %d.\n", getpid());
        printf("PARENT: Creating another child process.\n");

        child2pid = fork();
        if(child2pid == -1)
        {
            printf("PARENT: Child2 cannot be created. Fork failed.\n");
            exit(-1);
        }
        if(child2pid > 0)
        {
            printf("PARENT: Child2 process is created, but I'm in Parent process now.\n");
            wait(&status2);
            // waitpid(child2pid,&status2,WNOHANG);
            printf("PARENT: Child2 exited with status: %d\n", status2);
        }
        else if(child2pid == 0)
        {
            printf("CHILD2: I am Child2 process and my pid is %d.\n", getpid());
            sleep(6);
            printf("CHILD2: Process execution done.\n");
            exit(6);
        }

        wait(&status1);
        // waitpid(child2pid,&status2,WNOHANG);
        printf("PARENT: Child1 exited with status: %d\n", status1);
    }
    else if(child1pid == 0)
    {
        printf("CHILD1: I am Child1 process and my pid is %d.\n", getpid());
        sleep(9);
        printf("CHILD1: Process execution done.\n");
        exit(5);
    }
    
    return 0;
}