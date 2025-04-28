
#include "err_wrapper.h"

/* I could have use the perror + exit conjunction, but sometimes 
 * you want to supply additional argument to fmt string */

void
err_sys (const char* fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, fmt, ap);
    va_end(ap);

    exit(EXIT_FAILURE);
}

void 
err_app (const char* fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(0, fmt, ap);
    va_end(ap);

    exit(EXIT_FAILURE);
}

#define MAXLINE 100

void
err_doit (int errno_flag, const char* fmt, va_list ap)
{
    int errno_save = errno;
    char buf[MAXLINE];

    vsprintf(buf, fmt, ap); /* copy fmt to buffer, for convinience */

    if (errno_flag) 
    {
        sprintf(buf+strlen(buf), ": %s\n\
                code error: \"%d\"", strerror(errno_save), errno_save);
    } 
    else
    {

        sprintf(buf+strlen(buf), ": %s\n", "error has been encountered\r\n");
    }
    strcat(buf, "\n");
    vfprintf(stderr, buf, ap);
    return;
}



