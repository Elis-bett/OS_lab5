#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// limitations for the command length
#define MAX_LINE 80       
#define MAX_ARGS 10       

int main() {
    char input[MAX_LINE];
    char *args[MAX_ARGS];

    setvbuf(stdout, NULL, _IONBF, 0);

    while (1) {
        printf("myshell> ");

        // reading the input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; 
        }

        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0) {
            continue;
        }

        // if "exit" -> than exit from the shell
        if (strcmp(input, "exit") == 0) {
            break;
        }

        int i = 0;
        args[i] = strtok(input, " ");
        while (args[i] != NULL && i < MAX_ARGS - 1) {
            i++;
            args[i] = strtok(NULL, " ");
        }
        args[i] = NULL; 

        // process for executing a command
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork error");
            continue;
        }

        if (pid == 0) {
            // child code
            if (execvp(args[0], args) < 0) {
                perror("Command execution error");
                exit(1);
            }
        } else {
            // parent code
            // do not call wait() -> the command goes in parallel in the background

            // cleaing up zombi-processes
            while (waitpid(-1, NULL, WNOHANG) > 0);
        }
    }

    return 0;
}
