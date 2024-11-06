#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void demonstrateZombie() {
    pid_t pid = fork();
    
    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    }
    else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) is running\n", getpid());
        printf("Child process is exiting\n");
        exit(0);  // Child exits, creating a zombie
    }
    else {
        // Parent process
        printf("Parent process (PID: %d) is running\n", getpid());
        printf("Child process (PID: %d) will become a zombie\n", pid);
        
        // Parent process enters infinite loop, keeping child as zombie
        while (1) {
            sleep(1);  // Sleep to reduce CPU usage
        }
    }
}
void demonstrateOrphan() {
    pid_t pid = fork();
    
    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    }
    else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) is running\n", getpid());
        printf("Parent process (PID: %d) will exit soon\n", getppid());
        sleep(2);  // Ensure parent exits first
        printf("Child's parent PID after parent exits: %d\n", getppid());
        printf("Child process (now orphan) is exiting\n");
        exit(0);
    }
    else {
        // Parent process
        printf("Parent process (PID: %d) is running\n", getpid());
        printf("Parent process is exiting without waiting\n");
        exit(0);  // Parent exits without waiting, child becomes orphan
    }
}
int main() {
    demonstrateOrphan() ;
    return 0;
}
