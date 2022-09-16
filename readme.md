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
- Cross-compiler compatible function, typedef, pointer, and parameter
  attributes.
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
  - `VARGAPPLY` & `VARGEACH` apply a macro to a provided parameter list.
    - macros applied via `VARGEACH` take one parameter, provided via
      `__VA_ARGS__`.
    - macros applied via `VARGAPPLY` take two parameters, one via
      `__VA_ARGS__` and a constant provided in the `VARGAPPLY` call itself.
    - both optionally take a separator -- a name which, when succeeded by an
      empty set of parenthesis, should expand to a token.
      - Defaults to `SPACE`; other options are included, such as `SEMICOLON`
        and `COMMA`.
      - Separators are applied between visible tokens; *i.e.* only one
        separator will be emitted in between two visible macro expansions,
        even if there are multiple blank macro expansions separating them or
        if the end of the argument list is reached.
        - *e.g.*: `VARGEACH(VARGPACK, (1, 2, '3', , 4,), COMMA)` expands to
          the tokens: `1 , 2 , '3' , 4 `.
- Compound literal and list initializer cross-compatibility macros via using
  `struct` and `union` keywords followed by parenthesis (e.g.
  `struct(struct timespec)`; only works in C99+ (or with GNU extensions) and
  C++11+.
- Cross-language casting
  - `CAST` -> `static_cast` or C value cast
  - `RCAST` -> `reinterpret_cast` or C bytewise case
  - `CCAST` -> `const_cast`
  - `FCAST` -> function pointer cast

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
- Read-write memory synchronization (`atomic_fence`).

## `coro.h`
Cross-compiler multiplatform cooperative multitasking library.

### Dependencies
- `macrodefs.h`

### Features
- Stackful coroutines (`Coro_Fiber`).
  - *i.e.* uses an operating-system provided call stack.
  - Is compatible with Valgrind; define `CORO_USE_VALGRIND` before including
    the header if your compiler cannot find `valgrind/valgrind.h`.
  - Define `CORO_NO_FIBERS` to not include fiber definitons.
- Stackless coroutines (`CORO_DECLARE`, `CORO_DEFINE`, `CORO_BEGIN`,
  `CORO_END`).
  - *i.e.* uses a user-provided stack (`Coro_Stack`).

### Sample Usage
#### Stackless coroutines
```c
// sample uses features or extensions provided via
// GNU C, MS Visual C, ISO C99+, or ISO C++11+

#include <string.h> // memmove

// preconditions: end > ptr  -> data available to read
//                end = ptr  -> halt to receive more data
//                end = NULL -> end of file
typedef struct {
    uint8_t* ptr, * end;
} Reader;

CORO_DECLARE(uint8_t, read_single_byte);
uint8_t read_single_byte(Coro_Stack* coro, Reader* reader) {
    // "coro" is the name of a pointer to the current coroutine stack
    // & state; this variable must be defined before CORO_BEGIN

    CORO_BEGIN(read_single_byte) {
        while UNLIKELY(reader->end)
            CORO_YIELD(0);
    } CORO_END(reader->ptr++[0]);
}

CORO_DECLARE(uint32_t, decode_leb_u32, {
    uint32_t result : 28;
    uint32_t shift : 4;
});
uint32_t decode_leb_u32(Coro_Stack* coro, Reader* reader) {
    uint32_t result;
    CORO_BEGIN(decode_leb_u32) {
        uint8_t byte;
        uint32_t shift = 0;
        result = 0;

        do {
            // "coro_next" is the name of the next coroutine call frame
            // to pass as the "coro" parameter for stackless coroutine
            // functions
            byte = read_single_byte(coro_next, reader);

            if UNLIKELY(coro_next[0]) /* non-zero = yielded */ {
                // "frame" is the name of the current coroutine frame to
                // save and restore local variables
                frame->result = result & 0x0fffffffu;
                frame->shift = shift / 7;
                CORO_YIELD(0);
                result = frame->result;
                shift = frame->shift * 7;
            } else {
                result |= (byte & 0x7f) << shift;
            }
        } while (coro_next[0] || ((byte & 0x80) && (shift += 7) < 35);

        if (byte & 0x80) // decode error!
            result = 0;
    } CORO_END(result);
}

```

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

