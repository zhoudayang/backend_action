#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <iostream>

using namespace std;

int main() {
  int connfd;
  int len = 0;
  struct sockaddr_in client;
  client.sin_family = AF_INET;
  client.sin_port = htons(6666);
  client.sin_addr.s_addr = inet_addr("127.0.0.1");
  connfd = socket(AF_INET, SOCK_STREAM, 0);
  if (connfd < 0) {
    cout << "socket error" << endl;
    return 0;
  }
  if (connect(connfd, (struct sockaddr *) &client, sizeof(client)) < 0) {
    cout << "connect error" << endl;
    return 0;
  }
  char buffer[1024];
  bzero(buffer, sizeof(buffer));
  recv(connfd, buffer, 1024, 0);
  cout << "recv: " << buffer << endl;
  bzero(buffer, sizeof(buffer));
  strcpy(buffer, "this is an client!\n");
  send(connfd, buffer, 1024, 0);
  while (1) {
    bzero(buffer, sizeof(buffer));
    scanf("%s",buffer);
    int p = strlen(buffer);
    buffer[p] = '\0';
    send(connfd, buffer, 1024, 0);
    cout << "I have send buffer " << buffer << endl;
  }
  close(connfd);
  return 0;
}