#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/prctl.h>

#define MAX_BLOCKS 100

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