/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <string.h>

#ifndef EMDB_H
#define EMDB_H

/* This prevents conflicts whether stdlib.h is included again after or before
 * emdb.h. Ugly hack, I know. */
#include <stdlib.h>

void emdb_mem_file(void *ptr, size_t size, const char *file, int line);
void *emdb_malloc(size_t size, const char *file, int line);
void *emdb_calloc(size_t count, size_t size, const char *file, int line);
void *emdb_realloc(void *ptr, size_t size, const char *file, int line);
void emdb_free(void *ptr, const char *file, int line);

#ifndef EMDB_SOURCE
#define malloc(s) emdb_malloc(s, __FILE__, __LINE__)
#define calloc(c, s) emdb_calloc(c, s, __FILE__, __LINE__)
#define realloc(p, s) emdb_realloc(p, s, __FILE__, __LINE__)
#define free(p) emdb_free(p, __FILE__, __LINE__)
#endif

#define DUMPINT(x) printf("[%s:%d] #%s\n"                                     \
                          "VALUE: %d | SIZE: %lu\n\n",                        \
                          __FILE__, __LINE__, #x, x, sizeof(x))
#define DUMPSTR(x) printf("[%s:%d] #%s\n"                                     \
                          "VALUE: %s | SIZE: %lu | LENGTH: %lu\n\n",          \
                          __FILE__, __LINE__, #x, x, sizeof(x), strlen(x))
#endif
