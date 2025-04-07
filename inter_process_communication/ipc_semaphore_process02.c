#include <stdio.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <semaphore.h> 
#include <unistd.h> 

int main()
{
    int ret, semval;
    sem_t *sem;

    sem = sem_open("/semdummy",O_RDWR);

    if (sem == SEM_FAILED){
        perror("sem_open error");
        return -1;
    }else{
        printf("\n sem_open success\n");
    }

   sem_getvalue(sem , &semval );
   printf("\n semaphore val = (%d)\n",semval);

    ret = sem_wait(sem); //wait state 
    printf("\nProcess 2 executing critical section\n");
    sleep(5);
    printf("\n ret is (%d)\n",ret);
    printf("\nprocess 2:\n");
    sem_post(sem);

    printf("\nProcess 2 executed critical section\n");
    //sem_unlink("/sem1");

}
