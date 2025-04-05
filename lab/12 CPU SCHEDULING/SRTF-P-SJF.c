#include <stdio.h>

#define MAX 100

typedef struct {
    int pid;
    int at;
    int bt;
    int rt;
    int wt;
    int ct;
    int tt;
    int started;  // to track first response time if needed// not doing in this case
    int completed;
} process;

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int seq[MAX], time[MAX], k = 0;
    process p[n];

    // Input
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter the arrival time for process %d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].completed = 0;
        p[i].started = 0;
    }

    int completed = 0, t = 0, prev = -1;

    while (completed < n) {
        int idx = -1;
        int min_rt = MAX;

        // Find process with shortest remaining time at time t
        for (int i = 0; i < n; i++) {
            if (p[i].at <= t && p[i].rt > 0 && p[i].rt < min_rt) {
                min_rt = p[i].rt;
                idx = i;
            }
        }

        if (idx != -1) {
            if (prev != p[idx].pid) {
                seq[k] = p[idx].pid;
                time[k++] = t;
                prev = p[idx].pid;
            }

            p[idx].rt--;
            t++;

            if (p[idx].rt == 0) {
                p[idx].ct = t;
                p[idx].tt = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tt - p[idx].bt;
                p[idx].completed = 1;
                completed++;
            }
        } else {
            // CPU idle
            if (prev != 0) {
                seq[k] = 0;
                time[k++] = t;
                prev = 0;
            }
            t++;
        }
    }

    time[k++] = t;

    // Sort for output
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].pid > p[j + 1].pid) {
                process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Output
    double avg_ta = 0, avg_w = 0;
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        avg_ta += p[i].tt;
        avg_w += p[i].wt;
        printf("%7d\t%12d\t%10d\t%15d\t%15d\t%13d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tt, p[i].wt);
    }

    // Gantt Chart
    printf("\nGantt Chart:\n ");
    for (int i = 0; i < k - 1; i++) {
        printf("--------");
    }
    printf("\n");

    for (int i = 0; i < k - 1; i++) {
        if (seq[i] == 0)
            printf("| IDE\t");
        else if (seq[i] < 10)
            printf("| P0%d\t", seq[i]);
        else
            printf("| P%d\t", seq[i]);
    }
    printf("|\n ");

    for (int i = 0; i < k - 1; i++) {
        printf("--------");
    }
    printf("\n");

    for (int i = 0; i < k; i++) {
        printf("%d\t", time[i]);
    }

    printf("\n\nAVERAGE TURNAROUND TIME:\n%.2lf\n", avg_ta / n);
    printf("AVERAGE WAITING TIME:\n%.2lf\n", avg_w / n);

    return 0;
}
