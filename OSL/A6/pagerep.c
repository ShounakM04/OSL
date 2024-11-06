#include <stdio.h>

#define MAX 100

void FCFS(int pages[], int n, int frames) {
    int frame[frames], page_faults = 0, index = 0;

    for (int i = 0; i < frames; i++) {
        frame[i] = -1; // Initialize frames to -1
    }

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) { // Page hit
                found = 1;
                break;
            }
        }

        if (!found) { // Page fault
            frame[index] = pages[i];
            index = (index + 1) % frames;
            page_faults++;
        }
    }

    printf("FCFS Page Faults: %d\n", page_faults);
}

void LRU(int pages[], int n, int frames) {
    int frame[frames], page_faults = 0, recent[frames];

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
        recent[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) { // Page hit
                found = 1;
                recent[j] = i;
                break;
            }
        }

        if (!found) { // Page fault
            int min = 0;
            for (int j = 1; j < frames; j++) {
                if (recent[j] < recent[min]) {
                    min = j;
                }
            }
            frame[min] = pages[i];
            recent[min] = i;
            page_faults++;
        }
    }

    printf("LRU Page Faults: %d\n", page_faults);
}

void Optimal(int pages[], int n, int frames) {
    int frame[frames], page_faults = 0;

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) { // Page hit
                found = 1;
                break;
            }
        }

        if (!found) { // Page fault
            int index = -1, farthest = i + 1;
            for (int j = 0; j < frames; j++) {
                int next_use = n;
                for (int k = i + 1; k < n; k++) {
                    if (frame[j] == pages[k]) {
                        next_use = k;
                        break;
                    }
                }
                if (next_use > farthest) {
                    farthest = next_use;
                    index = j;
                }
            }
            if (index == -1) index = 0;
            frame[index] = pages[i];
            page_faults++;
        }
    }

    printf("Optimal Page Faults: %d\n", page_faults);
}

int main() {
    int n, frames;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames (minimum 3): ");
    scanf("%d", &frames);

    if (frames < 3) {
        printf("Number of frames should be at least 3.\n");
        return 1;
    }

    FCFS(pages, n, frames);
    LRU(pages, n, frames);
    Optimal(pages, n, frames);

    return 0;
}
