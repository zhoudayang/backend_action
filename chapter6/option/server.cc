#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
  int listenfd;
  struct sockaddr_in servaddr;
  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    printf("create error!\n");
    return 0;
  }
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(6666);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1) {
    printf("bind error! error: %s, %d\n",strerror(errno),errno);
    return 0;
  }
  if (listen(listenfd, 10) == -1) {
    printf("listen socket error!\n");
    return -1;
  }
  printf("-----wait for client's request! \n");
  int acceptfd;
  if ((acceptfd = accept(listenfd, (struct sockaddr *) NULL, NULL)) == -1) {
    printf("accept error!\n");
    return -1;
  }
  char recvMsg[110];
  ssize_t readLen = read(acceptfd, recvMsg, sizeof(recvMsg));
  if (readLen < 0) {
    printf("read error !\n");
    return -1;
  }
  recvMsg[9] = '\0';
  printf("readLen :%d, readMsg: %s\n", readLen, recvMsg);
  //sleep here for 5 seconds, but set recv timeout to 2 seconds, so client read error, resource temporarily
  sleep(5);
  recvMsg[0] = '9';
  ssize_t writeLen = write(acceptfd, recvMsg, sizeof(recvMsg));
  printf("writeLen :%d, writeMsg : %s \n", writeLen, recvMsg);
  if (writeLen < 0) {
    printf("writeLen error!\n");
    return -1;
  }
  close(acceptfd);
  return 0;
}