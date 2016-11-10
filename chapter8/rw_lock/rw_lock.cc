#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_rwlock_t rwlock;

void *reader(void *arg) {
  pthread_rwlock_rdlock(&rwlock);
  printf("reader %ld got the lock \n ", (long) arg);
  pthread_rwlock_unlock(&rwlock);
  pthread_exit(NULL);
}

void *writer(void *arg) {
  pthread_rwlock_wrlock(&rwlock);
  printf("writer %ld got the lock \n", (long) arg);
  pthread_rwlock_unlock(&rwlock);
  pthread_exit(NULL);
}

int main() {

  int result = pthread_rwlock_init(&rwlock, NULL);
  if (result) {
    printf("init rwlock failed!\n");
    exit(-1);
  }
  int reader_count = 1;
  int writer_count = 1;

  //thread attribute
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  for (int i = 1; i <=5; i++) {
    if (i%3 == 0) {
      pthread_t thread_id;
      pthread_create(&thread_id, &attr, writer, (void *) writer_count);
      ++writer_count;
    }
    else
   {
      pthread_t thread_id;
      pthread_create(&thread_id, &attr, reader, (void *) reader_count);
      ++reader_count;
    }
  }

  sleep(5);

}