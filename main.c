
/*
 * Main driver code.
 * Has to be fully recoded with a new validating logic and 
 * bootstrap function (wseek_start() or something like that).
 */

#include "webseeker.h"

int 
main (int argc, char* argv[]) 
{
    if (validate_input(argc, argv) == -1) 
        exit(EXIT_FAILURE);
    static struct wseeker scan; /* Create instanse of a struct */


    /* Convert from string to int port number */
    char **buf = NULL;
    const char* host_loc = argv[2];
    int hyphen = str_rm_hyphen(argv[3], &buf);
    if (hyphen < 0) {
        fprintf(stderr, "str_rm_hyphen: error occured");
        return -1;
    }
    int port1i = atoi(buf[0]); 
    int port2i = atoi(buf[1]);

    /* Validate port range */
    if (port1i <= 0 || port2i <= 0 || port1i > port2i) {
        usage(argv);
        return -1;
    }

    /* Adding our validated variables to the static struct */
    scan.host = host_loc;
    scan.mode = argv[2];
    scan.port_from = port1i;
    scan.port_to = port2i;


    int mode = 0;
    int opt;
    while ((opt = getopt(argc, argv, "na")) != -1) {
        switch (opt) {
            case 'n':
                if (mode) {
                    fprintf(stderr, "Error: some options are mutually exclusive, see `man wseek`\n");
                    exit(EXIT_FAILURE);
                }
                mode = 'n';
                if (normal_scan(&scan) == -1) {
                    fprintf(stderr, "Error occured in normal scan mode");
                    exit(EXIT_FAILURE);
                }
                    break;
            case 'a': 
                if (mode) {
                    fprintf(stderr, "Error: some options are mutually exclusive, see `man wseek`\n");
                    exit(EXIT_FAILURE);
                }
                mode = 'a';
                if (ping (&scan) == -1) {
                    fprintf(stderr, "Error occured in ping scan mode");
                    exit(EXIT_FAILURE);
                }
                    break;
            default: 
                    fprintf(stderr, 
                        "Usage: %s [-a | -n] <host> <port_from> <port_to>\n"
                        , argv[0]);
                    exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_SUCCESS);
}

