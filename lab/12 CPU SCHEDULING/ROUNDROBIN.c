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
    int rt;
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
        printf("Enter the arrival time for process %d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;  // Copy burst time
    }

    // Sort by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at || 
               (p[j].at == p[j + 1].at && p[j].bt > p[j + 1].bt)) {
                process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Round Robin Scheduling with Gantt chart and idle time
    while (done < n) {
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0 && p[i].at <= t) {
                executed = 1;
                if (p[i].rt > QUANTUM) {
                    seq[k] = p[i].pid;
                    t += QUANTUM;
                    time[k++] = t;
                    p[i].rt -= QUANTUM;
                } else {
                    seq[k] = p[i].pid;
                    t += p[i].rt;
                    time[k++] = t;
                    p[i].rt = 0;
                    p[i].ct = t;
                    p[i].tt = p[i].ct - p[i].at;
                    p[i].wt = p[i].tt - p[i].bt;
                    done++;
                }
            }
        }
        if (!executed) {
            // CPU idle
            seq[k] = 0;
            int nextArrival = MAX;  
            for (int i = 0; i < n; i++) {
                if (p[i].rt > 0 && p[i].at > t) {
                    nextArrival = (p[i].at < nextArrival) ? p[i].at : nextArrival;
                }
            }     // 0 represents idle
            t= nextArrival;
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
    double avg_ta=0;
    double avg_w=0;
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        avg_ta += p[i].tt;
        avg_w += p[i].wt;
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

    printf("\nAVERAGE TURNAROUND TIME\n");

    printf("%.2lf\n",avg_ta/n);

    printf("AVERAGE WAITING TIME\n");

    printf("%.2lf",avg_w/n);

    printf("\n");
    return 0;
}
