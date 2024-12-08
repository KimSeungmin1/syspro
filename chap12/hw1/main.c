#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() 
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("Failed");
        return 1;
    } else if (pid == 0) {
       
		printf("Recv: [%d] Hello from PID %d\n", getpid(), getppid());
    } else {
        printf("Send: [%d] Hello from PID %d\n", getpid(), pid);
    }

    return 0;
}

