#include <stdio.h>

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int isCompleted;
};

void printGanttChartSJF(int procIDs[], int startTimes[], int n, int finishTime) {
    printf("\nGantt Chart:\n");

    // Top bar
    printf(" ");
    for (int i = 0; i < n; i++) {
        printf(" ");
        for (int j = 0; j < startTimes[i + 1] - startTimes[i]; j++) {
            printf("--");
        }
        printf(" ");
    }
    printf("\n|");

    // Process IDs in the middle
    for (int i = 0; i < n; i++) {
        printf(" P%d ", procIDs[i]);
        for (int j = 0; j < startTimes[i + 1] - startTimes[i] - 1; j++) {
            printf(" ");
        }
        printf("|");
    }

    // Bottom bar
    printf("\n ");
    for (int i = 0; i < n; i++) {
        printf(" ");
        for (int j = 0; j < startTimes[i + 1] - startTimes[i]; j++) {
            printf("--");
        }
        printf(" ");
    }
    printf("\n");

    // Time markers
    printf("%d", startTimes[0]);
    for (int i = 0; i < n; i++) {
        printf("%*d", (startTimes[i + 1] - startTimes[i]) * 2 + 1, startTimes[i + 1]);
    }
    printf("\n");
}

void calculateSJF(struct Process proc[], int n) {
    int currentTime = 0, completed = 0;
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    int ganttProcIDs[100], ganttStartTimes[100], index = 0;

    for (int i = 0; i < n; i++) {
        proc[i].isCompleted = 0;
    }

    while (completed != n) {
        int shortest = -1, minBurstTime = 999999;

        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && !proc[i].isCompleted && proc[i].burstTime < minBurstTime) {
                minBurstTime = proc[i].burstTime;
                shortest = i;
            }
        }

        if (shortest == -1) {
            currentTime++;
            continue;
        }

        ganttProcIDs[index] = proc[shortest].processID;
        ganttStartTimes[index] = currentTime;
        index++;

        currentTime += proc[shortest].burstTime;
        proc[shortest].isCompleted = 1;
        completed++;

        proc[shortest].turnaroundTime = currentTime - proc[shortest].arrivalTime;
        proc[shortest].waitingTime = proc[shortest].turnaroundTime - proc[shortest].burstTime;

        totalWaitingTime += proc[shortest].waitingTime;
        totalTurnaroundTime += proc[shortest].turnaroundTime;
    }

    ganttStartTimes[index] = currentTime;

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].processID, proc[i].arrivalTime, proc[i].burstTime, proc[i].waitingTime, proc[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f", (float)totalWaitingTime / n);
    printf("\tAverage Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);

    printGanttChartSJF(ganttProcIDs, ganttStartTimes, index, currentTime);
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].processID = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrivalTime, &proc[i].burstTime);
    }

    calculateSJF(proc, n);

    return 0;
}
