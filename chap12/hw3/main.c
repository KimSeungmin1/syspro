#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int pipefd[2];
    pipe(pipefd);

    if (fork() == 0) {
        if (argc < 3) {
            execlp("ls", "ls", NULL);
        } else {
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[0]);
            close(pipefd[1]);
            execlp(argv[1], argv[1], NULL);
        }
        exit(1);
    }

    if (fork() == 0) {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        if (argc < 3) {
            execlp("wc", "wc", NULL);
        } else {
            execlp(argv[2], argv[2], NULL);
        }
        exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    wait(NULL);
    wait(NULL);

    return 0;
}

