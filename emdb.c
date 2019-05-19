/* See LICENSE file for copyright and license details. */

#define EMDB_SOURCE

#include "emdb.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void
emdb_mem_file(void *ptr, size_t size, const char *file, int line)
{
	FILE *f;
	char buf[256];
	sprintf(buf, "%p.mem", ptr);
	f = fopen(buf, "w");
	fprintf(f, "File: %s\nLine: %d\nSize: %zu bytes\n", file, line, size);
	fclose(f);
}

void *
emdb_malloc(size_t size, const char *file, int line)
{
	void *p;

	if (!(p = malloc(size)))
		return NULL;

	emdb_mem_file(p, size, file, line);

	return p;
}

void *
emdb_calloc(size_t count, size_t size, const char *file, int line)
{
	void *p;

	if (!(p = calloc(count, size)))
		return NULL;

	emdb_mem_file(p, count * size, file, line);

	return p;
}

void *
emdb_realloc(void *ptr, size_t size, const char *file, int line)
{
	void *p;
	char buf[256];

	if (!(p = realloc(ptr, size)))
		return NULL;

	sprintf(buf, "%p.mem", ptr);
	if (unlink(buf) < 0)
		printf("Double free: %p File: %s Line: %d\n", ptr, file, line);

	emdb_mem_file(p, size, file, line);

	return p;
}

void
emdb_free(void *ptr, const char *file, int line)
{
	char buf[256];

	sprintf(buf, "%p.mem", ptr);
	if (unlink(buf) < 0)
		printf("Double free: %p File: %s Line: %d\n", ptr, file, line);

	free(ptr);
}
