#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


//compile using gcc -pthread MULTI.c -o multi
//./multi 1 2 3 4

int *a;     // Shared array
int n;      // Shared size

void *thread_odd(void *arg) {
    printf("Thread function for odd is running\n");
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 != 0) {
            printf("Odd number is %d\n", a[i]);
        }
    }
    return NULL;
}

void *thread_even(void *arg) {
    printf("Thread function for even is running\n");
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0) {
            printf("Even number is %d\n", a[i]);
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t odd, even;

    if (argc < 2) {
        printf("Usage: %s <list of integers>\n", argv[0]);
        return 1;
    }

    n = argc - 1;
    a = (int *)malloc(n * sizeof(int));  // Allocate memory dynamically

    for (int i = 0; i < n; i++) {
        a[i] = atoi(argv[i + 1]);
    }

    pthread_create(&odd, NULL, thread_odd, NULL);
    pthread_create(&even, NULL, thread_even, NULL);

    pthread_join(odd, NULL);
    pthread_join(even, NULL);

    free(a);  // Free allocated memory
    return 0;
}
