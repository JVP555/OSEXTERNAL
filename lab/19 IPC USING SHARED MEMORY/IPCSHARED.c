#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>

//gcc IPCSHARED.c -o ipc
//./ipc sleep 2


int main(int argc, char *argv[]) {
    struct timeval start_time, end_time;
    pid_t pid;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [arguments]\n", argv[0]);
        return 1;
    }

    gettimeofday(&start_time, NULL);
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process: execute the command
        execvp(argv[1], &argv[1]);
        perror("Error executing command");
        exit(1);
    } else {
        // Parent process: wait and measure time
        wait(NULL);
        gettimeofday(&end_time, NULL);

        long seconds = end_time.tv_sec - start_time.tv_sec;
        long microseconds = end_time.tv_usec - start_time.tv_usec;

        if (microseconds < 0) {
            seconds -= 1;
            microseconds += 1000000;
        }

        printf("Command '%s' took %ld.%06ld seconds to execute.\n", argv[1], seconds, microseconds);
    }

    return 0;
}
