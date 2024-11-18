#include <stdio.h>

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
};

void calculateSRTF(struct Process proc[], int n) {
    int completed = 0, currentTime = 0, shortest = -1;
    int minRemainingTime = 999999; 
    int totalWaitingTime = 0, totalTurnaroundTime = 0, finishTime;
    int isCompleted[n];
    int startTimes[100], procIDs[100], index = 0; 

    for (int i = 0; i < n; i++) {
        proc[i].remainingTime = proc[i].burstTime;
        isCompleted[i] = 0;
    }

    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && !isCompleted[i] && proc[i].remainingTime < minRemainingTime) {
                minRemainingTime = proc[i].remainingTime;
                shortest = i;
            }
        }

        if (shortest == -1) {
            currentTime++;
            continue;
        }

        if (index == 0 || procIDs[index - 1] != proc[shortest].processID) {
            startTimes[index] = currentTime;
            procIDs[index] = proc[shortest].processID;
            index++;
        }

        proc[shortest].remainingTime--;
        minRemainingTime = proc[shortest].remainingTime;

        if (minRemainingTime == 0) {
            minRemainingTime = 999999; 
            completed++;
            isCompleted[shortest] = 1;
            finishTime = currentTime + 1;
            
            proc[shortest].turnaroundTime = finishTime - proc[shortest].arrivalTime;
            proc[shortest].waitingTime = proc[shortest].turnaroundTime - proc[shortest].burstTime;
            
            totalWaitingTime += proc[shortest].waitingTime;
            totalTurnaroundTime += proc[shortest].turnaroundTime;
        }

        currentTime++;
    }

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].processID, proc[i].arrivalTime, proc[i].burstTime, proc[i].waitingTime, proc[i].turnaroundTime);
    }

    float avgWaitingTime = (float)totalWaitingTime / n;
    float avgTurnaroundTime = (float)totalTurnaroundTime / n;

    printf("\nAverage Waiting Time: %.2f", avgWaitingTime);
    printf("\nAverage Turnaround Time: %.2f\n", avgTurnaroundTime);

    printGanttChartSRTF(procIDs, startTimes, index, currentTime);
}

void printGanttChartSRTF(int procIDs[], int startTimes[], int n, int finishTime) {
    printf("\nGantt Chart:\n ");
    
    for (int i = 0; i < n; i++) {
        printf(" ");
        for (int j = 0; j < startTimes[i + 1] - startTimes[i]; j++) {
            printf("--");
        }
        printf(" ");
    }
    printf("\n|");

    for (int i = 0; i < n; i++) {
        printf(" P%d ", procIDs[i]);
        for (int j = 0; j < startTimes[i + 1] - startTimes[i] - 1; j++) {
            printf(" ");
        }
        printf("|");
    }

    printf("\n ");
    for (int i = 0; i < n; i++) {
        printf(" ");
        for (int j = 0; j < startTimes[i + 1] - startTimes[i]; j++) {
            printf("--");
        }
        printf(" ");
    }
    printf("\n");

    printf("0");
    for (int i = 0; i < n; i++) {
        printf("   %d", startTimes[i + 1]);
    }
    printf("   %d\n", finishTime);
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

    calculateSRTF(proc, n);

    return 0;
}