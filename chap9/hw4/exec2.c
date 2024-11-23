#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXARG 100

int main() {
    char line[1024];
    char *args[MAXARG];
    char *token, *saveptr;
    int background;

    while (1) {
        printf("Pls input cmd : ");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            continue;
        }

        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, "exit") == 0) {
            printf("Exit\n");
            break;
        }

        if (line[0] == '\0') {
            continue;
        }

        background = 0;
        if (line[strlen(line) - 1] == '&') {
            background = 1;
            line[strlen(line) - 1] = '\0';
        }

        token = strtok_r(line, " ", &saveptr);
        int i = 0;
        while (token != NULL) {
            args[i++] = token;
            token = strtok_r(NULL, " ", &saveptr);
        }
        args[i] = NULL;

        printf("Parent process start\n");

        pid_t pid = fork();
        if (pid == -1) {
            printf("Parent process end\n");
            continue;
        }

        if (pid == 0) {
            printf("child process start\n");
            execvp(args[0], args);
            exit(1);
        } else {
            if (!background) {
                wait(NULL);
            }
            printf("Parent process end\n");
        }
    }

    return 0;
}

