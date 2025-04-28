
/*
 * Wrapper functions for some work to do? 
 */

#include "c.h"

int
str_rm_hyphen(char* buf, char*** buf_output) 
{
    int i = 0;
    int count = 0;

    *buf_output = malloc(2 * sizeof (char *)); /* Allocate enough memory for two pointers */
    if (*buf_output == NULL) {
        perror("malloc");
        return -1;
    }

    /* Allocate enough space for number, in each pointer */

    (*buf_output)[0] = malloc(sizeof (char) * 8);
    if ((*buf_output)[0] == NULL) {
        perror("malloc");
        return -1;
    }
    
    (*buf_output)[1] = malloc(sizeof (char) * 8);
    if ((*buf_output)[1] == NULL) {
        perror("malloc");
        return -1;
    }

    while (buf[i] != '\0') /* Searching hyphen and replacing it with '\0' */
    {
        if (buf[i] == '-')
        {
            buf[i] = '\0';
            count++;        /* Count is for error catching */
        }
        i++;
    }
    if (count > 1) { return -1; }


    strcpy((*buf_output)[0], buf);
    strcpy((*buf_output)[1], buf+strlen(buf)+1);

    return 0;
}




