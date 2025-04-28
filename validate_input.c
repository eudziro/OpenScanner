
#include "webseeker.h"

int
validate_input(int argc, char* argv[]) 
{
    /* Prints the usage if arguments are bad. And prints specialized help
     * function, if user asks. */
    if (argc < 2 || argc > 5) 
    {
        if (argc < 2) 
            usage(argv);
            return -1;

        if (strcmp(argv[1], "--help") == 0)
        {
            help_function(argv);
            return -1;
        }
    }
        
    return 0;
}

