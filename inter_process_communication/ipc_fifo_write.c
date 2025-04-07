#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int fd;
    char* myfifo = "/tmp/myfifo";
    char data[90];
    mkfifo(myfifo,0660);
    fd = open(myfifo,O_WRONLY);

    while(1)
    {
        printf("Enter a string to send to FIFO: \n");
        fgets(data,90,stdin);
        write(fd,data,strlen(data)+1);
    }
    close(fd);
    return 0;
}