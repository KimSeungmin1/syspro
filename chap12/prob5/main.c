#include <stdio.h>
#define MAXLINE 100

int main(int argc, char* argv[])
{
	char line[MAXLINE];
	FILE *fpin;
	if ((fpin = popen(argv[1], "r")) == NULL) {
		perror("popen error");
		return 1;
	}
	printf("The result from child process\n");
	while (fgets(line, MAXLINE, fpin))
		fputs(line, stdout);
	pclose(fpin);
	return 0;
}
