#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>

int Send(int fd, char *buf, size_t len) {
  size_t sended = 0;
  int count;
  if (len == 0)
    return 0;
  while (sended < len) {
    do {
      count = send(fd, buf, len - sended, 0);
    } while ((count < 0) && (errno == EINTR));
    if (count < 0)
      return count;
    sended += count;
    buf += count;
  }
  return len;
}

int Recv(int fd, char *buf, size_t len) {
  size_t readed = 0;
  int count;
  if (len == 0)
    return 0;
  while (readed < len) {
    do {
      count = read(fd, buf, len - readed);
    } while ((count < 0) && (errno == EINTR));
    //error
    if (count < 0) {
      return count;
    }
    //peer close the connection, cannot read anything
    else if (count == 0) {
      return readed;
    }
    readed += count;
    buf += count;
  }
  return len;
}