#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Using: %s <numb of iterations>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Invalid n\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        // clone the current process
        // the number of processes becomes 2 times more
        fork();
 
        sleep(5);
    }

    return 0;
}
