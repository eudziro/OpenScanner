#ifndef SCANNER_H
#define SCANNER_H


//
// OpenScanner(c) API
//

#ifdef __cplusplus 
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

void scan (int argc, char* argv[]);
void createPortList (int *low, int *high, char*** result);
void usage();


#ifdef __cplusplus 
}
#endif


#endif // SCANNER_H
