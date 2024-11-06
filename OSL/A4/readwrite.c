#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t writerSema;
int readcount = 0;
int shared = 0;
pthread_mutex_t mutex;


void *writer(void *wno){
  while(1){
    sem_wait(&writerSema);
    shared++;
    printf("Id %d writing %d\n", (*(int*)wno), shared);
    sem_post(&writerSema);
    sleep(2);
  }
}

void *reader(void *rno){
  while(1){
    pthread_mutex_lock(&mutex);
    readcount++;
    if(readcount == 1)
      sem_wait(&writerSema);
    pthread_mutex_unlock(&mutex);
    
    printf("Id %d reading %d\n", (*(int*)rno), shared);
    
    pthread_mutex_lock(&mutex);
    readcount--;
    if(readcount == 0)
      sem_post(&writerSema);
    pthread_mutex_unlock(&mutex);
    
    sleep(1);
  }
}

int main(){
  sem_init(&writerSema, 0, 1);
  pthread_mutex_init(&mutex, NULL);
  int writerID[5], readerID[10];
  pthread_t rea[10], writ[5];
  for(int i=0; i<10; i++) readerID[i] = i+1;
  for(int i=0; i<5; i++) writerID[i] = i+1;
  for(int i=0; i<10; i++) pthread_create(&rea[i], NULL, reader, (void*)&readerID[i]);
  for(int i=0; i<5; i++) pthread_create(&writ[i], NULL, writer, (void*)&writerID[i]);
  for(int i=0; i<10; i++) pthread_join(rea[i], NULL);
  for(int i=0; i<5; i++) pthread_join(writ[i], NULL);
  return 0;
}
