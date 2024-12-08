#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#define BUFFER_SIZE 256

int main() {
    int pipefd[2];
    char buffer[BUFFER_SIZE];
    if (pipe(pipefd) == -1) {
        perror("failed");
        return 1;
    }

    if (fork() == 0) { 
        close(pipefd[0]);
        printf("input string: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        write(pipefd[1], buffer, strlen(buffer) + 1);
        close(pipefd[1]);
        exit(0);
    }

    if (fork() == 0) {
        close(pipefd[1]);
        read(pipefd[0], buffer, BUFFER_SIZE);
        close(pipefd[0]);
        for (int i = 0; buffer[i]; i++) buffer[i] = toupper(buffer[i]);
        printf("%s\n", buffer);
        exit(0);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}

