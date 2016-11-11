#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>

#include "shared_data.h"

int main(){
  //create shared_memory with size of shared_data if not exist
  int sh_mid = shmget((key_t) 1234,sizeof(struct shared_data),0666|IPC_CREAT);
  //create shaared_memory error
  if(sh_mid == -1){
    fprintf(stderr,"shmget failed!\n");
    exit(-1);
  }
  void * shared_memory = (void *) 0;
  /* Attach shared memory segment.  */
  shared_memory = shmat(sh_mid,(void *)0,0);
  if(shared_memory == (void *) -1){
    fprintf(stderr,"shmget failed!\n");
    exit(-1);
  }
  printf("memory attached at %p\n",shared_memory);
  struct shared_data * shared_stuff;
  shared_stuff = (struct shared_data *) shared_memory;
  char buffer[2048];
  while(true){
    while(shared_stuff->written == 1){
      sleep(1);
      printf("waiting for client ...\n");
    }
    printf("enter some text: \n");
    memset(buffer,0,2048);
    fgets(buffer,2048,stdin);
    strncpy(shared_stuff->text,buffer,2048);
    shared_stuff->written = 1;
    if(strncmp(buffer,"end",3) == 0){
      break;
    }
  }

/* Detach shared memory segment.  */
  if(shmdt(shared_memory) == -1){
    fprintf(stderr,"shmt failed!\n");
    exit(-1);
  }

  exit(0);

}