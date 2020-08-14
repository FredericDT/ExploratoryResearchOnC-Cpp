#include <stdio.h>
#include <time.h>

#define eprintf(pattern, ...) fprintf(stderr, "%ld %s:%d: "pattern, time(NULL), __FILE__, __LINE__, ## __VA_ARGS__)

#define iprintf(pattern, ...) fprintf(stdout, "%ld %s:%d: "pattern, time(NULL), __FILE__, __LINE__, ## __VA_ARGS__)

#define EXIT_ERRNO(exp) if ((exp)) { eprintf("%s\n", strerror(errno)); exit(errno); }
