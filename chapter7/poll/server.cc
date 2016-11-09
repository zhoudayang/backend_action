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
#include <stdint.h>

using namespace std;

int bind_and_listen() {
  int serverfd;
  struct sockaddr_in my_addr;
  if ((serverfd = socket(AF_INET, SOCK_STREAM, 0))==-1) {
    cout << "socket error" << endl;
    return -1;
  }
  cout << "create socket ok" << endl;
  memset(&my_addr, 0, sizeof(my_addr));
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(6666);
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(serverfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr))==-1) {
    cout << "bind error" << endl;
    return -1;
  }
  cout << "bind ok" << endl;
  if (listen(serverfd, 10)==-1) {
    cout << "listen error" << endl;
    return -1;
  }
  cout << "listen ok " << endl;
  return serverfd;
}

int main() {
  int server_fd = bind_and_listen();
  if(server_fd == -1){
    cout<<"create or bind or listen error"<<endl;
    return -1;
  }
  int connfd;
  struct sockaddr_in cliaddr;
  vector<pollfd> fds;
  pollfd ser_fd;
  ser_fd.fd = server_fd;
  //cares read event of server
  ser_fd.events = POLLIN;
  fds.push_back(ser_fd);
  while (true) {
    //ready : active fd num
    int ready = poll(&*fds.begin(), fds.size(), INFTIM);
    if (ready == -1) {
      cout << "poll error " << endl;
      exit(-1);
    }
    if (fds[0].revents & POLLIN) {
      socklen_t len = sizeof(cliaddr);
      if ((connfd = accept(server_fd, (struct sockaddr *) &cliaddr, &len))==-1) {
        if (errno==EINTR) {
          continue;
        } else {
          cout << "accept error" << endl;
          exit(-1);
        }
      }
      cout << "accept a new client!" << inet_ntoa(cliaddr.sin_addr) << " : " << cliaddr.sin_port << endl;
      //add a new client
      pollfd cli_fd;
      cli_fd.fd = connfd;
      cli_fd.events = POLLIN;
      fds.push_back(cli_fd);
      if (--ready==0) {
        continue;
      }
    }
    auto it = fds.begin();
    ++it;
    for (; it!=fds.end();) {
      auto &fd = *it;
      if (fd.revents & POLLIN) {
        char buf[1024];
        memset(buf,0,1024);
        int readlen = read(fd.fd, buf, 1024);
        //peer close the connection
        if (readlen==0) {
          close(fd.fd);
          it = fds.erase(it);
          continue;
        }
        cout << "read msg is :" << buf << endl;
        //write same content to client
        write(fd.fd, buf, readlen);
        if (--ready==0) {
          break;
        }
      }
      ++it;
    }
  }
}




