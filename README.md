# malloc

`malloc` is a custom userland memory allocator written in C, implementing `malloc`, `free`, `realloc` and the bonus `show_alloc_mem`. It's built as a shared library that can transparently replace the system's `libc` allocator via `LD_PRELOAD`, backed directly by `mmap`-allocated memory zones rather than `sbrk`/`brk`.

---

## How it works

Allocations are grouped into three size classes:

| Type    | Used for                                   | Zone strategy                                                              |
|---------|---------------------------------------------|------------------------------------------------------------------------------|
| `TINY`  | requests up to `TINY_BYTES` (128 bytes)    | Shared zone (`t_page`) sized to hold `N_ALLOC` (100) allocations, `mmap`'d once and reused, page-size aligned |
| `SMALL` | requests up to `SMALL_BYTES` (1280 bytes)  | Same idea as `TINY`, with a bigger fixed-size zone                          |
| `LARGE` | anything bigger                             | Its own individual `mmap` zone, sized exactly to the request                |

1. `malloc()` picks a type from the requested size and asks `create_block()` for a block.
2. `lookup_page()` walks the existing `t_page` list for that type looking for room (`page_has_space`); if none fits, `create_page()` `mmap`s a new zone.
3. `select_block()` either recycles a free block already living in the zone, or bump-allocates a new one at the zone's `ptr_end`.
4. `free()` locates the owning page from the pointer's address range (`get_page`), validates the pointer actually belongs to a known block (`block_exist`), then either flips the block's `free` flag (`TINY`/`SMALL`) or `munmap`s the whole zone immediately (`LARGE`).
5. `realloc()` grows/shrinks a block in place when possible, otherwise falls back to `malloc` + `memcpy` + `free`.
6. `show_alloc_mem()` walks every zone and block and dumps addresses, sizes and free status, plus a running total — useful for debugging the allocator's internal state.

All debug/error output goes through raw `write()` (see `src/utils.c`) — no `printf`, no calls back into the allocator itself.

## Project structure

```
.
├── Makefile                  # Builds libft_malloc_$(HOSTTYPE).so (+ libft_malloc.so symlink)
├── include/
│   ├── malloc.h               # Public API, types (t_type, t_block, t_page, t_share) and prototypes
│   └── impl.h                 # Internal macros: size classes, alignment, debug helpers
├── src/
│   ├── malloc.c                # malloc(): picks TINY/SMALL/LARGE, delegates to create_block()
│   ├── block.c                  # t_block management: bump-allocating and recycling blocks
│   ├── page.c                    # t_share/t_page management: mmap'ing zones, page lookup
│   ├── free.c                     # free(): validates ptr, frees block or munmaps a LARGE page
│   ├── realloc.c                   # realloc(): grow/shrink in place, or malloc+copy+free
│   ├── show_alloc_mem.c              # Bonus: dumps allocator state (pages, blocks, total)
│   └── utils.c                        # write()-based helpers (len, ft_memcpy, print_hex, ...)
└── tests/
    ├── run.sh                # LD_PRELOAD wrapper to run a binary against libft_malloc.so
    ├── test0.c … test5.c     # Manual test programs (see below)
    └── test1 … test5         # Pre-built test binaries
```

## Building

Requirements: `clang`, `make`.

```sh
make        # builds libft_malloc_$(HOSTTYPE).so and the libft_malloc.so symlink
make clean  # removes object files
make fclean # removes object files, the .so and the symlink
make re     # fclean + all
```

`HOSTTYPE` defaults to `$(uname -m)_$(uname -s)` if not already set.

## Usage

`ft_malloc` is meant to be loaded in place of the system allocator via `LD_PRELOAD`:

```sh
export LD_LIBRARY_PATH=$(pwd)
export LD_PRELOAD=libft_malloc.so
./your_program
```

Any binary run this way will have its `malloc`, `free` and `realloc` calls routed through this library instead of glibc's.
