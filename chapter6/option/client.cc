#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

using namespace std;

#define MAXLINE 4096

int main() {
  int connfd, n;
  char recvline[4096], sendline[4096];
  struct sockaddr_in servaddr;
  if ((connfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("create socket error: %s : %d \n", strerror(errno), errno);
    return 0;
  }
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(6666);
  if (inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0) {
    printf("inet_pton error:%s,%d\n", strerror(errno), errno);
    return 0;
  }
  if (connect(connfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
    printf("connect error:%s : %d \n", strerror(errno), errno);
    return 0;
  }

  //set timeout

  struct timeval stTimeValStruct;
  stTimeValStruct.tv_sec = 2;
  stTimeValStruct.tv_usec = 0;
  if (setsockopt(connfd, SOL_SOCKET, SO_SNDTIMEO, &stTimeValStruct, sizeof(stTimeValStruct))) {
    printf("setsockopt error: %s: %d\n", strerror(errno), errno);
    return 0;
  }
  //set recv timeout
  if (setsockopt(connfd, SOL_SOCKET, SO_RCVTIMEO, &stTimeValStruct, sizeof(stTimeValStruct))) {
    printf("setsockopt error: %s :%d \n", strerror(errno), errno);
    return 0;
  }
  ssize_t writeLen;
  char sendMsg[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '\0'};
  int count = 0;
  writeLen = write(connfd, sendMsg, sizeof(sendMsg));
  if (writeLen < 0) {
    printf("write error: %s:%d\n", strerror(errno), errno);
    close(connfd);
    return 0;
  }
  else {
    cout << "write sucess,writeLen : " << writeLen << "sendMsg :" << sendMsg << endl;
  }
  char readMsg[10] = {0};
  int readLen = read(connfd, readMsg, sizeof(readMsg));
  if (readLen < 0) {
    printf("read error: %s:%d\n", strerror(errno), errno);
    close(connfd);
    return 0;
  }
  else {
    readMsg[9] = '\0';
    printf("read success: %d, readMsg: %s\n", readLen, readMsg);
  }
  close(connfd);
  return 0;
}