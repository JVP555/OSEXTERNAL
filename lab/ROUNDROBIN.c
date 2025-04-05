#include <stdio.h>

#define QUANTUM 2
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

    int seq[MAX], time[MAX], b[n], k = 0, t = 0, done = 0;
    process p[n];

    // Input
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter the arrival time for process %d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &p[i].bt);
        b[i] = p[i].bt;  // Copy burst time
    }

    // Sort by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at || 
               (p[j].at == p[j + 1].at && p[j].bt > p[j + 1].bt)) {
                process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;

                int tmp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = tmp;
            }
        }
    }

    // Round Robin Scheduling with Gantt chart and idle time
    while (done < n) {
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (b[i] > 0 && p[i].at <= t) {
                executed = 1;
                if (b[i] > QUANTUM) {
                    seq[k] = p[i].pid;
                    t += QUANTUM;
                    time[k++] = t;
                    b[i] -= QUANTUM;
                } else {
                    seq[k] = p[i].pid;
                    t += b[i];
                    time[k++] = t;
                    b[i] = 0;
                    p[i].ct = t;
                    p[i].tt = p[i].ct - p[i].at;
                    p[i].wt = p[i].tt - p[i].bt;
                    done++;
                }
            }
        }
        if (!executed) {
            // CPU idle
            seq[k] = 0;     // 0 represents idle
            t++;
            time[k++] = t;
        }
    }

    // Sort by PID for final output
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
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%7d\t%12d\t%10d\t%15d\t%15d\t%13d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tt, p[i].wt);
    }

    // Gantt Chart
    printf("\nGantt Chart:\n");
    printf(" ");
    for (int i = 0; i < k; i++) {
        printf("--------");
    }
    printf("\n");
    for (int i = 0; i < k; i++) {
        if (seq[i] == 0)
            printf("|IDE\t");
        else if(seq[i] < 10)
            printf("|P0%d\t", seq[i]);
        else
            printf("|P%d\t", seq[i]);
    }
    printf(" |\n");
    printf(" ");
    for (int i = 0; i < k; i++) {
        printf("--------");
    }
    printf("\n");
    printf("0  \t");
    for (int i = 0; i < k; i++) {
        printf("%1d\t", time[i]);
    }

    printf("\n");
    return 0;
}
