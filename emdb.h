/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifndef EMDB_H
#define EMDB_H

/* This prevents conflicts whether stdlib.h is included again after or before
 * emdb.h. Ugly hack, I know. */
#include <stdlib.h>

#define EMDB_RED     "\033[1m\033[31m"
#define EMDB_GREEN   "\033[1m\033[32m"
#define EMDB_YELLOW  "\033[1m\033[33m"
#define EMDB_BLUE    "\033[1m\033[34m"
#define EMDB_PURPLE  "\033[1m\033[34m"
#define EMDB_RESET   "\033[0m"

void emdb_mem_file(void *ptr, size_t size, const char *file, int line);
void *emdb_malloc(size_t size, const char *file, int line);
void *emdb_calloc(size_t count, size_t size, const char *file, int line);
void *emdb_realloc(void *ptr, size_t size, const char *file, int line);
void emdb_free(void *ptr, const char *file, int line);
void emdb_hexdump(char *p, int s);

#ifndef EMDB_SOURCE
#define malloc(s) emdb_malloc(s, __FILE__, __LINE__)
#define calloc(c, s) emdb_calloc(c, s, __FILE__, __LINE__)
#define realloc(p, s) emdb_realloc(p, s, __FILE__, __LINE__)
#define free(p) emdb_free(p, __FILE__, __LINE__)
#endif

/* dumps */
#define DUMPINT(x, d) do {                                                     \
        printf("[%s:%d] #%s\nVALUE: %d | SIZE: %lu\n",                         \
               __FILE__, __LINE__, #x, x, sizeof(x));                          \
        if (d) emdb_hexdump((char *)(&x), sizeof(int));                        \
        printf("\n");                                                          \
} while (0)
#define DUMPSTR(x, d) do {                                                     \
        printf("[%s:%d] #%s\nVALUE: %s | SIZE: %lu | LENGTH: %lu\n",           \
               __FILE__, __LINE__, #x, x, sizeof(x), strlen(x));               \
        if (d) emdb_hexdump(x, strlen(x));                                     \
        printf("\n");                                                          \
} while (0)

/* debug messages */
#define emdb_debug(tag, color, msg) printf(color "[" tag ":%s:%d] " msg EMDB_RESET "\n", __FILE__, __LINE__)
#define DEBUG(...)   emdb_debug("INFO",    EMDB_BLUE,   __VA_ARGS__)
#define DEBUGW(...)  emdb_debug("WARNING", EMDB_YELLOW, __VA_ARGS__)
#define DEBUGE(...)  emdb_debug("ERROR",   EMDB_RED,    __VA_ARGS__)
#define DEBUGOK(...) emdb_debug("OK",      EMDB_GREEN,  __VA_ARGS__)

/* time */
#define SLEEP(t)       do { struct timespec tv = { .tv_sec = t, .tv_nsec = 0         }; nanosleep(&tv, &tv); } while (0)
#define SLEEP_MILI(t)  do { struct timespec tv = { .tv_sec = 0, .tv_nsec = t*1000000 }; nanosleep(&tv, &tv); } while (0)
#define SLEEP_MICRO(t) do { struct timespec tv = { .tv_sec = 0, .tv_nsec = t*1000    }; nanosleep(&tv, &tv); } while (0)
#define SLEEP_NANO(t)  do { struct timespec tv = { .tv_sec = 0, .tv_nsec = t         }; nanosleep(&tv, &tv); } while (0)

#endif
