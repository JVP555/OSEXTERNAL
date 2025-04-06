#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>



//compile using gcc -pthread DININGSEMAPHORE.c -o din



#define N 5 // number of philosophers

sem_t forks[N]; // one semaphore per fork

void *philosopher(void *arg) {
    int id = *(int *)arg;

    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(1);

        // Pick up left and right forks
        sem_wait(&forks[id]); // left fork
        sem_wait(&forks[(id + 1) % N]); // right fork

        printf("Philosopher %d is eating\n", id);
        sleep(2);

        // Put down forks
        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % N]);

        printf("Philosopher %d finished eating and is thinking again.\n", id);
    }

    return NULL;
}

int main() {
    pthread_t tid[N];
    int ids[N];

    // Initialize semaphores for forks
    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &ids[i]);
    }

    // Join threads (optional for infinite loops)
    for (int i = 0; i < N; i++) {
        pthread_join(tid[i], NULL);
    }

    // Destroy semaphores
    for (int i = 0; i < N; i++) {
        sem_destroy(&forks[i]);
    }
    return 0;
}
