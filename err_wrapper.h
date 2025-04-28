#ifndef WS_ERRWRAPER
#define WS_ERRWRAPER

#include "c.h"

/* Prints formatted message to stderr, and terminates the process */
void err_sys(const char* fmt, ...);

/* Application level errors (i.e. those, which is not setting errno variable)
 * can be handled with this function.
 * Prints fmt message to stderr, and terminates the process */
void err_app(const char* fmt, ...);

void err_doit(int errno_flag, const char* fmt, va_list ap);

#endif /* WS_ERRWRAPER */
