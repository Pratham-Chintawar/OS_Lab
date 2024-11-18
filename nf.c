#include <stdio.h>
#include <stdbool.h>
void nextFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) 
        allocation[i] = -1;  // Initialize all allocations to -1

    int lastAllocated = 0;  // Start search from the last allocated block

    for (int i = 0; i < n; i++) {
        int j = lastAllocated;  // Start search from where we left off
        while (true) {
            if (blockSize[j] >= processSize[i]) {  // If block fits
                allocation[i] = j;  // Allocate block j to process i
                blockSize[j] -= processSize[i];  // Reduce block size
                lastAllocated = j;  // Update last allocated index
                break;
            }
            j = (j + 1) % m;  // Move to the next block (circular search)
            if (j == lastAllocated)  // If we searched all blocks
                break;
        }
    }

    printf("\nNext Fit Allocation:\nProcess No.\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("%d\t\t\t%d\n", i + 1, allocation[i] + 1);
        else
            printf("%d\t\t\tNot Allocated\n", i + 1);
    }
}

int main() {
    int blockSize[] = {100, 500, 200, 300, 600};
    int processSize[] = {212, 417, 112, 426};
    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    nextFit(blockSize, m, processSize, n);
    return 0;
}
