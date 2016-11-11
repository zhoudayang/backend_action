#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){

  const int input = 0;
  const int output = 1;
  int fd [2];
  //创建无名管道
  pipe(fd);
  pid_t pid = fork();
  if(pid < 0){
    printf("error when fork\n");
    exit(-1);
  }
  else if (pid == 0){
    printf("in child process ...\n");
    close(fd[input]);
    write(fd[output],"hello world",strlen("hello world"));
    exit(0);
  }
  else{
    printf("in the parent process!\n");
    close(fd[output]);
    char buf [1024];
    memset(buf,0,1024);
    int result = read(fd[input],buf,sizeof(buf));
    printf("%d bytes of data received from child process: %s\n",result,buf);
  }
  return 0;

}