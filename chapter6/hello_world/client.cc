#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char **argv){
  int sockfd;
  char sendline[4096];
  struct sockaddr_in servaddr;
  char * ip = "127.0.0.1";
  short port = 6666;
  if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0){
    printf("create socket error: %s(errno:%d)\n",strerror(errno),errno);
    return 0;
  }

  memset(&servaddr,0,sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(port);
  if(inet_pton(AF_INET,ip,&servaddr.sin_addr)<=0){
    printf("inet_pton error for %s\n",ip);
    return 0;
  }

  if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0){
    printf("connect error:%s (errno:%d)\n",strerror(errno),errno);
    return 0;
  }

  printf("send msg to server : \n");
  fgets(sendline,4096,stdin);
  if(send(sockfd,sendline,strlen(sendline),0)<0){
    printf("send error :%s (errno :%d)\n",strerror(errno),errno);
    return 0;
  }
  close(sockfd);
  return 0;

}
