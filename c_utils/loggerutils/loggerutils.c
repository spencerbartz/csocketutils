#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <stdarg.h>

#include "loggerutils.h"

void log_error(char *file, int line, const char *format, ...)
{
    char * newFormat;
	va_list	args;
	va_start(args, format);
    
    fprintf(stderr, "FILE: %s LINE: %d ERROR: ", file, line);
	
    if(format[strlen(format) - 1] != 10) {
        newFormat = malloc((strlen(format) + 1) * sizeof(char));
        strncat(newFormat, format, strlen(format));
        strncat(newFormat, "\n", 1);
	}
	else {
        newFormat = (char *) format;
    }

	vfprintf(stderr, newFormat, args);
	va_end(args);
}

void log_warning(char *file, int line, const char *format, ...)
{
    char * newFormat;
    va_list	args;
    va_start(args, format);
    
    fprintf(stderr, "FILE: %s LINE: %d WARNING: ", file, line);
	
    if(format[strlen(format) - 1] != 10) {
        newFormat = malloc((strlen(format) + 1) * sizeof(char));
		strncat(newFormat, format, strlen(format));
		strncat(newFormat, "\n", 1);
	}
	else {
        newFormat = (char *) format;
    }

	vfprintf(stderr, newFormat, args);
	va_end(args);
}

void log_debug(char *file, int line, const char *format, ...)
{
    char * newFormat;
	va_list	args;
	va_start(args, format);
	
    fprintf(stderr, "FILE: %s LINE: %d DEBUG: ", file, line);
	
	if(format[strlen(format) - 1] != 10) {
		newFormat = malloc((strlen(format) + 1) * sizeof(char));
		strncat(newFormat, format, strlen(format));
		strncat(newFormat, "\n", 1);
	}
	else {
        newFormat = (char *) format;
    }

	vfprintf(stderr, newFormat, args);
	va_end(args);
}
