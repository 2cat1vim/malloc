#ifndef IMPL_H
#define IMPL_H

// GLOBAL MACROS
# define PAGE_SIZE (getpagesize())
# define RW PROT_READ | PROT_WRITE
# define PA MAP_PRIVATE | MAP_ANONYMOUS
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

// DEBUG.C MACROS
#define SELECT_TYPE(n) (n == 0) ? BRED "TINY" RST : (n == 1) ? BRED "SMALL" RST : BRED "LARGE" RST
#define IS_FREE(f) (f == true) ? "Free" : "Not Free"
#define PTR(op) (op == 0) ? b : b + sizeof(t_block)
#define SIZE(op) (op == 0) ? b->size : b->size - sizeof(t_block)
#define WHERE_AM_I(op) \
	(op == 0) ? GRN "ptr status" RST " : ": CYN "ptr + sizeof(t_block) status" RST " : "

// COLORS MACROS

//Regular text
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

//Regular bold text
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"

//Regular underline text
#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"

// Reset
#define RST "\e[0m"

#endif
