/* See LICENSE file for copyright and license details. */
void emdb_mem_file(size_t size, const char *file, int line);
void *emdb_malloc(size_t size, const char *file, int line);
void *emdb_calloc(size_t count, size_t size, const char *file, int line);
void *emdb_realloc(void *ptr, size_t size, const char *file, int line);
void emdb_free(void *ptr, const char *file, int line);

#define malloc(s) emdb_malloc(s, __FILE__, __LINE__)
#define calloc(c, s) emdb_calloc(c, s, __FILE__, __LINE__)
#define realloc(p, s) emdb_realloc(p, s, __FILE__, __LINE__)
#define free(p) emdb_free(p, __FILE__, __LINE__)
