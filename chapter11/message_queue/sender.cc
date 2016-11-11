#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>

//self-defined basic message type
struct msg_st{
  long int msg_type;
  char text[BUFSIZ];
};

int main(){
  struct msg_st data;
  char buffer[BUFSIZ];
  int msgid = -1;
  ///IPC_CREAT: Create key if key does not exist.
  //create message queue with key 1234 msgid = msgget((key_t)1234,0666|IPC_CREAT);
  if(msgid == -1){
    fprintf(stderr,"msgget failed with errno: %d\n",errno);
    exit(-1);
  }
  while(true){
    printf("enter the text!\n");
    fgets(buffer,BUFSIZ,stdin);
    data.msg_type = 1;
    strcpy(data.text,buffer);
    //send data into message queue
    ///set msg_flg to zero block when message queue is full
    ///msg_flag is the last parameter of msgsnd function
    if(msgsnd(msgid,(void *) &data,BUFSIZ,0 )== -1){
      fprintf(stderr,"msgsnd failed \n");
      exit(-1);
    }
    if(strncmp(buffer,"end",3) == 0){
      break;
    }
    sleep(1);
  }
  exit(0);

}