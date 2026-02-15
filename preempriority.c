#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], priority[n], ct[n], tat[n], wt[n], completed[n], remaining_bt[n];

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("P%d Arrival Time: ", pid[i]);
        scanf("%d", &at[i]);
        printf("P%d Burst Time: ", pid[i]);
        scanf("%d", &bt[i]);
        printf("P%d Priority (Lower = Higher): ", pid[i]);
        scanf("%d", &priority[i]);
        
        remaining_bt[i] = bt[i]; 
        completed[i] = 0;
    }

    int time = 0, completedCount = 0;

    while (completedCount < n) {
        int idx = -1;
        int maxPriority = 9999;

        // Find the process with highest priority among those that have arrived
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && completed[i] == 0) {
                if (priority[i] < maxPriority) {
                    maxPriority = priority[i];
                    idx = i;
                }
                // Tie-breaker: If priorities are same, use Arrival Time
                else if (priority[i] == maxPriority) {
                    if (at[i] < at[idx]) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            time++; // CPU is idle
        } else {
            remaining_bt[idx]--; 
            time++;

            if (remaining_bt[idx] == 0) {
                ct[idx] = time;
                completed[idx] = 1;
                completedCount++;
            }
        }
    }

    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        totalWT += wt[i];
        totalTAT += tat[i];
    }

    // Output Table
    printf("\nProcess\tAT\tBT\tPri\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], priority[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);

    return 0;
}