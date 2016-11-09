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

void add_event(int epollfd,int fd,int state,vector<epoll_event> &fds){
  struct epoll_event ev;
  ev.events = state;
  ev.data.fd = state;
  epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&ev);
  fds.push_back(ev);
}

void delete_event(int epollfd,int fd,int state,vector<epoll_event> &fds){
  struct epoll_event ev;
  ev.events = state;
  ev.data.fd = fd;
  epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,&ev);
  for(auto it = fds.begin();it!=fds.end();++it){
    if((*it).data.fd == fd){
      fds.erase(it);
      break;
    }
  }
}

void modify_event(int epollfd,int fd,int state,vector<epoll_event> &fds){
  struct epoll_event ev;
  ev.events = state;
  ev.data.fd = fd;
  epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&ev);
  for(int i = 0;i<fds.size();i++){
    if(fds[i].data.fd == fd){
      fds[i].events = state;
    }
  }
}


void modify_event(int epollfd,int fd,int state,vector<epoll_event> &fds,char * buf ){
  struct epoll_event ev;
  ev.events = state;
  ev.data.fd = fd;
  epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&ev);
  for(int i = 0;i<fds.size();i++){
    if(fds[i].data.fd == fd){
      fds[i].events = state;
      fds[i].data.ptr = buf;
    }
  }
}

void do_epoll(int listenfd){
  vector<epoll_event> fds;
  int epollfd = epoll_create(100);
  add_event(epollfd,listenfd,EPOLLIN,fds);
  while(1){
    int result = epoll_wait(epollfd,fds.data(),fds.size(),-1);
    for(int i =0;i<result;++i){
      int fd = fds[i].data.fd;
      if((fd == listenfd)&&(fds[i].events & EPOLLIN)){
        struct sockaddr_in cliaddr;
        socklen_t len = sizeof(cliaddr);
        int clifd = accept(listenfd,(struct sockaddr *)&cliaddr,&len);
        if(clifd == -1){
          cout<<"accpet error"<<endl;
        }
        else{
          cout<<"accpet a client "<<inet_ntoa(cliaddr.sin_addr)<<" : "<<cliaddr.sin_port<<endl;
          //add event for read for new client file descriptor
          add_event(epollfd,clifd,EPOLLIN,fds);
        }
      }
      else if(fds[i].events & EPOLLIN){
        char * buf = new char [1024];
        memset(buf,0,1024);
        int n = read(fd,buf,1024);
        if(n==-1){
          cout<<"read error "<<endl;
          close(fd);
          delete_event(epollfd,fd,EPOLLIN,fds);
        }
        else{
          cout<<"read message:"<<buf<<endl;
          modify_event(epollfd,fd,EPOLLOUT,fds,buf);
        }
      }
      else if(fds[i].events & EPOLLOUT){
        char * buf = static_cast<char *> (fds[i].data.ptr);
        int n = write(fd,buf,strlen(buf));
        if(n == -1){
          cout<<"write error "<<endl;
          close(fd);
          delete_event(epollfd,fd,EPOLLOUT,fds);
        }
        else{
          modify_event(epollfd,fd,EPOLLIN,fds,NULL);
        }
        delete buf;
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