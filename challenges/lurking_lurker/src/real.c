#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/prctl.h>

#define SHM_KEY 12345
#define TARGET_SHR_SIZE 1280
/**
 * make an allocate shared memory method
 * so we can look the same as the other workers
 */

void *allocate_shared_memory(size_t size)
{
    int shmid = shmget(SHM_KEY, size, IPC_CREAT | 0666); // Create shared memory segment
    if (shmid == -1)
    {
        perror("shmget failed");
        exit(1);
    }

    void *shm_ptr = shmat(shmid, NULL, 0); // Attach the shared memory
    if (shm_ptr == (void *)-1)
    {
        perror("shmat failed");
        exit(1);
    }

    return shm_ptr;
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

    // allocate shr memory to look like the other workers
    size_t shm_size = TARGET_SHR_SIZE * 1024;
    void *shm_ptr = allocate_shared_memory(shm_size);
    memset(shm_ptr, 0, shm_size);

    // signal handler
    signal(SIGTERM, handle_signal);
    while (1)
    {
        sleep(60);
    }

    return 0;
}
