#ifndef WRAPPER_H
#define WRAPPER_H

#include <util.h>

void *Malloc(size_t size);
void *Alloc_array(void **ptr, size_t size, size_t elem_size);

#define ALLOC_ARRAY(ptr, count) Alloc_array((void **)&(ptr), (count), sizeof(*(ptr)))
#define FREE_AND_NULL(p) do { free(p); (p) = NULL; } while (0)


#endif // WRAPPER_H
