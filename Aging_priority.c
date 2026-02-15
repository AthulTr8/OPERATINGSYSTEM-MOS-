#include <stdio.h>

#define AGING_INTERVAL 5  // Decrease priority every 5 units of waiting

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], pri[n], initial_pri[n], ct[n], tat[n], wt[n], completed[n];

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("P%d Arrival Time: ", pid[i]);
        scanf("%d", &at[i]);
        printf("P%d Burst Time: ", pid[i]);
        scanf("%d", &bt[i]);
        printf("P%d Initial Priority (Lower = Higher): ", pid[i]);
        scanf("%d", &pri[i]);
        initial_pri[i] = pri[i]; 
        completed[i] = 0;
    }

    int time = 0, completedCount = 0;

    while (completedCount < n) {
        int idx = -1;
        int highest_priority = 9999;

        // Step 1: Apply Gradual Aging to all waiting processes
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && !completed[i]) {
                int wait_time = time - at[i];
                // For every 5 units of wait, priority improves (decreases) by 1
                int aged_priority = initial_pri[i] - (wait_time / AGING_INTERVAL);
                if (aged_priority < 0) aged_priority = 0;
                pri[i] = aged_priority; 
            }
        }

        // Step 2: Select process with the best (lowest) aged priority
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && !completed[i]) {
                if (pri[i] < highest_priority) {
                    highest_priority = pri[i];
                    idx = i;
                } else if (pri[i] == highest_priority) {
                    if (at[i] < at[idx]) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            time++; 
        } else {
            time += bt[idx];
            ct[idx] = time;
            completed[idx] = 1;
            completedCount++;
        }
    }

    // Step 3: Calculations for Averages and Throughput
    float totalWT = 0, totalTAT = 0;
    int maxCompletionTime = 0;

    printf("\nProcess\tAT\tBT\tOrigPri\tFinalPri\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        totalWT += wt[i];
        totalTAT += tat[i];
        
        if (ct[i] > maxCompletionTime) maxCompletionTime = ct[i];

        printf("P%d\t%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", 
                pid[i], at[i], bt[i], initial_pri[i], pri[i], ct[i], tat[i], wt[i]);
    }

    float avgWT = totalWT / n;
    float avgTAT = totalTAT / n;
    float throughput = (float)n / maxCompletionTime;

    printf("\n--- Performance Metrics ---\n");
    printf("Average Waiting Time: %.2f\n", avgWT);
    printf("Average Turnaround Time: %.2f\n", avgTAT);
    printf("Throughput: %.4f processes per unit time\n", throughput);

    return 0;
}