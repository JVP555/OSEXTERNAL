#include <stdio.h>

#define MAX 100

int main() {
    int n, f;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[MAX];
    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &f);

    int frames[f];
    int front = 0, rear = 0, count = 0, faults = 0;

    for (int i = 0; i < f; i++) frames[i] = -1;

    printf("\nPage\tFrames\t\tPage Fault\n");
    for (int i = 0; i < n; i++) {
        int hit = 0;

        // Check for hit
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                break;
            }
        }

        // Miss (Page Fault)
        if (!hit) {
            frames[rear] = pages[i];
            rear = (rear + 1) % f;
            if (count < f) count++;
            else front = (front + 1) % f;
            faults++;
        }

        // Print status
        printf("%d\t", pages[i]);
        for (int j = 0; j < f; j++) {
            if (frames[j] != -1) printf("%d ", frames[j]);
            else printf("- ");
        }
        printf("\t\t%s\n", hit ? "No" : "Yes");
    }

    printf("\nTotal Page Faults: %d\n", faults);

    return 0;
}
