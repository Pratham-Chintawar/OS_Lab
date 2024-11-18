#include <stdio.h>

struct Process {
    int pid;        
    int burstTime;  
    int remainingTime; 
    int priority;  
    int waitingTime;
    int turnAroundTime;
    int arrivalTime;
    int isCompleted;
};

int findNextProcess(struct Process proc[], int n, int currentTime) {
    int highestPriority = 1000000; 
    int nextProcess = -1; 
    
    for (int i = 0; i < n; i++) {
        if (proc[i].arrivalTime <= currentTime && proc[i].isCompleted == 0) {
            if (proc[i].priority < highestPriority) {
                highestPriority = proc[i].priority;
                nextProcess = i;
            }
        }
    }
    
    return nextProcess;
}

// Function to display the results
void displayProcesses(struct Process proc[], int n) {
    printf("\nPID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrivalTime,
               proc[i].burstTime, proc[i].priority, proc[i].waitingTime, proc[i].turnAroundTime);
    }
}

int main() {
    int n;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process proc[n];
    int totalTime = 0;
    
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Process %d\n", i + 1);
        proc[i].pid = i + 1;
        printf("Burst Time: ");
        scanf("%d", &proc[i].burstTime);
        printf("Priority (lower number means higher priority): ");
        scanf("%d", &proc[i].priority);
        printf("Arrival Time: ");
        scanf("%d", &proc[i].arrivalTime);
        proc[i].remainingTime = proc[i].burstTime;
        proc[i].isCompleted = 0;
        totalTime += proc[i].burstTime; // Calculate total burst time to track simulation end
    }

    int currentTime = 0, completed = 0;

    while (completed != n) {
        int nextProcess = findNextProcess(proc, n, currentTime);

        if (nextProcess == -1) {
            currentTime++;
        } else {
            proc[nextProcess].remainingTime--;
            currentTime++;

            if (proc[nextProcess].remainingTime == 0) {
                proc[nextProcess].isCompleted = 1;
                completed++;
                
                proc[nextProcess].turnAroundTime = currentTime - proc[nextProcess].arrivalTime;
                proc[nextProcess].waitingTime = proc[nextProcess].turnAroundTime - proc[nextProcess].burstTime;
            }
        }
    }

    displayProcesses(proc, n);
    
    return 0;
}
