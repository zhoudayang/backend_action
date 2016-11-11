#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int serverfd, acceptfd;
  struct sockaddr_in my_addr;
  struct sockaddr_in peer_addr;
  //create socket
  if ((serverfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    cout << "create error" << endl;
    return -1;
  }
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(6666);
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  //bind socket
  if (bind(serverfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) == -1) {
    cout << "bind error" << endl;
    return -1;
  }
  cout << "bind ok" << endl;
  //begin to listen
  if (listen(serverfd, 10) == -1) {
    cout << "listen error" << endl;
    return -1;
  }
  cout << "listen ok" << endl;
  fd_set client_fdset;
  memset(&client_fdset, 0, sizeof(fd_set));
  vector<int> fds;

  while (1) {
    FD_ZERO(&client_fdset);
    FD_SET(serverfd, &client_fdset);
    int maxfd = serverfd;
    for (auto fd:fds) {
      FD_SET(fd, &client_fdset);
      maxfd = max(maxfd, fd);
    }
    timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    //only care listen event
    int ret = select(maxfd + 1, &client_fdset, NULL, NULL, &tv);
    if (ret < 0) {
      cout << "select errot";
      break;
    }
    if (ret == 0) {
      cout << "time out " << endl;
      continue;
    }
    for (auto it = fds.begin(); it != fds.end();) {
      auto fd = *it;
      if (FD_ISSET(fd, &client_fdset)) {
        cout << "start recv from client " << fd << endl;
        char buffer[1024];
        memset(buffer, 0, 1024);
        int result = recv(fd, buffer, 1024, 0);
        if (result <= 0) {
          cout << "client close " << fd << endl;
          close(fd);
          FD_CLR(fd, &client_fdset);
          it = fds.erase(it);
          continue;
        }
        else if (result > 0) {
          buffer[result] = '\0';
          cout << "recv from client: " << buffer << endl;
        }
      }
      ++it;
    }
    if (FD_ISSET(serverfd, &client_fdset)) {
      struct sockaddr_in client_addr;
      size_t size = sizeof(sockaddr_in);
      int sock_client = accept(serverfd, (struct sockaddr *) &client_addr, (unsigned int *) &size);
      if (sock_client < 0) {
        cout << "accept error" << endl;
        continue;
      }
      fds.push_back(sock_client);
      char buffer[1024] = {0};
      strcpy(buffer, "this is server ! welcome!\n");
      send(sock_client, buffer, 1024, 0);
      cout << "new connection build: " << sock_client << " " << inet_ntoa(client_addr.sin_addr) << " "
          << ntohs(client_addr.sin_port) << endl;
      memset(buffer, 0, 1024);
      int result = recv(sock_client, buffer, 1024, 0);
      if (result <= 0) {
        cout << "recv error" << endl;
        close(serverfd);
        return -1;
      }
      cout << "recv: " << buffer << endl;
    }
  }
  return 0;
}