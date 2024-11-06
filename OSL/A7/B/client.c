#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>

int main(){
    int shmid = shmget((key_t)1, 1024, 0666 | IPC_CREAT);
    char *str = (char*) shmat(shmid, (void*)0, 0);
    while(1){
        printf("Received text: %s\n", str);
        sleep(1);
    }
    shmdt(str);
}