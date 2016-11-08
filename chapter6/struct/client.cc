#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <iostream>

#include "util.h"

using namespace std;

int main(){
  int connfd;
  struct sockaddr_in client;
  client.sin_family = AF_INET;
  client.sin_port = htons(6666);
  client.sin_addr.s_addr = inet_addr("127.0.0.1");
  connfd = socket(AF_INET,SOCK_STREAM,0);
  if(connfd<0){
    cout<<"create socket error"<<endl;
  }
  if(connect(connfd,(struct sockaddr *)& client,sizeof(client))<0){
    cout<<"connect error "<<endl;
    return -1;
  }
  pkg  pkg;
  pkg.num = 28;
  int length = sizeof(pkg);
  cout<<"len:"<<length<<endl;
  int ilen = 0;
  char * buff = new char [1000];
  *(int *) (buff +ilen) = htonl(length);
  ilen += sizeof(int);
  *(int*) (buff+ilen) = htonl(pkg.num);
  ilen+=sizeof(int);
  int writeLen = Send(connfd,buff,ilen);
  if(writeLen <0){
    cout<<"write error "<<endl;
    close(connfd);
    return 0;
  }
  else if(writeLen == ilen){
    cout<<"write success! writelen :"<<ilen<<endl;
  }

  close(connfd);
  return 0;
}