#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <sys/msg.h>

struct msg_st{
  long int msg_type;
  char text[BUFSIZ];
};

int main(){
  int msgid = -1;
  struct msg_st data;
  long int msg_type = 0;
  ///IPC_CREAT: Create key if key does not exist.
  //create message queue with key 1234
  msgid = msgget((key_t)1234,0666|IPC_CREAT);
  if(msgid == -1){
    fprintf(stderr,"msgget failed with error : %d\n",errno);
    exit(-1);
  }

  while(true){
    //read data from message queue
    ///set msg_flg to zero block when message queue is empty
    ///msg_flag is the last parameter of msgrcv function
    if(msgrcv(msgid,(void *)&data,BUFSIZ,msg_type,0)==-1){
      fprintf(stderr,"msgrcv failed with errno: %d\n",errno);
      exit(-1);
    }
    printf("you wrote: %s : %d \n",data.text,data.msg_type);
    //end to exit
    if(strncmp(data.text,"end",3) == 0){
      break;
    }
  }
  /* IPC_RMID : Remove identifier.  */
  //delete message queue
  if(msgctl(msgid,IPC_RMID,0) == -1){
    fprintf(stderr,"msgcl (IPC_RMID) failed \n");
    exit(-1);
  }
  exit(0);

}
