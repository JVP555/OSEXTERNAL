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

    int frames[f], time[f];
    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    int faults = 0, counter = 0;

    printf("\nPage\tFrames\t\tPage Fault\n");
    for (int i = 0; i < n; i++) {
        int hit = 0;

        // Check for hit
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                counter++;
                time[j] = counter; // Update time of access
                break;
            }
        }

        // Miss
        if (!hit) {
            int empty = -1;
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    empty = j;
                    break;
                }
            }

            if (empty != -1) {
                frames[empty] = pages[i];
                counter++;
                time[empty] = counter;
            } else {
                // Find LRU (min time)
                int minTime = time[0], pos = 0;
                for (int j = 1; j < f; j++) {
                    if (time[j] < minTime) {
                        minTime = time[j];
                        pos = j;
                    }
                }
                frames[pos] = pages[i];
                counter++;
                time[pos] = counter;
            }
            faults++;
        }

        // Print
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
