#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main() {
   
    clock_t main_start = clock();

    pid_t pid1 = fork();

    if (pid1 < 0) {
        printf("Error fork 1");
        return 1;
    }

    if (pid1 == 0) {
        // child process 1
        clock_t child1_start = clock();

        clock_t child1_end = clock();
        double elapsed_ms = ((double)(child1_end - child1_start) / CLOCKS_PER_SEC) * 1000.0;

        printf("[child 1] PID: %d, Parent PID: %d, Execurion time: %.2f мс\n", getpid(), getppid(), elapsed_ms);
        

        exit(0);
    }


    pid_t pid2 = fork();

    if (pid2 < 0) {
        printf("Error fork 2");
        return 1;
    }

    if (pid2 == 0) {
        //child process 2
        clock_t child2_start = clock();

        clock_t child2_end = clock();
        double elapsed_ms = ((double)(child2_end - child2_start) / CLOCKS_PER_SEC) * 1000.0;

        printf("[Child 2] PID: %d, Parent PID: %d, Execution time: %.2f мс\n", getpid(), getppid(), elapsed_ms);
        
        exit(0);
    }

    // waiting for the children processes
    wait(NULL);
    wait(NULL);

    clock_t main_end = clock();
    double main_elapsed_ms = ((double)(main_end - main_start) / CLOCKS_PER_SEC) * 1000.0;

    printf("[Main]   PID: %d, Parent PID: %d, Execution time: %.2f мс\n", getpid(), getppid(), main_elapsed_ms);

    return 0;
}
