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
#include <unordered_map>

#include <iostream>
using namespace std;

int socket_bind() {
  int listenfd;
  struct sockaddr_in servaddr;
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenfd == -1) {
    cout << "socket error " << endl;
    exit(-1);
  }
  cout<<"socket ok"<<endl;
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(6666);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1) {
    cout<<"bind error"<<endl;
    exit(-1);
  }
  cout<<"bind ok"<<endl;
  if(listen(listenfd,10)==-1)
  {
    cout<<"listen error"<<endl;
    exit(-1);
  }
  cout<<"listen fd"<<endl;
  return listenfd;
}

void add_event(int epollfd,int fd,int state){
  struct epoll_event ev;
  ev.events = state;
  ev.data.fd = fd;
  epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&ev);
}

void delete_event(int epollfd,int fd,int state){
  struct epoll_event ev;
  ev.events = state;
  ev.data.fd = fd;
  epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,&ev);

}

void modify_event(int epollfd,int fd,int state){
  struct epoll_event ev;
  ev.events = state;
  ev.data.fd = fd;
  epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&ev);
}

void do_epoll(int listenfd){
  vector<epoll_event> fds(100);
  const int epollfd = epoll_create(100);
  add_event(epollfd,listenfd,EPOLLIN);
  //保存fd和buf之间的对应关系
  unordered_map<int,char *> buffers;
  while(1){
    fds.clear();
    fds.resize(100);
    int result = epoll_wait(epollfd,fds.data(),fds.size(),-1);
    if(result >= fds.size()){
      fds.resize(fds.size()*2);
    }
    cout<<"epoll return size:"<<result<<endl;
    for(int i =0;i<result;++i){
      epoll_event ev = fds[i];
      const int fd = ev.data.fd;
      if((fd == listenfd)&&(ev.events & EPOLLIN)){
        struct sockaddr_in cliaddr;
        socklen_t len = sizeof(cliaddr);
        int clifd = accept(listenfd,(struct sockaddr *)&cliaddr,&len);
        if(clifd == -1){
          cout<<"accpet error"<<endl;
          exit(-1);
        }
        else{
          cout<<"accpet a client "<<inet_ntoa(cliaddr.sin_addr)<<" : "<<cliaddr.sin_port<<" the file descriptor is "<<clifd<<endl;
          //add event for read for new client file descriptor
          add_event(epollfd,clifd,EPOLLIN);
        }
      }
      else if(ev.events & EPOLLIN){
        char * buf = new char [1024];
        memset(buf,0,1024);
        int n = read(fd,buf,1024);
        if(n==-1){
          cout<<"read error "<<endl;
          close(fd);
          delete_event(epollfd,fd,EPOLLIN);
        }
        else{
          cout<<"read message:"<<buf<<endl;
          modify_event(epollfd,fd,EPOLLOUT);
          buffers[fd] = buf;
        }
      }
      else if(ev.events & EPOLLOUT){
        char * buf = buffers[fd];
        int n = write(fd,buf,strlen(buf));
        if(n == -1){
          cout<<"write error "<<endl;
          close(fd);
          delete_event(epollfd,fd,EPOLLOUT);
        }
        else{
          modify_event(epollfd,fd,EPOLLIN);
          buffers.erase(fd);
          delete buf;
        }
      }
    }
  }
  close(epollfd);
}

int main() {
  int listenfd;
  struct sockaddr_in servaddr;
  listenfd = socket_bind();
  do_epoll(listenfd);
  return 0;
}