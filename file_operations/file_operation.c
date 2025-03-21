#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    int fd,fdc, continueWrite = 1, offset = 0;
    ssize_t sizeread = 0, sizewrite = 0;
    char buffread[30] = {0}, buffwrite[9] = {0};
    fd = open("file01.txt",O_RDONLY);
    if(fd == -1)
    {
        printf("File cannot be opened due to error: %d\n", errno);
        perror("ERROR:");
    }
    else
    {
        printf("The file is opened successfully with fd id: %d\n", fd);
    }
    
    while((sizeread = read(fd,buffread,sizeof(buffread)-1)) > 0)
    {
        buffread[sizeread] = '\0';
        printf("Read following data from the file: <%s>\n", buffread);
    }
    
    if(sizeread == 0)
    {
        printf("The file is completely read and nothing more to read.\n");
    }
    else if(sizeread == -1)
    {
        printf("Error reading file due to %d\n", errno);
        perror("ERROR:");
    }


    fdc = open("file02.txt",O_CREAT|O_RDWR|O_APPEND,0731);
    if(fdc == -1)
    {
        printf("File cannot be created/opened due to error: %d\n", errno);
        perror("ERROR:");
    }
    else
    {
        printf("The file is created and opened successfully with fd id: %d\n", fdc);
    }

    printf("Start writing data into the file.\n");
    while(continueWrite)
    {
        printf("Enter a data of size %ld characters: ",sizeof(buffwrite));
        fgets(buffwrite,sizeof(buffwrite),stdin);
        sizewrite = write(fdc,buffwrite,strlen(buffwrite));
        if(sizewrite > 0)
        {
            printf("Data of size %ld bytes written succefssfully to the file.\n", sizewrite);
            printf("Do you want to continue writing? Enter 0 to STOP or 1 to CONTINUE\n");
            scanf("%d", &continueWrite);
            getchar();
        }
        else if(sizewrite == -1)
        {
            printf("Writing to the file failed due to error: %d\n", errno);
            perror("ERROR:");
        }
    }

    offset = lseek(fdc,0,SEEK_END);
    strcpy(buffwrite,"Ganesha!");
    sizewrite = write(fdc,buffwrite,strlen(buffwrite));

    close(fd);
    close(fdc);
       
    return 0;
}
