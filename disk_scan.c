#include <stdio.h>
#include <stdlib.h>

void scan(int requests[], int n, int head, int diskSize, int direction) {
    int seekCount = 0;
    printf("\nSCAN Disk Scheduling:\nSequence: %d ", head);

    // Sort requests to service them in one direction
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    // Move towards the given direction
    if (direction == 1) {  // Move right
        for (int i = 0; i < n; i++) {
            if (requests[i] >= head) {
                seekCount += abs(requests[i] - head);
                head = requests[i];
                printf("-> %d ", head);
            }
        }
        seekCount += abs(diskSize - 1 - head);
        head = diskSize - 1;
    } else {  // Move left
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] <= head) {
                seekCount += abs(requests[i] - head);
                head = requests[i];
                printf("-> %d ", head);
            }
        }
        seekCount += abs(0 - head);
        head = 0;
    }

    printf("\nTotal Seek Operations: %d\n", seekCount);
}

int main() {
    int requests[] = {82, 170, 43, 140, 24, 16, 190};
    int n = sizeof(requests) / sizeof(requests[0]);
    int head = 50;
    int diskSize = 200;
    int direction = 0;  // 1 = right, 0 = left

    scan(requests, n, head, diskSize, direction);
    return 0;
}