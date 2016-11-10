#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){
  pid_t pid = fork();
  if(pid <0){
    printf("error occurred on forking!\n");
  }
  else if(pid == 0){
    printf("sub process %d will sleep for 5 seconds!\n",getpid());
    sleep(5);
    exit(0);
  }
  else if(pid > 0){
    pid_t pr;
    do{
      //child process not complete, don't block
      pr = waitpid(pid,NULL,WNOHANG);
      if(pr == 0){
        printf("no child exited!\n");
        sleep(1);
      }
    }while(pr==0);
    if(pr == pid){
      printf("successfully get child %d\n",pid);
    }
    else
      printf("some error occurred!\n");
  }
  return 0;
}