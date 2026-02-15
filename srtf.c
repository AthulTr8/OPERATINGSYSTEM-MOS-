#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n];
    int remaining_bt[n], completed[n];

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("P%d Arrival Time: ", pid[i]);
        scanf("%d", &at[i]);
        printf("P%d Burst Time: ", pid[i]);
        scanf("%d", &bt[i]);

        remaining_bt[i] = bt[i];
        completed[i] = 0;
    }

    int time = 0, completedCount = 0;

    while (completedCount < n) {
        int idx = -1;
        int min_bt = 9999;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && completed[i] == 0) {
                if (remaining_bt[i] < min_bt) {
                    min_bt = remaining_bt[i];
                    idx = i;
                }
                else if (remaining_bt[i] == min_bt) {
                    if (at[i] < at[idx]) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            time++;  // CPU idle
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

    // Find total time taken (max completion time)
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