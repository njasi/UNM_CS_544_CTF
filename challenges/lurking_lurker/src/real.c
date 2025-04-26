#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/prctl.h>
#include <signal.h>
#include <sys/resource.h>
#include <sys/types.h>

#define TARGET_SHR_KB 1280 // target SHR in KiB
#define LIBRARY_PATH "/lib/x86_64-linux-gnu/libm.so.6" // math lib ig

void *loaded_libs[1024];
int loaded_count = 0;


size_t get_process_shared_memory_kb()
{
    FILE *f = fopen("/proc/self/statm", "r");
    if (!f)
        return 0;

    long size, resident, share;
    fscanf(f, "%ld %ld %ld", &size, &resident, &share);
    fclose(f);

    long page_size_kb = sysconf(_SC_PAGESIZE) / 1024;
    return share * page_size_kb;
}

void inflate_shared_memory()
{
    size_t shr_kb = get_process_shared_memory_kb();
    printf("[*] Initial SHR: %zu KB\n", shr_kb);

    while (shr_kb < TARGET_SHR_KB && loaded_count < 1024)
    {
        void *handle = dlopen(LIBRARY_PATH, RTLD_LAZY);
        if (!handle)
        {
            printf("[!] dlopen failed: %s\n", dlerror());
            break;
        }
        loaded_libs[loaded_count++] = handle;
        shr_kb = get_process_shared_memory_kb();
        printf("[+] Loaded %d libraries, SHR now: %zu KB\n", loaded_count, shr_kb);
        usleep(10000);
    }

    printf("[*] Final SHR: %zu KB\n", shr_kb);
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
    inflate_shared_memory();

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
