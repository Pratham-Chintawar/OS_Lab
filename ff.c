#include <stdio.h>

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) 
        allocation[i] = -1;  // Initialize all allocations to -1 (not allocated)

    for (int i = 0; i < n; i++) { // Iterate over each process
        for (int j = 0; j < m; j++) { // Check all memory blocks
            if (blockSize[j] >= processSize[i]) {  // If block fits
                allocation[i] = j;  // Allocate block j to process i
                blockSize[j] -= processSize[i];  // Reduce available block size
                break;  // Stop searching after first fit
            }
        }
    }

    printf("\nFirst Fit Allocation:\nProcess No.\tBlock No.\n");
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

    firstFit(blockSize, m, processSize, n);
    return 0;
}
