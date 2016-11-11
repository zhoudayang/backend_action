#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/shm.h>

#include "shared_data.h"

int main() {

  srand((unsigned int) getpid());
  //create shared_memory with size of shared_data if not exist
  int sh_mid = shmget((key_t)1234,sizeof(struct shared_data),0666|IPC_CREAT);
  //create error
  if(sh_mid == -1){
    fprintf(stderr,"shmget failed!\n");
    exit(-1);
  }
  void * shared_memory = (void *)0;
  //将共享内存映射到进程的地址空间之中
  /* Attach shared memory segment.  */
  shared_memory = shmat(sh_mid,(void*)0,0);
  if(shared_memory == (void *) -1 ){
    fprintf(stderr,"shamat failed!\n");
    exit(-1);
  }
  printf("memory attached at %p\n",shared_memory);
  struct shared_data * shared_stuff;
  shared_stuff = (struct shared_data *) shared_memory;
  shared_stuff->written = 0;
  while(true){
    if(shared_stuff->written){
      printf("you wrote : %s\n",shared_stuff->text);
      sleep(rand()%4);
      shared_stuff ->written = 0;
      //end to exit
      if(strncmp(shared_stuff->text,"end",3) == 0){
        break;
      }
    }

  }
  // 分离共享内存
  if(shmdt(shared_memory) == -1){
    fprintf(stderr,"shmdt failed!\n");
    exit(-1);
  }
  //删除共享内存
  if(shmctl(sh_mid,IPC_RMID,0) == -1){
    fprintf(stderr,"shmctl(IPC_RMID) failed\n");
    exit(-1);
  }

  exit(0);


}