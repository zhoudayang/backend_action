#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include<sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(){
  char * buf = "this is a Daemon\n";
  int len = strlen(buf);
  pid_t pid = fork();
  if(pid<0){
    perror("fork error!\n");
    exit(1);
  }
  else if(pid > 0){
    //parent process exit
    exit(0);
  }

  setsid();
  chdir("/");
  umask(0);
  const static int MAX_FILE = 65535;
  for(int i = 0;i<MAX_FILE;++i)
    close(i);

  while(true){
    int fd ;
    if((fd = open("/tmp/daemon.log",O_CREAT|O_WRONLY|O_APPEND,0600))<0){
      perror("open");
      exit(-1);
    }
    write(fd,buf,len);
    close(fd);
    sleep(10);
  }

}