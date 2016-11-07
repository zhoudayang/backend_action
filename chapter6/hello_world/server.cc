#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAX_LINE 4096
int main(){

  int listenfd,connfd;
  struct sockaddr_in serveraddr;
  char buf[MAX_LINE];
  int n;

  if((listenfd = socket(AF_INET,SOCK_STREAM,0)) == -1){
    printf("create socket error : %s(errno:%d)\n)",strerror(errno),errno);
    return 0;
  }

  memset(&serveraddr,0,sizeof (sockaddr_in));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(6666);
  if(bind(listenfd,(struct sockaddr *) & serveraddr,sizeof(serveraddr))==-1){
    printf("bind socket error:%s(errno:%d)\n",strerror(errno),errno);
    return 0;
  }
  if(listen(listenfd,10)==-1){
    printf("listen socker error: %s ))errno: %d)\n",strerror(errno),errno);
  }
  printf("---waiting for client's request --- \n");
  while(true){
    if((connfd = accept(listenfd,(struct sockaddr *)NULL,NULL))==-1){
      printf("accept socket error:%s(errno :%d)",strerror(errno),errno);
      continue;
    }
    n = recv(connfd,buf,MAX_LINE,0);
    buf[n] = '\0';
    printf("recv msg from client: %s",buf);
    close(connfd);
  }
  return 0;
}
