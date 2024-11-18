#include <stdio.h>
#include <stdlib.h>

void cscan(int requests[], int n, int head, int diskSize) {
    int seekCount = 0;
    int distance, curTrack;
    int left[n], right[n];
    int l = 0, r = 0;

    // Add requests on the left and right of the head
    for (int i = 0; i < n; i++) {
        if (requests[i] < head)
            left[l++] = requests[i];
        else
            right[r++] = requests[i];
    }

    // Sort left and right requests
    for (int i = 0; i < l - 1; i++) {
        for (int j = i + 1; j < l; j++) {
            if (left[i] > left[j]) {
                int temp = left[i];
                left[i] = left[j];
                left[j] = temp;
            }
        }
    }

    for (int i = 0; i < r - 1; i++) {
        for (int j = i + 1; j < r; j++) {
            if (right[i] > right[j]) {
                int temp = right[i];
                right[i] = right[j];
            }
        }
    }

    printf("\nC-SCAN Disk Scheduling:\nSequence: %d ", head);

    // Service the right side of the head
    for (int i = 0; i < r; i++) {
        curTrack = right[i];
        seekCount += abs(curTrack - head);
        head = curTrack;
        printf("-> %d ", head);
    }

    // Jump to the end of the disk
    seekCount += abs((diskSize - 1) - head);
    head = 0;
    printf("-> %d ", diskSize - 1);

    // Jump to the start and service the left side
    seekCount += diskSize - 1;
    head = 0;
    for (int i = 0; i < l; i++) {
        curTrack = left[i];
        seekCount += abs(curTrack - head);
        head = curTrack;
        printf("-> %d ", head);
    }

    printf("\nTotal Seek Operations: %d\n", seekCount);
}

int main() {
    int requests[] = {82, 170, 43, 140, 24, 16, 190};
    int n = sizeof(requests) / sizeof(requests[0]);
    int head = 50;
    int diskSize = 200;

    cscan(requests, n, head, diskSize);
    return 0;
}
