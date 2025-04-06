#include <stdio.h>
#define MAX 100
int printres(int r) {
    printf("RESOURCES: ");
    for (int i = 0; i < r; i++) {
        printf("%c ", 'A' + (i));
    }
    printf("\n");
    return 0;
}
int matrixenter(int matrix[MAX][MAX], int m, int n) {
    for (int i = 0; i < m; i++) {
        printf("PROCESS %d: ", i + 1);
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]); // Fixed
        }
    }
    return 0;
}

int matrixsubtraction(int matrix1[MAX][MAX], int matrix2[MAX][MAX], int matrix3[MAX][MAX], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix3[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    return 0;
}

int bankersalgo(int NEED[MAX][MAX], int ALLOCATED[MAX][MAX], int AVAILABLE[MAX], int pro[MAX], int p, int r) {
    int done = 0;
    int safeSequence[p];
    int index = 0;
    while (done < p) {
        int found = 0;
        for (int i = 0; i < p; i++) {
            if (pro[i] == -1) {  // Process not yet finished
                int canProceed = 1;

                for (int j = 0; j < r; j++) {
                    if (NEED[i][j] > AVAILABLE[j]) {
                        canProceed = 0;
                        break;
                    }
                }

                if (canProceed) {
                    for (int j = 0; j < r; j++) {
                        AVAILABLE[j] += ALLOCATED[i][j];
                    }
                    pro[i] = 1;
                    safeSequence[index++] = i+1;
                    printf("PROCESS %d COMPLETED\n",i+1);
                    done++;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("System is not in a safe state!\n");
            return 0;
        }
    }
    printf("System is in a safe state!\n");
    printf("\nSafe sequence: ");
    for (int i = 0; i < p; i++) {
        if(i!=p-1){
        printf("%d->",safeSequence[i]);
        }else{
            printf("%d",safeSequence[i]);
        }
    }
    printf("\n");

    return 1;  // Safe state
}



int matrixprint(int matrix[MAX][MAX], int m, int n,int processes[MAX]) {
    for (int i = 0; i < m; i++) {
        processes[i] = -1;//process not complete
        printf("PROCESS %d: ", i + 1);
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int main() {
    printf("Enter the number of processes: ");
    int p;
    scanf("%d", &p);

    printf("Enter the number of resources: ");
    int r;
    scanf("%d", &r);

    printf("Enter the available resources:\n");
    int AVAILABLE[r],processes[p];
    printres(r);
    printf("AVAILABLE: ");
    for (int i = 0; i < r; i++) {
        scanf("%d", &AVAILABLE[i]);
    }

    int ALLOCATED[MAX][MAX], MAXM[MAX][MAX], NEED[MAX][MAX];

    printf("Enter the allocation matrix:\n");
    printres(r);
    matrixenter(ALLOCATED, p, r);

    printf("Enter the max matrix:\n");
    printres(r);
    matrixenter(MAXM, p, r);

    matrixsubtraction(MAXM, ALLOCATED, NEED, p, r);

    printf("Need Matrix:\n");
    printres(r);
    matrixprint(NEED, p, r,processes);
    printf("\n");
    bankersalgo(NEED, ALLOCATED, AVAILABLE, processes, p, r);
    return 0;
}
