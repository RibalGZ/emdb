/* See LICENSE file for copyright and license details. */

#define EMDB_SOURCE

#include "emdb.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static size_t heap_catalog[HEAP_MAX];
static size_t heap_last = 0;
static size_t heap_set = 0;

static void
heap_init(void)
{
	if (!heap_set) {
		memset(heap_catalog, 0, sizeof(heap_catalog));
		heap_set = 1;
	}
}

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
	heap_init();
	
	void *p;

	if (!(p = malloc(size)))
		return NULL;

	heap_catalog[heap_last] = (size_t)p;
	++heap_last;
	emdb_mem_file(p, size, file, line);

	return p;
}

void *
emdb_calloc(size_t count, size_t size, const char *file, int line)
{
	heap_init();
	
	void *p;

	if (!(p = calloc(count, size)))
		return NULL;

	heap_catalog[heap_last] = (size_t)p;
	++heap_last;
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
	heap_init();
	
	char buf[256];

	sprintf(buf, "%p.mem", ptr);
	if (unlink(buf) < 0)
		printf("Double free: %p File: %s Line: %d\n", ptr, file, line);
	 
	free(ptr);

	size_t i;
	for (i = 0; i < HEAP_MAX; ++i) {
		if (heap_catalog[i] == (size_t)ptr) {
			heap_catalog[i] = 0;
		}
	}
}

int
emdb_var_is_dyn(void *ptr)
{
	size_t i;
	for (i = 0; i < HEAP_MAX; ++i) {
		if (heap_catalog[i] == (size_t)ptr) {
			return 1;
		}
	}

	return 0;
}

void
emdb_hexdump(char *p, int s)
{
	int i;
	unsigned char c[0x10];

	/* table header */
	printf(">>      ");
	for (i = 0; i < 0x10; i++)
		printf(" #%x",i);
	printf(" #");
	for (i = 0; i < 0x10; i++)
		printf("%x",i);
	printf("\n");

	/* content */
	for (i = 0; i < ((s + 15) & 0xfff0); i++) {
		if ((i % 0x10) == 0) {
			if (i != 0)
				printf("  %*.*s\n", 0x10, 0x10, c);
			printf(">> %04x ",i);
		}
		if (i < s) {
			printf(" %02x", p[i]);
			c[i & 0xf] = ((p[i] < 0x20) || (p[i] > 0x7e)) ? '.' : p[i];
		} else {
			printf("   ");
			c[i & 0xf] = ' ';
		}
	}
	printf("  %*.*s\n", 0x10, 0x10, c);
}
