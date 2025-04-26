#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/prctl.h>

#define MAX_BLOCKS 100

/**
 * handle kill signal
 */
void handle_signal(int sig);


/**
 * handle kill signal
 */
void handle_win(int sig);

/**
 * make fake name & save it to buf
 */
void generate_fake_name(char *buf, size_t len);

/**
 * fake job to make the worker threads look busy
 */
void do_work();