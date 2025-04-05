#include <stdio.h>

#define MAX 100

typedef struct {
    int pid;
    int at;
    int bt;
    int wt;
    int ct;
    int tt;
} process;

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    process p[n];
    int seq[MAX], time[MAX], k = 0, t = 0;

    // Input
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter the arrival time for process %d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &p[i].bt);
    }

    // Sort by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // 🔁 Changed RR loop to FCFS execution
    for (int i = 0; i < n; i++) {
        if (t < p[i].at) {
            // CPU idle
            seq[k] = 0;         // 0 = idle
            time[k++] = p[i].at;
            t = p[i].at;
        }
        seq[k] = p[i].pid;
        time[k++] = t + p[i].bt;

        t += p[i].bt;
        p[i].ct = t;
        p[i].tt = p[i].ct - p[i].at;
        p[i].wt = p[i].tt - p[i].bt;
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
    double avg_tt = 0, avg_wt = 0;
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        avg_tt += p[i].tt;
        avg_wt += p[i].wt;
        printf("%7d\t%12d\t%10d\t%15d\t%15d\t%13d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tt, p[i].wt);
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

    // Print timeline
    printf("0\t");
    for (int i = 0; i < k; i++) {
        printf("%d\t", time[i]);
    }

    printf("\n\nAVERAGE TURNAROUND TIME: %.2lf", avg_tt / n);
    printf("\nAVERAGE WAITING TIME: %.2lf\n", avg_wt / n);

    return 0;
}
