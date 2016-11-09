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
void handle_connection(int sockfd){


  
}




int main() {
  int sockfd;
  struct sockaddr_in servaddr;
  sockfd = socket(AF_INET,SOCK_STREAM,0);
  memset(&servaddr,0,sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(6666);
  inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr);
  handle_connection(sockfd);
  close(sockfd);
  return 0;
}
