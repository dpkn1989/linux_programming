#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


int main(int argc, char *argv[])
{
    int fd;
    char *addr;
    struct stat len;                          // Struct used to store metadata of shared mem
    fd = shm_open("/shm_1", O_RDONLY, 0);
    if (fd == -1)
    {
        printf("\n shm open error\n");
        return -1;
    }
    fstat(fd, &len);                          // Shared mem info stored to 'len'. len.st_size says how big the shared mem object is
    addr = mmap(NULL, len.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED)
    {
        printf("\n mmap error\n");
        return -1;
    }
    printf("\nRead data from shared memory - (%s)\n",addr);
    exit(0);
}
