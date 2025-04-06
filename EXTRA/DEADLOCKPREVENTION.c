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
            scanf("%d", &matrix[i][j]);
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

int matrixprint(int matrix[MAX][MAX], int m, int n, int processes[MAX]) {
    for (int i = 0; i < m; i++) {
        processes[i] = -1; // process not complete
        printf("PROCESS %d: ", i + 1);
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}

// Enforces deadlock prevention (Hold and Wait + Circular Wait)
int request_resources(int NEED[MAX][MAX], int ALLOCATED[MAX][MAX], int AVAILABLE[MAX], int p, int r, int pid) {
    int request[MAX];
    printf("Enter resource request for Process %d:\n", pid + 1);
    for (int i = 0; i < r; i++) {
        scanf("%d", &request[i]);

        // Check if requested more than need
        if (request[i] > NEED[pid][i]) {
            printf("Error: Request exceeds maximum need for resource %c.\n", 'A' + i);
            return 0;
        }

        // Check if requested more than available
        if (request[i] > AVAILABLE[i]) {
            printf("Error: Not enough of resource %c available.\n", 'A' + i);
            return 0;
        }
    }

    // Hold and Wait Prevention: Process can't hold any resource while requesting
    for (int i = 0; i < r; i++) {
        if (ALLOCATED[pid][i] > 0 && request[i] > 0) {
            printf("Hold and Wait violation: Process %d already holds resource %c.\n", pid + 1, 'A' + i);
            return 0;
        }
    }

    // Circular Wait Prevention: Requests must follow resource ordering
    for (int i = 1; i < r; i++) {
        if (request[i] > 0 && request[i - 1] == 0) {
            printf("Circular Wait violation: Process must request in increasing order of resources.\n");
            return 0;
        }
    }

    // Grant request
    for (int i = 0; i < r; i++) {
        AVAILABLE[i] -= request[i];
        ALLOCATED[pid][i] += request[i];
        NEED[pid][i] -= request[i];
    }

    printf("Request granted to Process %d.\n", pid + 1);
    return 1;
}

int main() {
    int p, r;
    printf("Enter the number of processes: ");
    scanf("%d", &p);

    printf("Enter the number of resources: ");
    scanf("%d", &r);

    int AVAILABLE[r], processes[p];
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
    matrixprint(NEED, p, r, processes);

    int choice;
    while (1) {
        printf("\nEnter process number to request resources (1 to %d, 0 to exit): ", p);
        scanf("%d", &choice);
        if (choice == 0) break;
        if (choice < 1 || choice > p) {
            printf("Invalid process number!\n");
            continue;
        }

        request_resources(NEED, ALLOCATED, AVAILABLE, p, r, choice - 1);
    }

    printf("System ended safely under deadlock prevention strategy.\n");
    return 0;
}
