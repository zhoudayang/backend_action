#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
//保证内存的齐位
#pragma pack(1)
struct pkg {
  int num;
};
int Send(int fd, char *buf, size_t len);

int Recv(int fd, char *buf, size_t len);

#endif