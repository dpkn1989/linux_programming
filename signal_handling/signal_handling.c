#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void Signal_Handler(int signal_number)
{
    if(signal_number == SIGINT)
    {
        printf("Received SIGINT\n");
    }
    else if(signal_number == SIGTERM)
    {
        printf("Received SIGTERM\n");
    }
}

int main(void)
{
    printf("The pid of Parent process is: %d\n", getpid());
    signal(SIGINT,Signal_Handler);
    //signal(SIGTERM,Signal_Handler);
    //signal(SIGTERM,SIG_IGN);
    signal(SIGTERM,SIG_DFL);

    while(1);
    
    return 0;
}