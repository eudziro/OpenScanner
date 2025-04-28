
/*
 * WebSeeker Main Header file
 *
 * Information about 
 */

#ifndef WSEEKER
#define WSEEKER

#include "c.h"
#include "err_wrapper.h"


#ifdef __cplusplus 
extern "C" {
#endif

struct wseeker {
    const char* host;
    const char* mode;
    int port_from;
    int port_to;
    uint32_t flags;
};

#define PING_PKT_S 64
#define PING_SLEEP_RATE 1000000

int ping (struct wseeker* pointer);

int str_rm_hyphen(char* buf, char*** buf_output);

int normal_scan (struct wseeker* pointer);

int create_port_list (int *low, int *high, char*** result);

void usage(char *argv[]);

void help_function(char *argv[]);

/* Checks input for a validness */
int validate_input(int argc, char* argv[]);

int str_rm_hyphen(char* buf, char*** buf_output);

#ifdef __cplusplus 
}
#endif


#endif /* WSEEKER */

