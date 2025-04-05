#include <stdio.h>
#include <stdlib.h>

#define MAX_TRACK 199  // Highest track number
#define MIN_TRACK 0    // Lowest track number

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

    int request[n + 2]; // +2 for head and edge
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the direction (0 for left, 1 for right): ");
    scanf("%d", &direction);  // 0 = toward lower tracks, 1 = higher tracks

    printf("Enter the sequence of disk requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    // Add head and end points to the request list
    request[n] = head;
    if (direction == 1)
        request[n + 1] = MAX_TRACK;
    else
        request[n + 1] = MIN_TRACK;

    n += 2;

    // Sort the requests
    sort(request, n);

    // Find index of current head in the sorted list
    int pos;
    for (int i = 0; i < n; i++) {
        if (request[i] == head) {
            pos = i;
            break;
        }
    }

    printf("\nOrder of servicing (SCAN):\n");
    int movement = 0;
    int current = head;
    printf("%d", head);

    if (direction == 1) {  // Moving towards higher tracks
        for (int i = pos + 1; i < n; i++) {
            printf(" -> %d", request[i]);
            movement += abs(current - request[i]);
            current = request[i];
        }
        for (int i = pos - 1; i >= 0; i--) {
            printf(" -> %d", request[i]);
            movement += abs(current - request[i]);
            current = request[i];
        }
    } else {  // Moving towards lower tracks
        for (int i = pos - 1; i >= 0; i--) {
            printf(" -> %d", request[i]);
            movement += abs(current - request[i]);
            current = request[i];
        }
        for (int i = pos + 1; i < n; i++) {
            printf(" -> %d", request[i]);
            movement += abs(current - request[i]);
            current = request[i];
        }
    }

    printf("\n\nTotal head movement: %d\n", movement);
    printf("Average head movement: %.2f\n", (float)movement / (n - 2));

    return 0;
}
