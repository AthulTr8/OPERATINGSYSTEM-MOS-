#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1) return 1;

    // Arrays to store process information
    int pid[n], at[n], bt[n], priority[n], ct[n], tat[n], wt[n], completed[n];

    // Input loop
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("P%d Arrival Time: ", pid[i]);
        scanf("%d", &at[i]);
        printf("P%d Burst Time: ", pid[i]);
        scanf("%d", &bt[i]);
        printf("P%d Priority (Lower number = Higher Priority): ", pid[i]);
        scanf("%d", &priority[i]);
        completed[i] = 0; // Initialize all processes as not completed
    }

    int time = 0, completedCount = 0;

    // Main scheduling loop
    while (completedCount < n) {
        int idx = -1;
        int highestPriority = 99999; // Using a large number to find the minimum

        for (int i = 0; i < n; i++) {
            // Check if process has arrived and is not yet finished
            if (at[i] <= time && completed[i] == 0) {
                // Select process with the best priority (smallest value)
                if (priority[i] < highestPriority) {
                    highestPriority = priority[i];
                    idx = i;
                }
                // Tie-breaker: If priorities are equal, use Arrival Time (FCFS)
                else if (priority[i] == highestPriority) {
                    if (at[i] < at[idx]) {
                        idx = i;
                    }
                }
            }
        }

        // If no process has arrived yet, jump time forward
        if (idx == -1) {
            time++;
        } else {
            // Process the selected job (Non-preemptive: it runs to completion)
            time += bt[idx];
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            
            completed[idx] = 1;
            completedCount++;
        }
    }

    // Calculate Averages
    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        totalWT += wt[i];
        totalTAT += tat[i];
    }

    // Output results
    printf("\n%-10s %-5s %-5s %-5s %-5s %-5s %-5s\n", 
           "Process", "AT", "BT", "Pri", "CT", "TAT", "WT");
    for (int i = 0; i < n; i++) {
        printf("P%-9d %-5d %-5d %-5d %-5d %-5d %-5d\n",
               pid[i], at[i], bt[i], priority[i], ct[i], tat[i], wt[i]);
    }
    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);
    return 0;
}