#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define NUM_FAKE 20

pid_t fake_pids[NUM_FAKE];
pid_t real_pid;

void start_fakes() {
    for (int i = 0; i < NUM_FAKE; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            execl("/fake", "/fake", NULL);
            exit(1); // if exec fails
        }
        fake_pids[i] = pid;
    }
}

void start_real() {
    pid_t pid = fork();
    if (pid == 0) {
        execl("/real", "/real", NULL);
        exit(1);
    }
    real_pid = pid;
}

int is_real(pid_t pid) {
    return pid == real_pid;
}

void warn_terminal(const char *msg) {
  FILE *fp = popen("who | awk '{print $2}'", "r");
  if (!fp) return;

  char tty[64];
  while (fgets(tty, sizeof(tty), fp)) {
      tty[strcspn(tty, "\n")] = 0; // strip newline
      char path[128];
      snprintf(path, sizeof(path), "/dev/%s", tty);

      FILE *dev = fopen(path, "w");
      if (dev) {
          fprintf(dev, "\n\033[1;31m%s\033[0m\n", msg);
          fclose(dev);
      }
  }
  pclose(fp);
}

void fail_state() {
    warn_terminal("You killed an innocent process :(");
}

int main() {
    start_real();
    start_fakes();

    // monitor children
    while (1) {
        int status;
        pid_t dead = wait(&status);

        if (!is_real(dead)) {
            fail_state();
        } else {
            exit(0);
        }
    }
}
