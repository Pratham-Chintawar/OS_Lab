#include <stdio.h>

int findLRU(int time[], int frames) {
    int min = time[0], index = 0;
    for (int i = 1; i < frames; i++) {
        if (time[i] < min) {
            min = time[i];
            index = i;
        }
    }
    return index;
}

void lru(int pages[], int n, int frames) {
    int frame[frames], time[frames], pageFaults = 0, count = 0;

    for (int i = 0; i < frames; i++) 
        frame[i] = -1;  // Initialize frames to -1

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                time[j] = ++count;  // Update the time stamp
                break;
            }
        }

        if (!found) {  // Page fault occurs
            int replaceIndex = (i < frames) ? i : findLRU(time, frames);
            frame[replaceIndex] = pages[i];
            time[replaceIndex] = ++count;
            pageFaults++;
        }

        printf("\nFrame: ");
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1) 
                printf("%d ", frame[j]);
            else 
                printf("- ");
        }
    }
    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main() {
    int pages[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames = 3;

    lru(pages, n, frames);
    return 0;
}
