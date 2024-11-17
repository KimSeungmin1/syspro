#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXARG 100

int main() 
{
    
char line[1024];
char *args[MAXARG];
char *token;
int background;

    while(1) {
        printf("Pls input cmd : ");

    if (fgets(line, sizeof(line), stdin) == NULL) {
            perror("Failed");
            exit(1);
        }

line[strcspn(line, "\n")] = 0;

    if (line[0] == '\0') {
        continue;
    }

background = 0;
    if (line[strlen(line) - 1] == '&') {
        background = 1;
        line[strlen(line) - 1] = '\0'; 
    }

token = strtok(line, " ");
int i = 0;

    while(token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
    }
    
args[i] = NULL;
pid_t pid = fork();
        
        if (pid == -1) {
            perror("fork fail");
            exit(1);
        }
        
        if (pid == 0) { // child
            if (execvp(args[0], args) == -1) {
                perror("Execute Failed¨");
                exit(1);
            }
        } 
        else { // Parent
            if (!background) {
                wait(NULL);
            }
        }
    }
    return 0;
}

