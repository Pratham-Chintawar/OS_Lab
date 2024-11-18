#include <stdio.h>
#include <limits.h>  // For INT_MIN

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) 
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int worstIndex = -1;
        int maxSize = INT_MIN;  // Initialize with the minimum possible value

        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i] && blockSize[j] > maxSize) {
                worstIndex = j;  // Update worst fit block index
                maxSize = blockSize[j];  // Update the maximum size found
            }
        }

        if (worstIndex != -1) {
            allocation[i] = worstIndex;  // Allocate block to process
            blockSize[worstIndex] -= processSize[i];  // Reduce block size
        }
    }

    printf("\nWorst Fit Allocation:\nProcess No.\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("%d\t\t\t%d\n", i + 1, allocation[i] + 1);
        else
            printf("%d\t\t\tNot Allocated\n", i + 1);
    }
}

int main() {
    int blockSize[] = {100, 500, 200, 300, 600};
    int processSize[] = {312, 417, 245 , 426};
    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    worstFit(blockSize, m, processSize, n);
    return 0;
}
