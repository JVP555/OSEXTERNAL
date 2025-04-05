#include <stdio.h>
#include <stdlib.h>

#define MAX_TRACK 199  // Maximum disk track
#define MIN_TRACK 0    // Minimum disk track

// Bubble sort function
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

    int request[n + 3];  // +3: requests + head + boundary track + wrap-around
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the direction (0 for left, 1 for right): ");
    scanf("%d", &direction);  // 0 = towards MIN, 1 = towards MAX

    printf("Enter the sequence of disk requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    // Add current head and boundary track based on direction
    request[n] = head;
    if (direction == 1) {
        request[n + 1] = MAX_TRACK;
        request[n + 2] = MIN_TRACK;  // wrap-around to start
    } else {
        request[n + 1] = MIN_TRACK;
        request[n + 2] = MAX_TRACK;  // wrap-around to end
    }

    n += 3;  // total elements now

    // Sort all
    sort(request, n);

    // Find index of head in sorted array
    int pos;
    for (int i = 0; i < n; i++) {
        if (request[i] == head) {
            pos = i;
            break;
        }
    }

    int movement = 0, current = head;
    printf("\nOrder of servicing (C-SCAN):\n");
    printf("%d", current);

    if (direction == 1) {  // Moving to higher tracks first
        // Service all to the right
        for (int i = pos + 1; i < n; i++) {
            printf(" -> %d", request[i]);
            movement += abs(current - request[i]);
            current = request[i];
        }
        // Wrap around (head jumps from MAX to MIN)
        for (int i = 0; i < pos; i++) {
            printf(" -> %d", request[i]);
            movement += abs(current - request[i]);
            current = request[i];
        }
    } else {  // Moving to lower tracks first
        // Service all to the left
        for (int i = pos - 1; i >= 0; i--) {
            printf(" -> %d", request[i]);
            movement += abs(current - request[i]);
            current = request[i];
        }
        // Wrap around (head jumps from MIN to MAX)
        for (int i = n - 1; i > pos; i--) {
            printf(" -> %d", request[i]);
            movement += abs(current - request[i]);
            current = request[i];
        }
    }

    printf("\n\nTotal head movement: %d\n", movement);
    printf("Average head movement: %.2f\n", (float)movement / (n - 3));  // excluding head, MIN, MAX

    return 0;
}
