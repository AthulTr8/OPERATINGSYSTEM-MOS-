#include <stdio.h>

#define AGING_THRESHOLD 15

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n], completed[n];

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("P%d Arrival Time: ", pid[i]);
        scanf("%d", &at[i]);
        printf("P%d Burst Time: ", pid[i]);
        scanf("%d", &bt[i]);
        completed[i] = 0;
    }

    int time = 0, completedCount = 0;

    while (completedCount < n) {
        int idx = -1;
        int min_bt = 9999;

        // Step 1: Check Aging condition
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && completed[i] == 0) {
                int waiting = time - at[i];

                if (waiting > AGING_THRESHOLD) {
                    idx = i;
                    break;   // immediately execute aged process
                }
            }
        }

        // Step 2: Normal SJF if no aged process
        if (idx == -1) {
            for (int i = 0; i < n; i++) {
                if (at[i] <= time && completed[i] == 0) {
                    if (bt[i] < min_bt) {
                        min_bt = bt[i];
                        idx = i;
                    }
                }
            }
        }

        // Step 3: Execute
        if (idx == -1) {
            time++;  // CPU idle
        } else {
            time += bt[idx];   // Non-preemptive
            ct[idx] = time;
            completed[idx] = 1;
            completedCount++;
        }
    }

    float totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        totalWT += wt[i];
        totalTAT += tat[i];
    }

    // Find total execution time (max completion time)
    int totalTime = 0;
    for (int i = 0; i < n; i++) {
        if (ct[i] > totalTime)
            totalTime = ct[i];
    }

    float throughput = (float)n / totalTime;

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f", totalTAT / n);
    printf("\nThroughput = %.3f processes/unit time\n", throughput);

    return 0;
}