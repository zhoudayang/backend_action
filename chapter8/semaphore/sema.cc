#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//信号量
sem_t sem;

void * customer(void * id){
  int customer_id = *(static_cast<int*>(id));
  //--sem
  if(sem_wait(&sem) == 0){
    usleep(100);
    printf("customer %d receive service ... \n",customer_id);
    //++sem
    sem_post(&sem);
  }
}

int main(){
  /* Initialize semaphore object SEM to VALUE.  If PSHARED then share it
   with other processes.
  extern int sem_init (sem_t *__sem, int __pshared, unsigned int __value)
  */
  //set sem to 3
  //init semaphore
  sem_init(&sem,0,3);
  constexpr  int NUM = 10;
  pthread_t threads[NUM];
  int ids[NUM];
  for(int i =0;i<NUM;++i){
    ids[i] = i;
    int result = pthread_create(&threads[i],NULL,customer,&ids[i]);
    if(result){
      perror("pthread_create error!\n");
      return -1;
    }
    else{
      printf("customer %i arrive!\n",i);
    }
    usleep(10);
  }
  for(int i =0;i<NUM;i++){
    pthread_join(threads[i],NULL);
  }

  //destroy semaphore
  sem_destroy(&sem);

  return 0;

}
