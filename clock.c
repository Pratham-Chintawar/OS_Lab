#include <stdio.h>

void clock(int pages[], int n, int frames) {
    int frame[frames], useBit[frames], pointer = 0, pageFaults = 0;

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;  // Initialize frames to -1
        useBit[i] = 0;  // Initialize use bits to 0
    }

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                useBit[j] = 1;  // Set the use bit
                break;
            }
        }

        if (!found) {  // Page fault occurs
            while (useBit[pointer] == 1) {
                useBit[pointer] = 0;  // Reset the use bit
                pointer = (pointer + 1) % frames;  // Move to the next frame
            }
            frame[pointer] = pages[i];  // Replace the page
            useBit[pointer] = 1;  // Set the use bit
            pointer = (pointer + 1) % frames;  // Update the pointer
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

    clock(pages, n, frames);
    return 0;
}
