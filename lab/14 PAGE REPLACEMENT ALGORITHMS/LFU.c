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

    int frames[f], freq[f];
    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        freq[i] = 0;
    }

    int faults = 0;

    printf("\nPage\tFrames\t\tPage Fault\n");
    for (int i = 0; i < n; i++) {
        int hit = 0;

        // Check for hit
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                freq[j]++;
                hit = 1;
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
                freq[empty] = 1;
            } else {
                // Find LFU (lowest freq)
                int min = freq[0], pos = 0;
                for (int j = 1; j < f; j++) {
                    if (freq[j] < min) {
                        min = freq[j];
                        pos = j;
                    }
                }
                frames[pos] = pages[i];
                freq[pos] = 1;
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
