#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void sort(int arr[], int n){
  for(int i=0; i<n-1; i++){
    for(int j=0; j<n-i-1; j++){
      if(arr[j] > arr[j+1]){
        int temp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = temp;
      }
    }
  }
}

int main(){
    int size;
    printf("\nenter size: ");
    scanf("%d", &size);
    printf("\nEnter elements: ");
    int arr[size];
    for(int i=0; i<size; i++) scanf("%d", &arr[i]);
    printf("\nNow Sorting");
    sort(arr, size);
    char *args[size+2];
    char argsize[20];
    args[0] = "./test";
    sprintf(argsize, "%d", size);
    args[1] = argsize;

    for(int i=0; i<size; i++){
        args[i+2] = malloc(10*sizeof(char));
        snprintf(args[i+2], 20, "%d", arr[i]);
    }
    args[size+2] = NULL;
    pid_t pid = fork();

    
    if(pid < 0){
        printf("Fork error");
        return 1;
    }
    else if(pid == 0){
        printf("\nIn child");
        sleep(1);
        execve(args[0], args, NULL);
        return 1;
    }
    else{
        printf("\nIn Parent now");
        wait(0);
        printf("\nparent over");
        return 1;
    }
}
