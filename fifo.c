#include <stdio.h>

void fifo(int pages[], int n, int frames) {
    int frame[frames];
    int front = 0, pageFaults = 0;

    for (int i = 0; i < frames; i++) 
        frame[i] = -1;  // Initialize frames to -1 (empty)

    for (int i = 0; i < n; i++) {
        int found = 0;
        // Check if the page is already in a frame
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {  // Page fault occurs
            frame[front] = pages[i];  // Replace the oldest page
            front = (front + 1) % frames;  // Update the front pointer
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
    int pages[] = {1, 3, 0, 3, 5, 6, 3};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames = 3;

    fifo(pages, n, frames);
    return 0;
}

