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
using namespace std;

#include "util.h"

int main() {
  int sockfd, acceptfd;
  struct sockaddr_in my_addr;
  struct sockaddr_in peer_addr;
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    cout << "socket " << endl;
    return -1;
  }

  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(6666);
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  bzero(&(my_addr.sin_addr.s_addr), 0);
  if (bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) == -1) {
    cout << "bind" << endl;
    return -1;
  }
  cout << "bind ok" << endl;

  if (listen(sockfd, 10) == -1) {
    cout << "listen" << endl;
    return -1;
  }

  cout << "listen ok " << endl;

  char recvMsg[1000];
  socklen_t size = sizeof(my_addr);
  acceptfd = accept(sockfd, (struct sockaddr *) &my_addr, &size);
  if (acceptfd < 0) {
    close(sockfd);
    cout << "accpet failed " << endl;
    return -1;
  }

  size_t readLen = Recv(acceptfd, recvMsg, sizeof(int));
  if (readLen < 0) {
    cout << "read error" << endl;
    return -1;
  }
  int len = (int) ntohl(*(int *) recvMsg);
  cout << "len: " << len << endl;
  if (len < 0) {
    cout << "read failed " << endl;
    return -1;
  }
  Recv(acceptfd,recvMsg,len);
  char *buf = recvMsg;
  pkg pkg;
  int cur = 0;
  memcpy(&pkg ,buf,len);
  cur += sizeof(int);
  pkg.num = ntohl(pkg.num);
  cout<<"num: "<<pkg.num<<endl;
  close(acceptfd);
  return 0;
}


