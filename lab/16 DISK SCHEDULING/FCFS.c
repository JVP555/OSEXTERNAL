#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head;
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int request[n], order[n], movement = 0;

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the sequence of disk requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    printf("\nOrder of servicing (FCFS):\n");
    printf("%d", head);  // starting head position
    int current = head;

    for (int i = 0; i < n; i++) {
        printf(" -> %d", request[i]);
        movement += abs(current - request[i]);
        current = request[i];
    }

    printf("\n\nTotal head movement: %d\n", movement);
    printf("Average head movement: %.2f\n", (float)movement / n);
    return 0;
}
