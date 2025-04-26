#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h> //
#include <time.h> //
#include <sys/prctl.h>
// note that we don't need all these libs, but we
// include them so we look the same as the other workers

void filler_functions()
{
    srand(time(NULL));
    rand();

    char buf1[16] = "hello";
    char buf2[16];
    strcpy(buf2, buf1);
    memset(buf2, 0, sizeof(buf2));
    strcmp(buf1, buf2);

    getpid();
    getppid();
    sleep(0);

    signal(SIGUSR1, SIG_IGN);

    prctl(PR_GET_NAME);
}


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
    // call things so they get linked in
    filler_functions();

    pid_t pid = fork();
    if (pid > 0)
        exit(0);

    setsid();
    chdir("/");


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
