#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_CMD_LEN 1024

void execute_command(char *cmd) {
    char *args[10];
    int i = 0;
    char *token = strtok(cmd, " ");

    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (fork() == 0) {
        execvp(args[0], args);
        perror("Command execution failed");
        exit(1);
    } else {
        wait(NULL);
    }
}

void handle_redirection(char *cmd) {
    char *input = NULL, *output = NULL;

    char *in_ptr = strstr(cmd, "<");
    if (in_ptr) {
        *in_ptr = '\0';
        input = strtok(in_ptr + 1, " ");
    }

    char *out_ptr = strstr(cmd, ">");
    if (out_ptr) {
        *out_ptr = '\0';
        output = strtok(out_ptr + 1, " ");
    }

    if (fork() == 0) {
        if (input) {
            int fd = open(input, O_RDONLY);
            if (fd < 0) {
                perror("Failed to open input file");
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }

        if (output) {
            int fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                perror("Failed to open output file");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        execute_command(cmd);
        exit(0);
    } else {
        wait(NULL);
    }
}

void shell_loop() {
    char cmd[MAX_CMD_LEN];

    while (1) {
        printf("[shell] ");
        fflush(stdout);

        if (!fgets(cmd, sizeof(cmd), stdin)) break;
        cmd[strcspn(cmd, "\n")] = '\0';

        if (strchr(cmd, '&')) {
            if (fork() == 0) {
                cmd[strlen(cmd) - 1] = '\0';
                execute_command(cmd);
                exit(0);
            }
            continue;
        }

        char *part = strtok(cmd, ";");
        while (part) {
            if (strchr(part, '<') || strchr(part, '>')) {
                handle_redirection(part);
            } else {
                execute_command(part);
            }
            part = strtok(NULL, ";");
        }
    }
}

int main() {
    shell_loop();
    return 0;
}


