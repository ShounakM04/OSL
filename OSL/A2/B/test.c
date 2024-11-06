#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
int main(int argc, char *argv[]){
    int size = atoi(argv[1]);
    printf("\nReceived size: %d\n", size);
    int arr[size];
    for(int i=0; i<size; i++){
        arr[i] = atoi(argv[i+2]);
        printf("%d\t", arr[i]);
    }
    printf("\nEnter number to be searched: ");
    int ele;
    scanf("%d", &ele);
    int low = 0;
    int high = size-1;
    bool flag = false;
    while(low <= high){
        int mid = (low+high)/2;
        if(ele == arr[mid]){
            flag = true;
            printf("\nElement found at pos %d: ", mid+1);
            break;
        }
        else if(ele < arr[mid]){
            high = mid-1;
        }
        else low = mid+1;
    }
    if(flag == false) printf("Not found");

    printf("\nNow returning to parent");
}
