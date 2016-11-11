#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <zconf.h>
#include <unistd.h>

int main(){
  //有名管道对应的路径
  const char * path = "/tmp/pipe";
  if(access(path,F_OK) == 0){
    execlp("rm","-f",path);
    printf("delete exist path\n");
  }
  if(mkfifo(path,0777)<0){
    printf("create named pipe error!\n");
  }
  int fd = open(path,O_RDONLY|O_NONBLOCK);
  char buf[1024];
  while(true){
    memset(buf,0,1024);
    if(read(fd,buf,1024) == 0){
      printf("no data!\n");
    }
    else{
      printf("get data! : %s \n",buf);
      break;
    }
    sleep(1);
  }
  close(fd);
  return 0;

}