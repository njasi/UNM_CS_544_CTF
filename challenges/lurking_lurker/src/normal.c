#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/prctl.h>
#include "shared.h"

void handle_signal(int sig)
{
    if (sig == SIGTERM)
    {
        FILE *f = fopen("/home/inspector/ouch.txt", "w");
        if (f)
        {
            fprintf(f, "You killed a process you didn't need to\n");
            fclose(f);
        }
        exit(0);
    }
}

int main(int argc, char *argv[])
{
    char fake_name[64];
    generate_fake_name(fake_name, sizeof(fake_name));


    prctl(PR_SET_NAME, fake_name);
    memset(argv[0], 0, strlen(argv[0]));
    strncpy(argv[0], fake_name, strlen(fake_name));

    // signal handler
    signal(SIGTERM, handle_signal);
    do_work();

    return 0;
}
