#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <errno.h>
#include <poll.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <unp.h>

using namespace std;

int main() {
  int connfd = 0;
  struct sockaddr_in client;
  client.sin_family = AF_INET;
  client.sin_port = htons(6666);
  client.sin_addr.s_addr = inet_addr("127.0.0.1");
  connfd = socket(AF_INET, SOCK_STREAM, 0);
  if (connfd < 0) {
    cout << "create socket error " << strerror(errno)<<endl;
    return -1;
  }
  if (connect(connfd, (struct sockaddr *) &client, sizeof(client)) < 0) {
    cout << "connect error " <<strerror(errno)<< endl;;
    return -1;
  }
  struct pollfd fds[2];
  fds[0].fd = connfd;
  fds[0].events = POLLIN;
  fds[1].fd = STDIN_FILENO;
  fds[1].events = POLLIN;
  while (true) {
    poll(fds,2,-1);
    if(fds[0].revents &POLLIN){
      char buf [1024];
      int n = read(fds[0].fd,buf,1024);
      if(n == 0){
        cout<<"server close the connection!"<<endl;
        close(connfd);
        break;
      }
      write(STDOUT_FILENO,buf,n);
    }
    if(fds[1].revents &POLLIN){
      char buf [1024];
      int n = read(fds[1].fd,buf,1024);
      if(n == 0){
        shutdown(connfd,SHUT_WR);
        continue;
      }
      write(connfd,buf,n);
    }
  }

  return 0;
}