#include <stdio.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <semaphore.h> 
#include <unistd.h> 

int main()
{
    int ret, semval;
    unsigned int value;
    sem_t *sem;

    sem = sem_open("/semdummy",  O_RDWR);

    if (sem == SEM_FAILED){
        perror("sem_open error");
        return -1;
    }else{
        printf("\n sem_open success\n");
    }

   sem_getvalue(sem , &semval );
   printf("\n semval = (%d)\n",semval);

    ret = sem_wait(sem); //wait state 
    printf("\n ret is (%d)\n",ret);
    printf("\nprocess 3:terminating\n");
    sem_post(sem);

    //sem_unlink("/sem1");
}
