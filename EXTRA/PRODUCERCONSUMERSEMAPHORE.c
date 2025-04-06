#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5   // Size of the buffer
#define PRODUCE_ITEMS 10 // Number of items each producer produces

sem_t empty;     // Semaphore to count empty slots in the buffer
sem_t full;      // Semaphore to count full slots in the buffer
sem_t mutex;     // Semaphore to provide mutual exclusion on the shared buffer

int buffer[BUFFER_SIZE]; // Shared buffer
int in = 0; // Index for producing items
int out = 0; // Index for consuming items

// Producer thread function
void* producer(void* arg) {
    for (int i = 0; i < PRODUCE_ITEMS; i++) {
        sem_wait(&empty);  // Wait for an empty slot
        sem_wait(&mutex);  // Enter critical section

        buffer[in] = i+1;  // Produce an item
        printf("Produced: %d at index %d\n", i+1, in);
        in = (in + 1) % BUFFER_SIZE; // Move to next buffer slot

        sem_post(&mutex);  // Exit critical section
        sem_post(&full);   // Signal that there is a full slot
        sleep(1); // Simulate time to produce an item
    }
    return NULL;
}

// Consumer thread function
void* consumer(void* arg) {
    for (int i = 0; i < PRODUCE_ITEMS; i++) {
        sem_wait(&full);  // Wait for a full slot
        sem_wait(&mutex); // Enter critical section

        int item = buffer[out];  // Consume an item
        printf("Consumed: %d from index %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE; // Move to next buffer slot

        sem_post(&mutex);  // Exit critical section
        sem_post(&empty);  // Signal that there is an empty slot
        sleep(2); // Simulate time to consume an item
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);  // Initially, all slots are empty
    sem_init(&full, 0, 0);             // No full slots initially
    sem_init(&mutex, 0, 1);            // Mutex for mutual exclusion on the buffer

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Join threads (wait for them to finish)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
