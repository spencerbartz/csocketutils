#ifndef LOGGERUTILS_H
#define LOGGERUTILS_H

#if __STDC__
#  ifndef NOPROTOS
#    define PARAMS(args)      args
#  endif
#endif
#ifndef PARAMS
#  define PARAMS(args)        ()
#endif

extern void log_error PARAMS((char *file, int line, const char *format, ...));
extern void log_warning PARAMS((char *file, int line, const char *format, ...));
extern void log_debug PARAMS((char *file, int line, const char *format, ...));
#endif
