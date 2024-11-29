#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void timeout(int sig)
{
    if (sig == SIGALRM) {
        puts("Wake up\n");
        alarm(5);
    }
}

void keycontrol(int sig)
{
    if (sig == SIGINT) {
        puts("CTRL+C pressed. Exiting");
        exit(0);
    }
}

int main()
{
    struct sigaction sa_alarm, sa_int;

    sa_alarm.sa_handler = timeout;
    sigemptyset(&sa_alarm.sa_mask);
    sa_alarm.sa_flags = 0;
    sigaction(SIGALRM, &sa_alarm, NULL);

    sa_int.sa_handler = keycontrol;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);

    alarm(5);

    short i = 0;
    while (1) {
        sleep(1);
        i++;
        printf("%d second\n", i);
    }

    return 0;
}

