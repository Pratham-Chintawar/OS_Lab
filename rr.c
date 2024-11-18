#include <stdio.h>

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
};

#include <stdio.h>

void printGanttChartRR(int ganttProcIDs[], int ganttStartTimes[], int size, int totalTime) {
    printf("\nGantt Chart:\n");

    // Print the top border of the Gantt chart
    printf(" ");
    for (int i = 0; i < size; i++) {
        printf("------");
    }
    printf("-\n");

    // Print the process IDs in each time slot
    for (int i = 0; i < size; i++) {
        printf("|  P%d ", ganttProcIDs[i]);
    }
    printf("|\n");

    // Print the middle border of the Gantt chart
    printf(" ");
    for (int i = 0; i < size; i++) {
        printf("------");
    }
    printf("-\n");

    // Print the timeline, aligning the times with each process segment
    for (int i = 0; i < size; i++) {
        printf("%-6d", ganttStartTimes[i]);
    }
    printf("%-6d\n", totalTime); // Print the final total time at the end
}



void calculateRoundRobin(struct Process proc[], int n, int timeQuantum) {
    int currentTime = 0, completed = 0;
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    int ganttProcIDs[100], ganttStartTimes[100], index = 0;

    for (int i = 0; i < n; i++) {
        proc[i].remainingTime = proc[i].burstTime;
    }

    while (completed != n) {
        int allIdle = 1;

        for (int i = 0; i < n; i++) {
            if (proc[i].remainingTime > 0 && proc[i].arrivalTime <= currentTime) {
                allIdle = 0;

                if (index == 0 || ganttProcIDs[index - 1] != proc[i].processID) {
                    ganttProcIDs[index] = proc[i].processID;
                    ganttStartTimes[index] = currentTime;
                    index++;
                }

                if (proc[i].remainingTime > timeQuantum) {
                    currentTime += timeQuantum;
                    proc[i].remainingTime -= timeQuantum;

                } else {
                    currentTime += proc[i].remainingTime;
                    proc[i].remainingTime = 0;
                    completed++;

                    proc[i].turnaroundTime = currentTime - proc[i].arrivalTime;
                    proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;

                    totalWaitingTime += proc[i].waitingTime;
                    totalTurnaroundTime += proc[i].turnaroundTime;
                }
            }
        }

        if (allIdle) {
            currentTime++; 
        }
    }

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].processID, proc[i].arrivalTime, proc[i].burstTime, proc[i].waitingTime, proc[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f", (float)totalWaitingTime / n);
    printf("\t\tAverage Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);

    printGanttChartRR(ganttProcIDs, ganttStartTimes, index, currentTime);
}

int main() {
    int n, timeQuantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].processID = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrivalTime, &proc[i].burstTime);
    }

    printf("Enter time quantum: ");
    scanf("%d", &timeQuantum);

    calculateRoundRobin(proc, n, timeQuantum);

    return 0;
}
