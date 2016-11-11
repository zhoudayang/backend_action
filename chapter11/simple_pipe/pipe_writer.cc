
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(){
  const char * path = "/tmp/pipe";
  int fd;
  fd = open(path,O_WRONLY|O_NONBLOCK);
  write(fd,"hello world!",strlen("hello world!"));
  close(fd);
  return 0;
}