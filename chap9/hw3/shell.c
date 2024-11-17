#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_CMD_LEN 100

void execute_command(char *cmd) {
	char *args[10];
	int i = 0;
	char *token = strtok(cmd, " ");

	while (token != NULL) {
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;

	pid = fork();

	if (pid == 0){
		execvp(
