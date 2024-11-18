#include <stdio.h>
#include <limits.h>  // For INT_MAX

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) 
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int bestIndex = -1;
        int minSize = INT_MAX;  // Initialize with the maximum possible value

        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i] && blockSize[j] < minSize) {
                bestIndex = j;  // Update best fit block index
                minSize = blockSize[j];  // Update the minimum size found
            }
        }

        if (bestIndex != -1) {
            allocation[i] = bestIndex;  // Allocate block to process
            blockSize[bestIndex] -= processSize[i];  // Reduce block size
        }
    }

    printf("\nBest Fit Allocation:\nProcess No.\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("%d\t\t\t%d\n", i + 1, allocation[i] + 1);
        else
            printf("%d\t\t\tNot Allocated\n", i + 1);
    }
}

int main() {
    int blockSize[] = {100, 500, 200, 300, 600};
    int processSize[] = {212, 417, 245, 426};
    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    bestFit(blockSize, m, processSize, n);
    return 0;
}
