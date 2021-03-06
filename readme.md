# Simon's C Headers
A selection of cross-compiler compatible header files for use in my C or C++
projects. All files listed here are C89, C99+, and C++ compatible.

These headers are covered by the GNU Lesser General Public License v3

## `macrodefs.h`
General-use definitions, annotations, and macro definitions.

### Features
- General use macro meta-programming definitions.
  - `STRINGIFY` to stringify the result of a macro expansion.
  - `CONCATENATE` to concatenate two macro expansions together.
- String macros for execution environment printout.
  - `COMPILER_NAME` for compiler used.
  - `OS_NAME` for operating system name.
  - `ARCH_NAME` for processor architecture.
- Consistent macro defines for execution environment detection.
  - Only have to check for `_WIN32` instead of 10+ definitions to tell if you're
    compiling for Windows.
  - Only have to check for `__i386__` instead of 12+ definitions to tell if
    you're compiling for IA-32/x86.
- Compiler feature detection (`__has_attribute`, `__has_declspec_attribute`,
etc.).
  - Includes C++ feature detection macros (e.g. `cpp_constexpr`, `cpp_rtti`).
- Cross-compiler compatible function, typedef, pointer, and parameter attributes.
  - `ALLOCATOR` to denote an associated free function for a given allocation
    function.
  - `CHECK_RESULT` to enforce `if (error) { HANDLE }` on lazy devs.
  - `CONST_FUNC`, `PURE_FUNC`, `PRINTF_FUNC`, and `SCANF_FUNC` are like the
    GCC attributes of similar names.
  - `DEPRECATED` to force people off of old and/or insecure API calls.
  - `NO_RETURN` to denote a function which doesn't return to the caller.
  - `RETURNS_NONNULL` to enforce a lack of billion dollar mistakes.
  - `NULLABLE` and `NOTNULL` for pointers.
- Keywords unavailable in older language variants.
  - `inline` in C89.
  - `__restrict` in C89 or C++.
- Cross-OS and C89/C++03-safe drop-ins for `<stdint.h>`, `<inttypes.h>`,
  `<stdbool.h>`, and `<endian.h>`.
  - Standard boolean type (`bool`).
  - Standard sized integer types (`intX_t`, `int_fastX_t`, `int_leastX_t`,
    `intptr_t`, `intmax_t`).
  - `BYTE_ORDER`, `BIG_ENDIAN`, `LITTLE_ENDIAN`, `PDP_ENDIAN` macros.
  - Host-to-endian and endian-to-host conversion functions.
- `MIN`/`MAX`
  - On supported environments/compilers, a variant which doesn't duplicate side
    effects is used.
- Byte swapping operations.
  - `BSWAP16`, `BSWAP32`, `BSWAP64`
- `WORD_SIZE` for preprocessor pointer size detection.
- Explicit `FALLTHROUGH` for `switch`-`case` blocks.
- Variadic macro building blocks for preprocessor metaprogramming.
  - `VARGEMPTY` checks if the parameter list it is provided is empty;
    returns 1 if empty, 0 if not.
  - `VARGCOUNT` returns the number of parameters it has been passed.
  - `VARGAPPLY` applies a macro to a provided parameter list.

## `atomics.h`
Cross-compiler header-only atomic operations library.

### Dependencies
- `macrodefs.h`

### Features
- Sized atomic integer type definitions & operations (`atomic_X`).
  - Function names are based on C11's `<stdatomic.h>` and C++11's `<atomic>`,
    but with specialized definitions for each atomic type suffixed after
    each operation for C99- compatibility.
      - e.g. an `atomic_exchange` for `atomic_uint16` is called
        `atomic_exchange_uint16`.
      - This is not a problem in C++.
- Atomic flag operations (`atomic_flag`).
- Read-write memory synchronization (`atmoic_fence`).

## `coro.h`
Cross-compiler multiplatform cooperative multitasking library.

### Dependencies
- `macrodefs.h`

### Features
- Stackful coroutines (`Coro_Fiber`).
  - Is compatible with Valgrind; define `CORO_USE_VALGRIND` before including
    the header if your compiler cannot find `valgrind/valgrind.h`.
  - Define `CORO_NO_FIBERS` to not include fiber definitons.
- Stackless coroutines (`Coro_Stack`, `CORO_DECLARE`, `CORO_DEFINE`).

## `thread.h`
Multiplatform single-file C11-compatible preemptive multitasking library.

To build as a library, create a source file and define `THREAD_IMPLEMENTATION`
before including `thread.h`.

### Dependencies
- `macrodefs.h`

### Features
- Threads (`thrd_t`).
- Mutexes (`mtx_t`).
- Condition variables (`cnd_t`).
- Semaphores (`sem_t`).
- Relative timed lock & wait variants of `_timed` functions using `_np` suffix.
  - e.g. `mtx_reltimedlock_np`, `cnd_reltimedwait_np`, `sem_reltimedwait_np`.
- Thread-local storage (`tss_t`, `tss_dtor_t`).
- Hint for how many concurrent threads are available
  (`thrd_hardware_concurrency`).
  - Equivalent to C++11's `thread::hardware_concurrency`.

