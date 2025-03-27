#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    printf("I'm the process replacing Child process and my arguments are below: \n");
    for(int i=0; i<argc; i++)
    {
        printf("<%s>\n",argv[i]);
    }   
    return 5;
}