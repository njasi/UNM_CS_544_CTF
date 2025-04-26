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
        FILE *f = fopen("/home/inspector/flag.txt", "w");
        if (f)
        {
            fprintf(f, "cs544{my_final_message_goodbye}\n");
            fclose(f);
        }
        exit(0);
    }
}

/**
 * fake job to make the worker threads look busy
 */
void do_work()
{
    size_t current_blocks = 0;
    void *blocks[MAX_BLOCKS];

    while (1)
    {
        // do some busy work
        int total = 0;
        for (int i = 0; i < 1000; i++)
        {
            total += rand() % 100;
        }

        // allocate / free randomly to look real
        if (rand() % 2 == 0 && current_blocks < MAX_BLOCKS)
        {
            size_t size = (rand() % (100 - 4) + 4) * 1024;
            blocks[current_blocks] = malloc(size);

            if (blocks[current_blocks])
            {
                current_blocks++;
            }
        }
        else if (current_blocks > 0)
        {
            size_t idx = rand() % current_blocks;
            free(blocks[idx]);
            blocks[idx] = blocks[current_blocks - 1];
            current_blocks--;
        }

        usleep(100000);
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
