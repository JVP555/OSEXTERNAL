#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, head, direction;
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int request[n];
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    printf("Enter the sequence of disk requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    // Sort the requests
    sort(request, n);

    // Find index of current head in the sorted list
    int pos = 0;
    for (int i = 0; i < n; i++) {
        if (head < request[i]) {
            pos = i;
            break;
        }
    }

    printf("\nOrder of servicing (LOOK):\n");
    int movement = 0;
    int current = head;
    printf("%d", head);

    if (direction == 1) {
        // Go right first
        for (int i = pos; i < n; i++) {
            printf(" -> %d", request[i]);
            movement += abs(current - request[i]);
            current = request[i];
        }
        // Then go left
        for (int i = pos - 1; i >= 0; i--) {
            printf(" -> %d", request[i]);
            movement += abs(current - request[i]);
            current = request[i];
        }
    } else {
        // Go left first
        for (int i = pos - 1; i >= 0; i--) {
            printf(" -> %d", request[i]);
            movement += abs(current - request[i]);
            current = request[i];
        }
        // Then go right
        for (int i = pos; i < n; i++) {
            printf(" -> %d", request[i]);
            movement += abs(current - request[i]);
            current = request[i];
        }
    }

    printf("\n\nTotal head movement: %d\n", movement);
    printf("Average head movement: %.2f\n", (float)movement / n);

    return 0;
}
