#include <stdio.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <semaphore.h> 
#include <unistd.h> 

int main()
{
    int semval;
    unsigned int value;
    sem_t *sem;

    sem = sem_open("/semdummy",O_CREAT | O_RDWR,0660,2);

    if (sem == SEM_FAILED){
        perror("sem_open error");
        return -1;
    }else{
        printf("\n sem_open success\n");
    }

   sem_getvalue(sem , &semval );
   printf("\n before sem_wait semaphore value = (%d)\n",semval);

   sem_wait(sem); //wait state 
   sem_getvalue(sem , &semval );
   printf("\n after sem_wait semaphore value = (%d)\n",semval);


    printf("\nprocess 1: Executing Critical section\n");
    sleep(9);
    sem_post(sem);
    printf("\n critical section executed\n");
    sem_getvalue(sem , &semval );
    printf("\n after  sem_post semaphore value = (%d)\n",semval);

    //sem_unlink("/semdummy");
}
