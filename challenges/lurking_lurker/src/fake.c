#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/prctl.h>


#define MAX_BLOCKS 100

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
        FILE *f = fopen("/home/inspector/ouch.txt", "w");
        if (f)
        {
            fprintf(f, "You killed a process you didn't need to\n");
            fclose(f);
        }
        exit(0);
    }
}

void generate_fake_name(char *buf, size_t len)
{
    srand(time(NULL) ^ getpid());
    int cpu = rand() % 16;
    int id = rand() % 100;

    snprintf(buf, len, "kworker/%d:%d", cpu, id);
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
    // call things so they get linked in
    filler_functions();

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
