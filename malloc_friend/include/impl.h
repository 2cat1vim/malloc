#ifndef IMPL_H
#define IMPL_H

# define PAGE_SIZE (getpagesize())
# define N_ALLOC 100
# define TINY_BYTES 128
# define SMALL_BYTES 1280
# define TINY_MMAP (((TINY_BYTES) * N_ALLOC + PAGE_SIZE - 1) / PAGE_SIZE * PAGE_SIZE)
# define SMALL_MMAP (((SMALL_BYTES) * N_ALLOC + PAGE_SIZE - 1) / PAGE_SIZE * PAGE_SIZE)
# define LIMIT(type) \
    (type == SMALL) ? (size_t)SMALL_MMAP : (size_t)TINY_MMAP
# define SIZE_BY_TYPE(type, size) \
    (type == TINY) ? (size_t)TINY_BYTES : (type == SMALL) ? (size_t)SMALL_BYTES : (size_t)size
#define ALIGN(size) \
	(((size) + 7) / 8 * 8)

#endif
