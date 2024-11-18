#include <stdio.h>

int findOptimal(int pages[], int n, int frame[], int frames, int current) {
    int farthest = current, index = -1;

    for (int i = 0; i < frames; i++) {
        int j;  
        for (j = current + 1; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        if (j == n)  // If a page is never used again
            return i;
    }
    return (index == -1) ? 0 : index;
}

void optimal(int pages[], int n, int frames) {
    int frame[frames], pageFaults = 0;

    for (int i = 0; i < frames; i++) 
        frame[i] = -1;  // Initialize frames to -1

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {  // Page fault occurs
            int replaceIndex;
            if (i < frames)
                replaceIndex = i;  // Fill empty frames initially
            else
                replaceIndex = findOptimal(pages, n, frame, frames, i);

            frame[replaceIndex] = pages[i];
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
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames = 3;

    optimal(pages, n, frames);
    return 0;
}
