# malloc

`malloc` is a custom implementation of `malloc`, `free`, and `realloc` written in C, compiled as a dynamic library (`libft_malloc.so`) that can be `LD_PRELOAD`'d (or linked) in place of the standard libc allocator.

It manages memory using `mmap`-ed pages split into three allocation strategies (`TINY`, `SMALL`, `LARGE`), each page holding a linked list of blocks, and exposes a debug helper (`show_alloc_mem`) to visualize the current state of all allocated pages and blocks.

> ⚠️ **Educational use only.** This is a learning project (42-style "malloc" exercise) meant to explore memory management, `mmap`, pointer arithmetic, and shared library builds. It is not intended as a production-grade allocator.

---

## How it works

1. On the first call to `malloc`, the library computes which bucket the requested size falls into:
   - **TINY**: allocations that fit (with header) under `TINY_BYTES` (128 bytes)
   - **SMALL**: allocations that fit (with header) under `SMALL_BYTES` (1280 bytes)
   - **LARGE**: anything bigger, mapped individually
2. It looks up an existing page of the right type with enough free space, or `mmap`s a new one (`TINY`/`SMALL` pages are pre-sized to hold ~100 allocations; `LARGE` pages are sized exactly to the request).
3. Within a page, it walks the block list looking for a free block big enough to reuse, otherwise appends a new block at the end of the page.
4. `free` marks `TINY`/`SMALL` blocks as reusable in place, while `LARGE` pages are `munmap`ed entirely.
5. `realloc` shrinks in place when possible, or falls back to `free` + `malloc` (copy) when growing.
6. `show_alloc_mem` walks every page/block and prints addresses, free status, and sizes for debugging.

## Project structure

```
.
├── main.c                       # Test/demo program exercising malloc/free/realloc
├── Makefile                     # Builds the test binary and links against malloc_friend
├── ex.txt                       # LD_LIBRARY_PATH helper snippet
└── malloc_friend/
    ├── Makefile                  # Builds libft_malloc_<HOSTTYPE>.so (+ libft_malloc.so symlink)
    ├── include/
    │   ├── malloc.h               # Public API, t_block/t_page structs, prototypes
    │   └── impl.h                 # Internal macros (sizes, alignment, debug/color macros)
    └── src/
        ├── malloc.c                # malloc() entry point, bucket selection
        ├── free.c                  # free() entry point, block/page freeing logic
        ├── realloc.c                # realloc() entry point, shrink/grow-copy logic
        ├── page.c                   # Page mmap'ing, lookup, and space-checking
        ├── block.c                  # Block creation/selection within a page
        ├── debug.c                  # show_alloc_mem() pretty-printer
        └── utils.c                  # print_hex/print_nbr/pout helpers (no libc printf)
```

## Building

Requirements: `clang`, `make`.

```sh
make        # builds malloc_friend/libft_malloc_<HOSTTYPE>.so, then the malloc_test binary
make clean  # removes object files (test + library)
make fclean # removes object files, the .so, and the malloc_test binary
make re     # fclean + all
```

The library itself can also be built standalone:

```sh
cd malloc_friend
make        # produces libft_malloc_<HOSTTYPE>.so and a libft_malloc.so symlink
```

## Usage

Before running anything linked against `libft_malloc.so`, point the dynamic linker at it:

```sh
export LD_LIBRARY_PATH=$PWD/malloc_friend:$LD_LIBRARY_PATH
```

(this exact line is provided in `ex.txt` for convenience).

Then run the test binary:

```sh
./malloc_test
```

`main.c` demonstrates typical usage: allocating `TINY`/`LARGE`-sized chunks, freeing some, then growing/shrinking others via `realloc`, printing the allocator state with `show_alloc_mem()` between each step.

```c
#include "malloc_friend/include/malloc.h"

char* a = malloc(88);
char* b = malloc(8200);
show_alloc_mem();   // dumps every page/block, sizes, and free status
free(a);
char* c = realloc(b, 111322);
```

## Debugging

`show_alloc_mem()` prints, for each page type (`TINY`/`SMALL`/`LARGE`):
- the page address
- each block's raw pointer and user-visible pointer (past the header)
- its size, free/not-free status
- a running total of bytes allocated across all pages

## Disclaimer

This project was built for learning purposes (custom allocators, `mmap`, raw pointer/struct manipulation, shared library builds). It has known rough edges (see the `NEED GUARDS` comments in `free.c`/`realloc.c`/`malloc.c`) and should not be used as a drop-in allocator for real applications.
