#include <stdio.h>
#include <stdbool.h>

void calc(int pCount, int rCount, int max[pCount][rCount], int need[pCount][rCount], int alloc[pCount][rCount]) {
    for (int i = 0; i < pCount; i++) {
        for (int j = 0; j < rCount; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    printf("Need matrix calculated.\n");
}

bool isSafe(int pCount, int rCount, int available[rCount], int need[pCount][rCount], int alloc[pCount][rCount], int safeSeq[pCount]) {
    bool finished[pCount];
    for (int i = 0; i < pCount; i++) finished[i] = false;

    int work[rCount];
    for (int i = 0; i < rCount; i++) work[i] = available[i];

    int count = 0;
    while (count != pCount) {
        bool found = false;
        for (int p = 0; p < pCount; p++) {
            if (!finished[p]) {
                bool canAlloc = true;
                for (int r = 0; r < rCount; r++) {
                    if (need[p][r] > work[r]) {
                        canAlloc = false;
                        break;
                    }
                }
                if (canAlloc) {
                    for (int r = 0; r < rCount; r++) {
                        work[r] += alloc[p][r];
                    }
                    finished[p] = true;
                    safeSeq[count++] = p;
                    found = true;
                }
            }
        }
        if (!found) return false;
    }
    return true;
}

bool newreq(int process, int rCount, int available[rCount], int alloc[][rCount], int need[][rCount], int req[rCount]) {
    printf("Enter resource request for process id %d: ", process);
    for (int i = 0; i < rCount; i++) {
        scanf("%d", &req[i]);
    }
    
    bool canAlloc = true;
    for (int r = 0; r < rCount && canAlloc; r++) {
        if (req[r] > available[r] || req[r] > need[process][r]) {
            canAlloc = false;
        }
    }
    
    if (canAlloc) {
        for (int r = 0; r < rCount; r++) {
            available[r] -= req[r];
            need[process][r] -= req[r];
            alloc[process][r] += req[r];
        }
        printf("Request granted.\n");
        return true;
    } else {
        printf("Request cannot be granted.\n");
        return false;
    }
}

int main() {
    int pCount, rCount;
    printf("Enter Process count: ");
    scanf("%d", &pCount);
    printf("Enter Resource count: ");
    scanf("%d", &rCount);

    int max[pCount][rCount], alloc[pCount][rCount], need[pCount][rCount];
    int available[rCount];
    int safeSeq[pCount];

    printf("Enter Max matrix:\n");
    for (int i = 0; i < pCount; i++) {
        for (int j = 0; j < rCount; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    
    printf("Enter Allocation matrix:\n");
    for (int i = 0; i < pCount; i++) {
        for (int j = 0; j < rCount; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }
    
    printf("Enter Available resources:\n");
    for (int i = 0; i < rCount; i++) scanf("%d", &available[i]);

    int choice, process;
    bool needCalculated = false;

    do {
        printf("\nMenu:\n");
        printf("1. Calculate Need Matrix\n");
        printf("2. Check Safe Sequence\n");
        printf("3. Enter New Request\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                calc(pCount, rCount, max, need, alloc);
                needCalculated = true;
                break;

            case 2:
                if (!needCalculated) {
                    printf("Please calculate the Need matrix first.\n");
                } else {
                    if (isSafe(pCount, rCount, available, need, alloc, safeSeq)) {
                        printf("System is in a safe state.\nSafe sequence: ");
                        for (int i = 0; i < pCount; i++) printf("%d ", safeSeq[i]);
                        printf("\n");
                    } else {
                        printf("System is not in a safe state.\n");
                    }
                }
                break;

            case 3:
                if (!needCalculated) {
                    printf("Please calculate the Need matrix first.\n");
                } else {
                    printf("Enter process number (0 to %d): ", pCount - 1);
                    scanf("%d", &process);
                    if (process >= 0 && process < pCount) {
                        int req[rCount];  // Declare req here
                        if (newreq(process, rCount, available, alloc, need, req)) {
                            if (isSafe(pCount, rCount, available, need, alloc, safeSeq)) {
                                printf("After granting request, system remains in a safe state.\nSafe sequence: ");
                                for (int i = 0; i < pCount; i++) printf("%d ", safeSeq[i]);
                                printf("\n");
                            } else {
                                printf("After granting request, system is not in a safe state. Rolling back.\n");
                                for (int r = 0; r < rCount; r++) {
                                    available[r] += req[r];
                                    need[process][r] += req[r];
                                    alloc[process][r] -= req[r];
                                }
                            }
                        }
                    } else {
                        printf("Invalid process number.\n");
                    }
                }
                break;

            case 4:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
