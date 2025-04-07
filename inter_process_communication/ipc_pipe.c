#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    int fd[2], wvalue, rvalue, loop, flag = 1, status;

    if(pipe(fd)==-1)
    {
        perror("PIPE creation error.");
        exit(-1);
    }

    switch(fork())
    {
        case -1:
            perror("Process cannot be forked.");
            exit(-1);
        case 0:
           printf("PID of Child process is: %d\n",getpid());
           close(fd[1]);
           while(1)
           {
                loop = read(fd[0],&rvalue,sizeof(rvalue));
                if(loop == 0)
                {
                    printf("Child process read 0 from the PIPE and closing PIPE connection.\n");
                    if(close(fd[0])==-1)
                    {
                        perror("Read end of PIPE cannot be closed.");
                        exit(-1);
                    }
                    break;
                }
                else if(loop > 0)
                   printf("Child process read %d from the PIPE.\n",rvalue);
                else if(loop == -1)
                {
                    perror("Read error in the child process.");
                    exit(-1);
                }
           }
           printf("Child process terminating.\n");
           break;
        default:
           printf("PID of Parent process is: %d\n",getpid());
           close(fd[0]);
           while(flag == 1)
           {
                printf("Please provide an integer to send to the child process:\n");
                scanf("%d",&wvalue);
                write(fd[1],&wvalue,sizeof(wvalue));
                sleep(1);
                printf("Do you want to continue sending integers to the child process? 1 for YES & 0 for NO\n");
                scanf("%d",&flag);
                if(flag==0)
                   break;
           }
           printf("Parent process closing the PIPE connection and terminating.\n");
           if(close(fd[1])==-1)
           {
               perror("Write end of PIPE cannot be closed.");
               exit(-1);
           }
           wait(&status);
           break;
    }
       
    return 0;
}