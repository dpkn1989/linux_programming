#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int fd;
    char* myfifo = "/tmp/myfifo";
    char data[90];

    fd = open(myfifo,O_RDONLY);

    while(1)
    {
        read(fd,data,90);
        printf("The data read from FIFO is: %s\n",data);
    }
    close(fd);
    return 0;
}