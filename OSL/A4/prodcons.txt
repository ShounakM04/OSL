#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#define BUFFER 5

sem_t full, empty;
pthread_mutex_t mutex;
int in = 0;
int out = 0;
int buffer[BUFFER];

void *producer(void* arg){
  int item;
  while(1){
    item = rand()%5;
    if(sem_trywait(&empty) == -1){
      printf("\nProducer waiting: Buffer is full.");
      sem_wait(&empty);
    }
    pthread_mutex_lock(&mutex);
    buffer[in] = item;
    in = (in+1)%BUFFER;
    printf("\nProducer Produced : %d", item);
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
    sleep(1);
  }
}

void *consumer(void* arg){
  int item;
  while(1){
    if(sem_trywait(&full) == -1){
      printf("\nConsumer waiting: Buffer is empty.");
      sem_wait(&full);
    }
    pthread_mutex_lock(&mutex);
    item = buffer[out];
    out = (out+1)%BUFFER;
    printf("\nConsumer Consumed : %d", item);
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
    sleep(2);
  }
}

int main(){
  pthread_t prod, cons;
  
  sem_init(&full, 0, 0);
  sem_init(&empty, 0, BUFFER);
  
  pthread_mutex_init(&mutex, NULL);
  
  pthread_create(&prod, NULL, producer, NULL);
  pthread_create(&cons, NULL, consumer, NULL);
  pthread_join(prod, NULL);
  pthread_join(cons, NULL);
  
  return 0;
}
