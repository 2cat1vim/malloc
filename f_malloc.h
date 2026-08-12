#ifndef MALLOC_H
#define MALLOC_H

#include <sys/mman.h>
#include <sys/resource.h>

void* f_malloc(size_t size);
void f_free(void* ptr);
#endif
