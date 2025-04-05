#include <stdio.h>

#define MAX 100

int main() {
    int m, n;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    int blockSize[MAX], blockAllocated[MAX];
    for (int i = 0; i < m; i++) {
        printf("Enter size of block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
        blockAllocated[i] = -1;  // -1 = free
    }

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int processSize[MAX], processBlock[MAX];
    for (int i = 0; i < n; i++) {
        printf("Enter size of process %d: ", i + 1);
        scanf("%d", &processSize[i]);
        processBlock[i] = -1;  // -1 = not allocated
    }

    // 🔁 Worst Fit Allocation
    for (int i = 0; i < n; i++) {
        int worst = -1;
        for (int j = 0; j < m; j++) {
            if (blockAllocated[j] == -1 && blockSize[j] >= processSize[i]) {
                if (worst == -1 || blockSize[j] > blockSize[worst]) {
                    worst = j;
                }
            }
        }
        if (worst != -1) {
            processBlock[i] = worst;
            blockAllocated[worst] = i;
        }
    }

    // Result Table
    printf("\nProcess\tSize\tAllocated Block\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t", i + 1, processSize[i]);
        if (processBlock[i] != -1)
            printf("Block %d\n", processBlock[i] + 1);
        else
            printf("Not Allocated\n");
    }

    // Gantt Chart Style Block Status
    printf("\nMemory Block Status:\n ");
    for (int i = 0; i < m; i++) printf("--------");
    printf("\n");
    for (int i = 0; i < m; i++) {
        if (blockAllocated[i] != -1)
            printf("| P%d\t", blockAllocated[i] + 1);
        else
            printf("| Free\t");
    }
    printf("|\n ");
    for (int i = 0; i < m; i++) printf("--------");
    printf("\n");

    return 0;
}
