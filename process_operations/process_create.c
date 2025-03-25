#include <stdio.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
    pid_t childpid;
    int var = 54;

    childpid = fork();
    switch(childpid)
    {
        case -1:
            printf("A child process cannot be forked.\n");
            break;
        
        case 0:
            printf("I am child process and my pid is %d.\n", getpid());
            printf("The pid of my parent is %d.\n", getppid());
            printf("The value of var in child process is %d.\n",var*2);
            break;
        
        default:
            printf("I am parent process and my pid is %d.\n", getpid());
            printf("The value of var in parent process is %d.\n",var);
    }

    return 0;
}