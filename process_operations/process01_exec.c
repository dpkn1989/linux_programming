#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    printf("I'm Parent process with pid: %d\n",getpid());
    printf("I'm forking a new process now.\n");
    pid_t chpid = fork();
    int status;

    if(chpid == -1)
    {
        printf("Child process cannot be forked due to error: %d.\n",errno);
        perror("ERROR: ");
        return -1;
    }

    if(chpid == 0)
    {
        printf("I'm in Child process and my pid is: %d.\n",getpid());
        // execl("./process02_exec","arg1","arg2","arg3",NULL);
        char* args[] = {"arg1","arg2","arg3","arg4","arg5",NULL};
        execv("./process02_exec",args);
        printf("This line will not be printed.\n");
    }
    else
    {
        printf("I'm from Parent process again.\n");
        wait(&status);
        printf("The child process I forked with pid <%d> exited with status <%d>.\n",chpid,status);
    }
        
    return 0;
}
