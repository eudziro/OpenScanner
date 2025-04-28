
#include "webseeker.h"

void 
help_function(char *argv[]) {
    fprintf(stderr, 
            "Usage: %s [-a | -n] <host> <port_from>-<port_to>\n \
            \n \
            General info:\n \
                MODES\n\
                    anon       SYN scan in anonimous mode (host won't know)\n \
                    normal     scan in normal mode\n \
                HOST\n\
                    Host's IP address in IPv4 or IPv6 format string\n\
                    could be also in domain-name format, like \"example.com\".\n\
                PORTS\n\
                    Desired port range scan. For example \"16-100\".\n\n\n"
                    
            , argv[0]);
}

void
usage(char *argv[]) {
    fprintf(stderr, 
            "Usage: %s [-a | -n] <host> <port_from>-<port_to>\n \
             Type \"--help\" for more\n"
             , argv[0]);

}

