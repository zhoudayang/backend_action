#include <string.h>
#include <sys/shm.h>
#include <errno.h>
#include <cstdio>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/sem.h>
union sem{
  int val;
};

#define SEM_KEY 4001
#define SHM_KEY 5678

int main(){
  int semid,shmid;
  shmid = shmget(SHM_KEY,sizeof(int),IPC_CREAT|0666);
  if(shmid <0 ){
    printf("create shm error!\n");
    return -1;
  }
  void *shmptr = shmat(shmid,NULL,0);
  if(shmptr == (void *)-1){
    printf("shmat error:%s\n",strerror(errno));
    return -1;
  }
  int * data = (int *) shmptr;
  semid = semget(SEM_KEY,2,0666);
  struct sembuf sembuf1;
  //union sem num;
  while(true){
    //decrease second semaphore by 1
    sembuf1.sem_num = 1;
    sembuf1.sem_op = -1;
    sembuf1.sem_flg = SEM_UNDO;
    semop(semid,&sembuf1,1);

    scanf("%d",data);

    //increase first semaphore by 1
    sembuf1.sem_num = 0;
    sembuf1.sem_op =1 ;
    sembuf1.sem_flg = SEM_UNDO;
    semop(semid,&sembuf1,1);
  }
  return 0;
}