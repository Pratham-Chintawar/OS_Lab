#include <stdio.h>

struct Process {
    int processID;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
};

void calculateWaitingTime(struct Process proc[], int n) {
    proc[0].waitingTime = 0; 
    
    for (int i = 1; i < n; i++) {
        proc[i].waitingTime = proc[i-1].waitingTime + proc[i-1].burstTime;
    }
}

void calculateTurnaroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaroundTime = proc[i].burstTime + proc[i].waitingTime;
    }
}

void printGanttChart(int procIDs[], int burstTimes[], int waitingTimes[], int n) {
    printf("\nGantt Chart:\n");
    
    printf(" ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < burstTimes[i]; j++) {
            printf("--");
        }
        printf(" ");
    }
    printf("\n|");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < burstTimes[i] - 1; j++) {
            printf(" ");
        }
        printf("P%d", procIDs[i]);
        for (int j = 0; j < burstTimes[i] - 1; j++) {
            printf(" ");
        }
        printf("|");
    }
    
    printf("\n ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < burstTimes[i]; j++) {
            printf("--");
        }
        printf(" ");
    }
    printf("\n");

    printf("0");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < burstTimes[i]; j++) {
            printf("  ");
        }
        printf("%d", waitingTimes[i] + burstTimes[i]);
    }
    printf("\n");
}

void calculateAverageTime(struct Process proc[], int n) {
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    calculateWaitingTime(proc, n);
    calculateTurnaroundTime(proc, n);
    
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    
    for (int i = 0; i < n; i++) {
        totalWaitingTime += proc[i].waitingTime;
        totalTurnaroundTime += proc[i].turnaroundTime;
        printf("%d\t%d\t\t%d\t\t%d\n", proc[i].processID, proc[i].burstTime, proc[i].waitingTime, proc[i].turnaroundTime);
    }

    float avgWaitingTime = (float)totalWaitingTime / n;
    float avgTurnaroundTime = (float)totalTurnaroundTime / n;

    printf("\nAverage Waiting Time: %.2f", avgWaitingTime);
    printf("\nAverage Turnaround Time: %.2f\n", avgTurnaroundTime);

    int procIDs[n], burstTimes[n], waitingTimes[n];
    for (int i = 0; i < n; i++) {
        procIDs[i] = proc[i].processID;
        burstTimes[i] = proc[i].burstTime;
        waitingTimes[i] = proc[i].waitingTime;
    }

    printGanttChart(procIDs, burstTimes, waitingTimes, n);
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].processID = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].burstTime);
    }

    calculateAverageTime(proc, n);

    return 0;
}
