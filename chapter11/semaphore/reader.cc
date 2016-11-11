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


#define SEM_KEY 4001
#define SHM_KEY 5678
int main(){
  int semid,shmid;
  shmid = shmget(SHM_KEY,sizeof(int),IPC_CREAT|0666);
  if(shmid<0){
    printf("create shm error!\n");
    return -1;
  }

  void *shm_ptr = shmat(shmid,NULL,0);
  if(shm_ptr == (void *) -1){
    printf("shmat error:%s\n",strerror(errno));
    return -1;
  }

  int * data = (int *)shm_ptr;
  //创建一个semid，有两个信号量
  semid = semget(SEM_KEY,2,IPC_CREAT|0666);
  //初始化这两个信号量

  //set first semaphore init to zero
  semctl(semid,0,SETVAL,0);

  //set second semaphore init to 1
  semctl(semid,1,SETVAL,1);

  struct sembuf sembuf1;

  while(true){
    //descrease first semaphore by one
    sembuf1.sem_num = 0;
    sembuf1.sem_op = -1;
    sembuf1.sem_flg = SEM_UNDO;
    semop(semid,&sembuf1,1);//reader will block until receive signal

    printf("the NUM:%d\n",*data);

    //increase second semaphore by one
    sembuf1.sem_num = 1; // let reader ready again
    sembuf1.sem_op = 1;
    sembuf1.sem_flg = SEM_UNDO;

    semop(semid,&sembuf1,1);
  }
  return 0;

}