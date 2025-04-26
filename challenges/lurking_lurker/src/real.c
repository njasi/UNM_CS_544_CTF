#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/prctl.h>
// note that we don't need all these libs, but we
// include them so we look the same as the other workers


void handle_signal(int sig)
{
    if (sig == SIGTERM)
    {
        FILE *f = fopen("/home/inspector/flag.txt", "w");
        if (f)
        {
            fprintf(f, "cs544{my_final_message_goodbye}\n");
            fclose(f);
        }
        exit(0);
    }
}

int main(int argc, char *argv[])
{
    pid_t pid = fork();
    if (pid > 0)
        exit(0);

    // become session leader & hide
    setsid();
    chdir("/");

    // close fds
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);

    // fake args & hide
    prctl(PR_SET_NAME, "kworker/0:1");
    memset(argv[0], 0, strlen(argv[0]));
    strcpy(argv[0], "kworker/0:1");

    // signal handler
    signal(SIGTERM, handle_signal);
    while (1)
    {
        sleep(60);
    }

    return 0;
}
