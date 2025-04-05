#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int pid;
    int at;
    int bt;
    int rem_bt; // Remaining burst time
    int pri;    // Priority (lower number = higher priority)
    int wt;
    int ct;
    int tt;
    int done;
} process;

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int seq[MAX], time[MAX], k = 0, t = 0, completed = 0;
    process p[n];

    // Input
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].rem_bt = p[i].bt;
        printf("Enter priority for process %d (lower number = higher priority): ", i + 1);
        scanf("%d", &p[i].pri);
        p[i].done = 0;
    }

    // Scheduling loop (Preemptive Priority)
    while (completed < n) {
        int idx = -1;
        int highest_priority = MAX;
        // Find highest priority job available at time t
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= t && p[i].pri < highest_priority) {
                highest_priority = p[i].pri;
                idx = i;
            }
        }

        if (idx != -1) {
            // Process execution
            if (k == 0 || seq[k - 1] != p[idx].pid) {
                seq[k] = p[idx].pid;
                time[k++] = t;
            }
            p[idx].rem_bt--;
            t++;

            if (p[idx].rem_bt == 0) {
                p[idx].done = 1;
                p[idx].ct = t;
                p[idx].tt = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tt - p[idx].bt;
                completed++;
            }
        } else {
            // CPU Idle
            if (k == 0 || seq[k - 1] != 0) {
                seq[k] = 0;
                time[k++] = t;
            }
            t++;
        }
    }


    // Sort by PID for output
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].pid > p[j + 1].pid) {
                process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Output Table
    double avg_ta = 0, avg_w = 0;
    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        avg_ta += p[i].tt;
        avg_w += p[i].wt;
        printf("%7d\t%12d\t%10d\t%8d\t%15d\t%15d\t%13d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pri, p[i].ct, p[i].tt, p[i].wt);
    }

    // Gantt Chart
    printf("\nGantt Chart:\n ");
    for (int i = 0; i < k; i++) {
        printf("--------");
    }
    printf("\n");

    for (int i = 0; i < k; i++) {
        if (seq[i] == 0)
            printf("| IDE\t");
        else if (seq[i] < 10)
            printf("| P0%d\t", seq[i]);
        else
            printf("| P%d\t", seq[i]);
    }

    printf("|\n ");
    for (int i = 0; i < k; i++) {
        printf("--------");
    }
    printf("\n");

    // ✅ Fix: Separate time loop + print final time after last tick
    for (int i = 0; i < k; i++) {
        printf("%d\t", time[i]);
    }
    printf("%d\n", t);
    // Averages
    printf("\n\nAVERAGE TURNAROUND TIME:\n%.2lf\n", avg_ta / n);
    printf("AVERAGE WAITING TIME:\n%.2lf\n", avg_w / n);

    return 0;
}
