#include <stdio.h>

#define MAX 100

typedef struct {
    int pid;
    int at;
    int bt;
    int pri;  // priority
    int wt;
    int ct;
    int tt;
    int done;
} process;

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int seq[MAX], time[MAX], k = 0, t = 0, done = 0;
    process p[n];

    // Input
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &p[i].bt);
        printf("Enter priority for process %d (lower number = higher priority): ", i + 1);
        scanf("%d", &p[i].pri);
        p[i].done = 0;
    }

    // Scheduling loop (Non-preemptive Priority)
    while (done < n) {
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
            seq[k] = p[idx].pid;
            t += p[idx].bt;
            time[k++] = t;

            p[idx].ct = t;
            p[idx].tt = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tt - p[idx].bt;
            p[idx].done = 1;
            done++;
        } else {
            // CPU Idle
            seq[k] = 0;
            int next_arrival = MAX;
            for (int i = 0; i < n; i++) {
                if (!p[i].done && p[i].at > t && p[i].at < next_arrival) {
                    next_arrival = p[i].at;
                }
            }
            t = next_arrival;
            time[k++] = t;
        }
    }

    // Sort by PID for display
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].pid > p[j + 1].pid) {
                process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Output table
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

    printf("0\t");
    for (int i = 0; i < k; i++) {
        printf("%d\t", time[i]);
    }

    // Average Times
    printf("\n\nAVERAGE TURNAROUND TIME:\n%.2lf\n", avg_ta / n);
    printf("AVERAGE WAITING TIME:\n%.2lf\n", avg_w / n);

    return 0;
}
