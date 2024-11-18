#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int findClosest(int head, int requests[], bool visited[], int n) {
    int minDistance = 9999, index = -1;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && abs(requests[i] - head) < minDistance) {
            minDistance = abs(requests[i] - head);
            index = i;
        }
    }
    return index;
}

void sstf(int requests[], int n, int head) {
    bool visited[n];
    for (int i = 0; i < n; i++) visited[i] = false;

    int seekCount = 0;
    printf("\nSSTF Disk Scheduling:\nSequence: %d ", head);

    for (int i = 0; i < n; i++) {
        int index = findClosest(head, requests, visited, n);
        visited[index] = true;
        seekCount += abs(requests[index] - head);
        head = requests[index];
        printf("-> %d ", head);
    }

    printf("\nTotal Seek Operations: %d\n", seekCount);
}

int main() {
    int requests[] = {82, 170, 43, 140, 24, 16, 190};
    int n = sizeof(requests) / sizeof(requests[0]);
    int head = 50;

    sstf(requests, n, head);
    return 0;
}
