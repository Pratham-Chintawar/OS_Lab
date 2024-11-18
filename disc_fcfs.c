#include <stdio.h>
#include <stdlib.h>

void fcfs(int requests[], int n, int head) {
    int seekCount = 0;
    printf("\nFCFS Disk Scheduling:\nSequence: %d ", head);

    for (int i = 0; i < n; i++) {
        seekCount += abs(requests[i] - head);  // Seek time calculation
        head = requests[i];  // Move head to the current request
        printf("-> %d ", head);
    }

    printf("\nTotal Seek Operations: %d\n", seekCount);
}

int main() {
    int requests[] = {82, 170, 43, 140, 24, 16, 190};
    int n = sizeof(requests) / sizeof(requests[0]);
    int head = 50;

    fcfs(requests, n, head);
    return 0;
}
