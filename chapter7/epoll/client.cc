#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/types.h>
#include <vector>

#include <iostream>
using namespace std;

int main() {
  int sockfd;
  struct sockaddr_in servaddr;
  sockfd = socket(AF_INET,SOCK_STREAM,0);
  memset(&servaddr,0,sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(6666);
  inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr);
  if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) == -1){
    cout<<"connect error!"<<endl;
    exit(-1);
  }
  while(true){
    char buf[1024];
    memset(buf,0,1024);
    scanf("%s",buf);
    write(sockfd,buf,1024);
    memset(buf,0,1024);
    int ret = read(sockfd,buf,1024);
    if(ret == 0){
      close(sockfd);
      return -1;
    }
    else if(ret <0){
      close(sockfd);
      cout<<"read error!"<<endl;
      return -1;
    }
    else{
      buf[ret] = '\0';
      cout<<"read "<<buf<<endl;
    }
  }
  return 0;
}
