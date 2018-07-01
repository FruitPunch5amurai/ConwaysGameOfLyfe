#include "BasicLogger.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#undef X
#define X(a,b) b,
char *log_name[] = {
	LOG_TABLE
};
#undef X

void _blog(char *f, int l, LogType type, char *msg,...)
{
	va_list ap;
	va_start(ap, msg);
	fprintf(stdout, "{%s} %s:Line %i: ", log_name[type], f, l);
	vfprintf(stdout, msg, ap);
	fprintf(stdout, "\n");
	va_end(ap);
	fprintf(stdout, "\n");
}