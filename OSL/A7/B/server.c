#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>

int main(){
    int shmid = shmget((key_t)1, 1024, 0666 | IPC_CREAT);
    char *str = (char*) shmat(shmid, (void*)0, 0);
    while(1){
        printf("Enter the text: ");
        fgets(str, 1024, stdin);
        printf("Received text: %s\n", str);
    }
    shmdt(str);
}