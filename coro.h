/**
 * @file coro.h
 * @author Simon Bolivar
 * @date 23 Jan 2022
 * 
 * @brief Coroutine library using fibers.
 * 
 * @note This code was inspired by and adapted from Coco, a true C coroutine
 *       patch for the Lua runtime by Mike Pall: http://coco.luajit.org/
 * 
 * @copyright MIT
 * 
 * @par
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * @par
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * @par
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef CORO_H_
#define CORO_H_

#include "macrodefs.h"
#if CPP_PREREQ(1L)
#   include <cstdlib>
#else
#   include <stdlib.h>
#endif

/**
 * @brief A cooperative thread.
 */
typedef struct Coro_Fiber Coro_Fiber;

/**
 * @brief Function signature for calling a coroutine.
 */
typedef int (CDECL* Coro_Function)(Coro_Fiber *const, uintptr_t);

#ifdef _USES_WINFIBERS
#   undef _USES_WINFIBERS
#endif
#ifdef _NO_CORO_IMPL
#   undef _NO_CORO_IMPL
#endif

#if ((defined(_WIN32) && (_WIN32_WINNT >= 0x0400)) || defined(__WINRT__)) && \
    !defined(CORO_NO_WINFIBERS)
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN 1
#   endif
#   include <windows.h>
#   if defined __WINRT__ || _WIN32_WINNT >= 0x0600
#       define ConvertThreadToFiber(x) \
            ConvertThreadToFiberEx(x, FIBER_FLAG_FLOAT_SWITCH)
#   endif
#   define CORO_DEFAULT_STACK_SIZE 0

    struct Coro_Fiber {
        void* handle;
        void* back;
        Coro_Function fn;
        uintptr_t up;
    };

#   define __CORO_INIT(coro, start, param, stksz) return !!( \
        (coro)->handle = CreateFiberEx( \
            (stksz), (stksz), 0, (start), (void*)(param) \
    ))
#   define __CORO_DESTROY(coro) { \
        DeleteFiber((coro)->handle); \
        (coro)->handle = NULL; \
    }
#   define __CORO_RESUME(coro) { \
        void* cur = GetCurrentFiber(); \
        (coro)->back = (!cur || cur == (void*)(uintptr_t)0x1e00) ? \
            ConvertThreadToFiber(NULL) : \
            cur \
        ; \
        SwitchToFiber((coro)->handle); \
    }
#   define __CORO_SUSPEND(coro) { SwitchToFiber((coro)->back); }
#   define __CORO_STARTDECL STDCALL
#   define __CORO_STARTPARAMS (void* p)
#   define __CORO_GETPTR Coro_Fiber* coro = (Coro_Fiber*)p;
#   define _USES_WINFIBERS
#elif GCC_PREREQ(30000) && !defined(CORO_NO_ASM) /* gcc assembly */
#   ifdef __i386__
#       ifdef __PIC__
            typedef struct { uintptr_t eip, esp, ebp, ebx; } _Coro_Context;

            static_force_inline void __coro_switch(
                _Coro_Context *const restrict from,
                _Coro_Context *const restrict to
            ) {
                __asm__ __volatile__ (
                    "call 1f\n"
                    "1:\ttpopl %%eax\n\t"
                    "addl $(2f-1b),%%eax\n\t"
                    "movl %%eax, (%0)\n\t"
                    "movl %%esp, 4(%0)\n\t"
                    "movl %%ebp, 8(%0)\n\t"
                    "movl %%ebx, 12(%0)\n\t"
                    "movl 12(%1), %%ebx\n\t"
                    "movl 8(%1), %%ebp\n\t"
                    "movl 4(%1), %%esp\n\t"
                    "jmp *(%1)\n"
                    "2:\n"
                    : "+S" (from)
                    , "+D" (to)
                    :
                    : "eax"
                    , "ecx"
                    , "edx"
                    , "memory"
                    , "cc"
                );
            }
#       else
            typedef struct { uintptr_t eip, esp, ebp; } _Coro_Context;

            static_force_inline void __coro_switch(
                _Coro_Context *const restrict from,
                _Coro_Context *const restrict to
            ) {
                __asm__ __volatile__ (
                    "movl $1f, (%0)\n\t"
                    "movl %%esp, 4(%0)\n\t"
                    "movl %%ebp, 8(%0)\n\t"
                    "movl 8(%1), %%ebp\n\t"
                    "movl 4(%1), %%esp\n\t"
                    "jmp *(%1)\n"
                    "1:\n"
                    : "+S" (from)
                    , "+D" (to)
                    :
                    : "eax"
                    , "ecx"
                    , "edx"
                    , "memory"
                    , "cc"
                );
            }
#       endif

#       define __CORO_CTX_INIT(coro, ctx, func, stack, param) do { \
            (ctx).eip = (uintptr_t)__extension__(void*)(func); \
            (ctx).esp = (uintptr_t)(stack); \
            (ctx).ebp = 0; \
            (stack)[0] = 0xdeadc0de; \
            (coro)->param = (param); \
        } while (0)
#       define __CORO_SWITCH(from, to) __coro_switch(from, to)
#       define __CORO_STATE_HEAD uintptr_t param;
#       ifdef _NO_CORO_IMPL
#           undef _NO_CORO_IMPL
#       endif
#   elif defined(__x86_64__)
        static void __coro_entry(void) {
            __asm__ __volatile__ ( "\tmovq %r13, %rdi\n\tjmpq *%r12\n" );
        }

        typedef ALIGN_TO(16) struct {
            uint64_t parts[2];
        } _Coro_R128;

        typedef struct {
            uintptr_t rip, rsp, rbp, rbx, r12, r13, r14, r15;
#       ifdef _WIN32
            uintptr_t rdi, rsi;
            _Coro_R128 xmm[10];
#       endif
        } _Coro_Context;

        static_force_inline void __coro_switch(
            _Coro_Context *const restrict from,
            _Coro_Context *const restrict to
        ) {
            __asm__ __volatile__ (
                "leaq 1f(%%rip), %%rax\n\t"
                "movq %%rax, (%0)\n\t"
                "movq %%rsp, 8(%0)\n\t"
                "movq %%rbp, 16(%0)\n\t"
                "movq %%rbx, 24(%0)\n\t"
                "movq %%r12, 32(%0)\n\t"
                "movq %%r13, 40(%0)\n\t"
                "movq %%r14, 48(%0)\n\t"
                "movq %%r15, 56(%0)\n\t"
#           ifdef _WIN32
                "movq %%rdi, 64(%0)\n\t"
                "movq %%rsi, 72(%0)\n\t"
                "movdqa %%xmm6, 80(%0)\n\t"
                "movdqa %%xmm7, 96(%0)\n\t"
                "movdqa %%xmm8, 112(%0)\n\t"
                "movdqa %%xmm9, 128(%0)\n\t"
                "movdqa %%xmm10, 144(%0)\n\t"
                "movdqa %%xmm11, 160(%0)\n\t"
                "movdqa %%xmm12, 176(%0)\n\t"
                "movdqa %%xmm13, 192(%0)\n\t"
                "movdqa %%xmm14, 208(%0)\n\t"
                "movdqa %%xmm15, 224(%0)\n\t"
                "movdqa 224(%1), %%xmm15\n\t"
                "movdqa 208(%1), %%xmm14\n\t"
                "movdqa 192(%1), %%xmm13\n\t"
                "movdqa 176(%1), %%xmm12\n\t"
                "movdqa 160(%1), %%xmm11\n\t"
                "movdqa 144(%1), %%xmm10\n\t"
                "movdqa 128(%1), %%xmm9\n\t"
                "movdqa 112(%1), %%xmm8\n\t"
                "movdqa 96(%1), %%xmm7\n\t"
                "movdqa 80(%1), %%xmm6\n\t"
                "movq 72(%1), %%rsi\n\t"
                "movq 64(%1), %%rdi\n\t"
#               define __CORO_CTX_EXTRA(ctx) \
                    (ctx).rdi = 0; \
                    (ctx).rsi = 0; \
                    memset((ctx).xmm, 0, sizeof (ctx).xmm);
#           else
#               define __CORO_CTX_EXTRA(ctx)
#           endif
                "movq 56(%1), %%r15\n\t"
                "movq 48(%1), %%r14\n\t"
                "movq 40(%1), %%r13\n\t"
                "movq 32(%1), %%r12\n\t"
                "movq 24(%1), %%rbx\n\t"
                "movq 16(%1), %%rbp\n\t"
                "movq 8(%1), %%rsp\n\t"
                "jmpq *(%1)\n"
                "1:\n"
                : "+S" (from)
                , "+D" (to)
                :
                : "rax"
                , "rcx"
                , "rdx"
                , "r8"
                , "r9"
                , "r10"
                , "r11"
                , "memory"
                , "cc"
            );
        }

#       define __CORO_CTX_INIT(coro, ctx, func, stack, param) do { \
            (ctx).rip = (uintptr_t)__extension__(void*)__coro_entry; \
            (ctx).rsp = (uintptr_t)(stack); \
            (ctx).rbp = 0; \
            (ctx).rbx = 0; \
            (ctx).r12 = __extension__(void*)(func); \
            (ctx).r13 = (param); \
            (ctx).r14 = 0; \
            (ctx).r15 = 0; \
            __CORO_CTX_EXTRA(ctx) \
            (stack)[0] = 0xdeadc0dedeadc0de; \
        while (0)
#       define __CORO_SWITCH(from, to) __coro_switch(from, to);
#       ifdef _NO_CORO_IMPL
#           undef _NO_CORO_IMPL
#       endif
#   elif defined(__mips__) && !defined(__mips_eabi) && \
        ((defined(_ABIO32) && _MIPS_SIM == _ABIO32) || \
        (defined(_MIPS_SIM_ABI32) && _MIPS_SIM == _MIPS_SIM_ABI32))
#       define __CORO_STKADJUST 8
        typedef struct { uintptr_t ra, sp; } _Coro_Context;

        static const uint32_t __coro_switch[] = {
#       ifdef __mips_soft_float
            0x27bdffd8,
#       else
            0x27bdffa8,
            0xf7be0050,
            0xf7bc0048,
            0xf7ba0040,
            0xf7b80038,
            0xf7b60030,
            0xf7b40028,
#       endif
            0xafbe0024,
            0xafb70020,
            0xafb6001c,
            0xafb50018,
            0xafb40014,
            0xafb30010,
            0xafb2000c,
            0xafb10008,
            0xafb00004,
            0xafbc0000,
            0xac9d0004,
            0xac9f0000,
            0x8cbf0000,
            0x8cbd0004,
            0x03e0c821,
            0x8fbe0024,
            0x8fb70020,
            0x8fb6001c,
            0x8fb50018,
            0x8fb40014,
            0x8fb30010,
            0x8fb2000c,
            0x8fb10008,
            0x8fb00004,
            0x8fbc0000,
#       ifdef __mips_soft_float
            0x03e00008,
            0x27bd0028
#       else
            0xd7be0050,
            0xd7bc0048,
            0xd7ba0040,
            0xd7b80038,
            0xd7b60030,
            0xd7b40028,
            0x03e00008,
            0x27bd0058
#       endif
        };

#       define __coro_switch(from, to) do { \
            (__extension__ \
                (void (*)(_Coro_Context*, _Coro_Context*))__coro_switch \
            )((from), (to)); \
        } while (0)

#       ifdef __mips_soft_float
#           define __CORO_CTX_INIT(coro, ctx, func, stack, param) do { \
                (ctx)->ra = (uintptr_t)__extension__(void*)(func); \
                (ctx)->sp = (uintptr_t)(&(stack)[-10]); \
                (stack)[4] = (size_t)(param); \
            while (0)
#       else
#           define __CORO_CTX_INIT(coro, ctx, func, stack, param) do { \
                (ctx)->ra = (uintptr_t)__extension__(void*)(func); \
                (ctx)->sp = (uintptr_t)(&(stack)[-22]); \
                (stack)[4] = (size_t)(param); \
            while (0)
#       endif
#       define __CORO_SWITCH(from, to) __coro_switch(from, to);
#       define __CORO_STARTPARAMS \
            (int _a, int _b, int _c, int _d, Coro_Fiber* coro)
#       define __CORO_STARTUNUSED { (void)_a; (void)_b; (void)_c; (void)_d; }
#       ifdef _NO_CORO_IMPL
#           undef _NO_CORO_IMPL
#       endif
#   elif defined(__sparc__)
#       define __CORO_STKADJUST 24
        typedef struct { uintptr_t regs[4]; } _Coro_Context;
#       ifdef __LP64__
            static_force_inline void __coro_switch(
                _Coro_Context *const restrict from,
                _Coro_Context *const restrict to
            ) {
                uintptr_t stack[16] __attribute__((aligned(16)));
                uintptr_t tmpsp = (uintptr_t)&stack[0] - 2047UL;
                __asm__ __volatile__ (
                    "ta 3\n\t"
                    "stx %%sp,[%0+8]\n\t"
                    "mov %2,%%sp\n\t"
                    "sethi %%hh(1f),%%g1\n\t"
                    "or %%g1,%%hm(1f),%%g1\n\t"
                    "sethi %%lm(1f),%%g2\n\t"
                    "or %%g2,%%lo(1f),%%g2\n\t"
                    "sllx %%g1,32,%%g1\n\t"
                    "or %%g1,%%g2,%%g1\n\t"
                    "stx %%g1,[%0]\n\t"
                    "mov %1,%%o1\n\t"
                    "ldx [%%o1+8],%%o2\n\t"
                    "ldx [%%o2+%3],%%l0\n\t"
                    "ldx [%%o2+%3+8],%%l1\n\t"
                    "ldx [%%o2+%3+0x10],%%l2\n\t"
                    "ldx [%%o2+%3+0x18],%%l3\n\t"
                    "ldx [%%o2+%3+0x20],%%l4\n\t"
                    "ldx [%%o2+%3+0x28],%%l5\n\t"
                    "ldx [%%o2+%3+0x30],%%l6\n\t"
                    "ldx [%%o2+%3+0x38],%%l7\n\t"
                    "ldx [%%o2+%3+0x40],%%i0\n\t"
                    "ldx [%%o2+%3+0x48],%%i1\n\t"
                    "ldx [%%o2+%3+0x50],%%i2\n\t"
                    "ldx [%%o2+%3+0x58],%%i3\n\t"
                    "ldx [%%o2+%3+0x60],%%i4\n\t"
                    "ldx [%%o2+%3+0x68],%%i5\n\t"
                    "ldx [%%o2+%3+0x70],%%i6\n\t"
                    "ldx [%%o2+%3+0x78],%%i7\n\t"
                    "mov %%o2,%%sp\n\t"
                    "ldx [%%o1],%%o2\n\t"
                    "ldx [%%o1+16],%%o0\n\t"
                    "jmpl %%o2,%%g0\n\t"
                    "nop\n\t"
                    "1:\n"
                    :
                    : "r"(from)
                    , "r"(to)
                    , "r"(tmpsp)
                    , "i"(2047UL)
                    : "g1"
                    , "g2"
                    , "o0"
                    , "o1"
                    , "o2"
                    , "o3"
                    , "o4"
                    , "o5"
                    , "o7"
                    , "memory"
                    , "cc"
                );
            }

#           define __CORO_CTX_INIT(coro, ctx, func, stack, param) do { \
                (ctx).regs[0] = (uintptr_t)__extension__(void*)(func); \
                (ctx).regs[1] = (uintptr_t)(stack); \
                (ctx).regs[2] = (param); \
                stack[0] = 0; \
                stack[1] = 0; \
                stack[2] = 0; \
                stack[3] = 0; \
                stack[4] = 0; \
                stack[5] = 0; \
                stack[6] = 0; \
                stack[7] = 0; \
                stack[8] = 0; \
                stack[9] = 0; \
                stack[10] = 0; \
                stack[11] = 0; \
                stack[12] = 0; \
                stack[13] = 0; \
                stack[14] = (uintptr_t)&(stack)[__CORO_STKADJUST] - 2047UL; \
                stack[15] = 0xdeadc0de; \
            while (0)
#       else
            static_force_inline void __coro_switch(
                _Coro_Context *const restrict from,
                _Coro_Context *const restrict to
            ) {
                uintptr_t tmpstk[16] __attribute__((aligned(16)));
                __asm__ __volatile__ (
                    "ta 3\n\t"
                    "stx %%sp,[%0+4]\n\t"
                    "mov %2,%%sp\n\t"
                    "set 1f,%%g1\n\t"
                    "st %%g1,[%0]\n\t"
                    "mov %1,%%o1\n\t"
                    "ld [%%o1+4],%%o2\n\t"
                    "ldd [%%o2],%%l0\n\t"
                    "ldd [%%o2+8],%%l2\n\t"
                    "ldd [%%o2+0x10],%%l4\n\t"
                    "ldd [%%o2+0x18],%%l6\n\t"
                    "ldd [%%o2+0x20],%%i0\n\t"
                    "ldd [%%o2+0x28],%%i2\n\t"
                    "ldd [%%o2+0x30],%%i4\n\t"
                    "ldd [%%o2+0x38],%%i6\n\t"
                    "mov %%o2,%%sp\n\t"
                    "ld [%%o1],%%o2\n\t"
                    "ld [%%o1+8],%%o0\n\t"
                    "jmpl %%o2,%%g0\n\t"
                    "nop\n\t"
                    "1:\n"
                    :
                    : "r"(from)
                    , "r"(to)
                    , "r"(tmpstk)
                    : "g1"
                    , "o0"
                    , "o1"
                    , "o2"
                    , "o3"
                    , "o4"
                    , "o5"
                    , "o7"
                    , "memory"
                    , "cc"
                );

#           define __CORO_CTX_INIT(coro, ctx, func, stack, param) do { \
                (ctx).regs[0] = (uintptr_t)__extension__(void*)(func); \
                (ctx).regs[1] = (uintptr_t)(stack); \
                (ctx).regs[2] = (param); \
                stack[0] = 0; \
                stack[1] = 0; \
                stack[2] = 0; \
                stack[3] = 0; \
                stack[4] = 0; \
                stack[5] = 0; \
                stack[6] = 0; \
                stack[7] = 0; \
                stack[8] = 0; \
                stack[9] = 0; \
                stack[10] = 0; \
                stack[11] = 0; \
                stack[12] = 0; \
                stack[13] = 0; \
                stack[14] = (uintptr_t)&stack[__CORO_STKADJUST] - 2047UL; \
                stack[15] = 0xdeadc0dedeadc0de; \
            } while (0)
#       endif
#       define __CORO_SWITCH(from, to) __coro_switch(from, to);
#       ifdef _NO_CORO_IMPL
#           undef _NO_CORO_IMPL
#       endif
#   elif defined(__ARM_EABI__)
        typedef struct {
#       ifndef __SOFTFP__
            uintptr_t fpregs[16];
#       endif
            uintptr_t r4, r5, r6, r7, r8, r9, r10, r11, lr, sp;
        } _Coro_Context;

        void __coro_start(void);
        int __coro_switch(
            _Coro_Context *const restrict from,
            _Coro_Context *const restrict to
        );

        __asm__ (
            ".text\n"
            ".globl __coro_switch\n"
            ".type __coro_switch #function\n"
            ".hidden __coro_switch\n"
            "__coro_switch:\n"
#       ifndef __SOFTFP
            "  vstmia r0!, {d8-d15}\n"
#       endif
            "  stmia r0, {r4-r11, lr}\n"
            "  str sp, [r0, #9*4]\n"
#       ifndef __SOFTFP
            "  vldmia r1!, {d8-d15}\n"
#       endif
            "  ldr sp, [r1, #9*4]\n"
            "  ldmia r1, {r4-r11, pc}\n"
            ".size __coro_switch, .-__coro_switch\n"
        );

        __asm__ (
            ".text\n"
            ".globl __coro_start\n"
            ".type __coro_start #function\n"
            ".hidden __coro_start\n"
            "__coro_start:\n"
            "  mov r0, r4\n"
            "  mov ip, r5\n"
            "  mov lr, r6\n"
            "  bx ip\n"
            ".size __coro_start, .-__coro_start\n"
        );

#       define __CORO_STKADJUST 0
#       define __CORO_CTX_INIT(coro, ctx, func, stack, param) do { \
            (ctx).r4 = (param); \
            (ctx).r5 = (uintptr_t)__extension__(void*)(func); \
            (ctx).r6 = 0xdeadc0de; \
            (ctx).lr = (uintptr_t)__extension__(void*)__coro_start; \
            (ctx).sp = (uintptr_t)(stack); \
        } while (0)
#       define __CORO_SWITCH(from, to) __coro_switch(from, to);
#       ifdef _NO_CORO_IMPL
#           undef _NO_CORO_IMPL
#       endif
#   elif defined(__aarch64__)
        typedef struct {
            uintptr_t x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29;
            uintptr_t x30, sp, lr, d8, d9, d10, d11, d12, d13, d14, d15;
        } _Coro_Context;

        int __coro_switch(
            _Coro_Context *const restrict from,
            _Coro_Context *const restrict to
        );

        __asm__(
            ".text\n"
            ".globl coco_switch\n"
            ".type coco_switch #function\n"
            ".hidden coco_switch\n"
            "coco_switch:\n"
            "  mov x10, sp\n"
            "  mov x11, x30\n"
            "  stp x19, x20, [x0, #(0*16)]\n"
            "  stp x21, x22, [x0, #(1*16)]\n"
            "  stp d8, d9, [x0, #(7*16)]\n"
            "  stp x23, x24, [x0, #(2*16)]\n"
            "  stp d10, d11, [x0, #(8*16)]\n"
            "  stp x25, x26, [x0, #(3*16)]\n"
            "  stp d12, d13, [x0, #(9*16)]\n"
            "  stp x27, x28, [x0, #(4*16)]\n"
            "  stp d14, d15, [x0, #(10*16)]\n"
            "  stp x29, x30, [x0, #(5*16)]\n"
            "  stp x10, x11, [x0, #(6*16)]\n"
            "  ldp x19, x20, [x1, #(0*16)]\n"
            "  ldp x21, x22, [x1, #(1*16)]\n"
            "  ldp d8, d9, [x1, #(7*16)]\n"
            "  ldp x23, x24, [x1, #(2*16)]\n"
            "  ldp d10, d11, [x1, #(8*16)]\n"
            "  ldp x25, x26, [x1, #(3*16)]\n"
            "  ldp d12, d13, [x1, #(9*16)]\n"
            "  ldp x27, x28, [x1, #(4*16)]\n"
            "  ldp d14, d15, [x1, #(10*16)]\n"
            "  ldp x29, x30, [x1, #(5*16)]\n"
            "  ldp x10, x11, [x1, #(6*16)]\n"
            "  mov sp, x10\n"
            "  br x11\n"
            ".size coco_switch, .-coco_switch\n"
        );

        __asm__(
            ".text\n"
            ".globl coco_wrap_main\n"
            ".type coco_wrap_main #function\n"
            ".hidden coco_wrap_main\n"
            "coco_wrap_main:\n"
            "  mov x0, x19\n"
            "  mov x30, x21\n"
            "  br x20\n"
            ".size coco_wrap_main, .-coco_wrap_main\n"
        );
        
#       define __CORO_STKADJUST 0
#       define __CORO_CTX_INIT(coro, ctx, func, stack, param) do { \
            (ctx).x19 = (param); \
            (ctx).x20 = (uintptr_t)__extension__(void*)(func); \
            (ctx).x21 = 0xdeadc0dedeadc0de; \
            (ctx).sp = (uintptr_t)(stack) & ~15; \
            (ctx).lr = (uintptr_t)__extension__(void*)__coro_start; \
        } while (0)
#       define __CORO_SWITCH(from, to) __coro_switch(from, to);
#       ifdef _NO_CORO_IMPL
#           undef _NO_CORO_IMPL
#       endif
#   else
#       define _NO_CORO_IMPL 1
#   endif
#else
#   define _NO_CORO_IMPL 1
#endif

#ifdef _NO_CORO_IMPL /* stdc setjmp/longjmp */
#   undef _NO_CORO_IMPL

#   ifdef CORO_NO_SETJMP
#       define _NO_CORO_IMPL 1
#   else
#       include <setjmp.h>
        typedef jmp_buf _Coro_Context;

#       ifdef __i386__
#           define __CORO_STATE_HEAD uintptr_t param;
#           if __GLIBC__ == 2 && defined(JB_SP) /* glibc2 */
#               define __CORO_CTX_PATCH(coro, buf, func, stack, p) do { \
                    (buf)->__jmpbuf[JB_PC] = (intptr_t) __extension__ (void*)( \
                        func \
                    ); \
                    (buf)->__jmpbuf[JB_SP] = (intptr_t)(stack); \
                    (buf)->__jmpbuf[JB_BP] = 0; \
                    (stack)[__CORO_STKADJUST-1] = 0xdeadc0de; \
                    (coro)->param = (p); \
                } while (0)
#           elif defined(__linux__) && defined(_I386_JMP_BUF_H) /* libc5 */
#               define __CORO_CTX_PATCH(coro, buf, func, stack, p) do { \
                    (buf)->__pc = (intptr_t) __extension__ (void*)(func); \
                    (buf)->__sp = (intptr_t)(stack); \
                    (buf)->__bp = 0; \
                    (stack)[__CORO_STKADJUST-1] = 0xdeadc0de; \
                    (coro)->param = (p); \
                } while (0)
#           elif defined(__FreeBSD__) /* freebsd */
#               define __CORO_STKADJUST 2
#               define __CORO_CTX_PATCH(coro, buf, func, stack, p) do { \
                    (buf)->_jb[0] = (intptr_t) __extension__ (void*)(func); \
                    (buf)->_jb[2] = (intptr_t)(stack); \
                    (buf)->_jb[3] = 0; \
                    (stack)[__CORO_STKADJUST-1] = 0xdeadc0de; \
                    (coro)->param = (p); \
                } while (0)
#           elif defined(__NetBSD__) || defined(__OpenBSD__) /* openbsd */
#               define __CORO_STKADJUST 2
#               define __CORO_CTX_PATCH(coro, buf, func, stack, p) do { \
                    (buf)[0] = (intptr_t) __extension__ (void*)(func); \
                    (buf)[2] = (intptr_t)(stack); \
                    (buf)[3] = 0; \
                    (stack)[__CORO_STKADJUST-1] = 0xdeadc0de; \
                    (coro)->param = (p); \
                } while (0)
#           elif defined(__solaris__) && _JBLEN == 10 /* solaris */
#               define __CORO_CTX_PATCH(coro, buf, func, stack, p) do { \
                    (buf)[5] = (intptr_t) __extension__ (void*)(func); \
                    (buf)[4] = (intptr_t)(stack); \
                    (buf)[3] = 0; \
                    (stack)[__CORO_STKADJUST-1] = 0xdeadc0de; \
                    (coro)->param = (p); \
                } while (0)
#           elif defined(__MACH__) && defined(_BSD_I386_SETJMP_H) /* macos */
#               define __CORO_CTX_PATCH(buf, func, stack, p) do { \
                    (buf)[12] = (intptr_t) __extension__ (void*)(func); \
                    (buf)[9] = (intptr_t)(stack); \
                    (buf)[8] = 0; \
                    (stack)[__CORO_STKADJUST-1] = 0xdeadc0de; \
                    (coro)->param = (p); \
                } while (0)
#           else
#               define _NO_CORO_IMPL 1
#           endif
#       elif defined(__x86_64__)
#           define __CORO_STATE_HEAD uintptr_t param;
#           define __CORO_STARTPARAMS ( \
                int _a, int _b, int _c, int _d, int _e, int _f, \
                Coro_Fiber* coro \
            )
#           define __CORO_STARTUNUSED \
                { (void)_a; (void)_b; (void)_c; (void)_d; (void)_e; (void)_f; }

/*#           ifdef _WIN32
#               define __CORO_CTX_PATCH(coro, buf, func, stack, p) do { \
                    (buf)->Rip = (intptr_t) __extension__ (void*)(func); \
                    (buf)->Rsp = (intptr_t)(stack); \
                    (buf)->Rbp = 0; \
                    (stack)[0] = 0xdeadc0dedeadc0de; \
                    (coro)->param = (p); \
                } while (0)*/
#           if defined(__solaris__) && _JBLEN == 8 /* solaris */
#               define __CORO_CTX_PATCH(coro, buf, func, stack, p) do { \
                    (buf)[7] = (intptr_t) __extension__ (void*)(func); \
                    (buf)[6] = (intptr_t)(stack); \
                    (buf)[5] = 0; \
                    (stack)[0] = 0xdeadc0dedeadc0de; \
                    (coro)->param = (p); \
                } while (0)
#           else
#               define _NO_CORO_IMPL 1
#           endif
#       elif defined(__powerpc__)
#           define __CORO_STKADJUST 16
#           define __CORO_STARTPARAMS ( \
                int _a, int _b, int _c, int _d, int _e, int _f, int _g, \
                int _h, Coro_Fiber* coro \
            )
#           define __CORO_STARTUNUSED { \
                (void)_a; (void)_b; (void)_c; (void)_d; (void)_e; \
                (void)_f; (void)_g; (void)_h; \
            }
#           if defined(__MACH__) && defined(_BSD_PPC_SETJMP_H) /* macos */
#               define __CORO_CTX_PATCH(coro, buf, func, stack, p) do { \
                    (buf)[21] = (intptr_t) __extension__ (void*)(func); \
                    (buf)[0] = (intptr_t)(stack); \
                    (stack)[14] = (p); \
                } while (0)
#           else
#               define _NO_CORO_IMPL 1
#           endif
#       elif defined(__mips__) && _MIPS_SIM == _MIPS_SIM_ABI32 && \
            !defined(__mips_eabi)
#           define __CORO_STKADJUST 8
#           define __CORO_STARTPARAMS ( \
                int _a, int _b, int _c, int _d, Coro_Fiber* coro \
            )
#           define __CORO_STARTUNUSED \
                { (void)_a; (void)_b; (void)_c; (void)_d; }
#           if __GLIBC__ == 2 || defined(__UCLIBC__) /* glibc2 */
#               define __CORO_CTX_PATCH(coro, buf, func, stack, p) do { \
                    (buf)->__jmpbuf->__pc = __extension__ (void*)(func); \
                    (buf)->__jmpbuf->__sp = (stack); \
                    (buf)->__jmpbuf->__fp = NULL; \
                    (stack)[4] = (p); \
                } while (0)
#           else
#               define _NO_CORO_IMPL 1
#           endif
#       elif defined(__arm__)
#           define __CORO_STKADJUST 2
#           define __CORO_STARTPARAMS ( \
                int _a, int _b, int _c, int _d, Coro_Fiber* coro \
            )
#           define __CORO_STARTUNUSED \
                { (void)_a; (void)_b; (void)_c; (void)_d; }
#           if __GLIBC__ == 2 || defined(__UCLIBC__) /* glibc2 */
#               define __CORO_JMPBUF(buf, x) \
                    ((buf)->__jmpbuf)[((sizeof(__jmp_buf)/sizeof(int))-2)+(x)]
#           elif defined(__APPLE__) /* iOS */
#               define __CORO_JMPBUF (buf)[7+(x)]
#           endif
#           ifdef __CORO_JMPBUF
#               define __CORO_CTX_PATCH(coro, buf, func, stack, param) do { \
                    __CORO_JMPBUF(1) = (intptr_t)( \
                        __extension__ (void*)(func) \
                    ); \
                    __CORO_JMPBUF(0) = (intptr_t)(stack); \
                    __CORO_JMPBUF(-1) = 0; \
                } while (0)
#           else
#               define _NO_CORO_IMPL 1
#           endif
#       else
#           define _NO_CORO_IMPL 1
#       endif

#       ifndef _NO_CORO_IMPL
#           define __CORO_CTX_INIT(coro, ctx, func, stack, param) do { \
                _setjmp(ctx); \
                __CORO_CTX_PATCH( \
                    coro, (_JUMP_BUFFER*)ctx, func, stack, param \
                ); \
            } while (0)
#           define __CORO_SWITCH(from, to) \
                if (!_setjmp(*(from))) _longjmp(*(to), 1);
#       endif
#   endif
#endif
#ifdef _NO_CORO_IMPL /* posix ucontext */
#   if __has_include(<ucontext.h>) || defined(__unix__)
#       include <ucontext.h>
        typedef ucontext_t _Coro_Context;

#       if defined(__LP64__) || INTPTR_MAX != INT32_MAX
#           define __CORO_STARTPARAMS \
                (uint32_t l, uint32_t h)
#           define __CORO_GETPTR Coro_Fiber* p = (Coro_Fiber*)( \
                ((uintptr_t)h << 32) | (uintptr_t)l \
            );
#           define __CORO_CTX_INIT(coro, nf, start) makecontent( \
                &(coro)->ctx, \
                (start), \
                2, \
                (int)(uintptr_t)(nf), \
                (int)((uintptr_t)(nf) >> 32) \
            )
#       else
#           define __CORO_CTX_INIT(coro, nf, start) makecontext( \
                &(coro)->ctx, (start), 1, (int)(uintptr_t)(nf) \
            )
#       endif
#       define __CORO_SETUP(coro, nf, start) { \
            getcontext(&((coro)->ctx)); \
            (coro)->ctx.uc_link = NULL; \
            (coro)->ctx.uc_stack.ss_sp = (coro)->alloc_ptr; \
            (coro)->ctx.uc_stack.ss_size = ( \
                (char*)coro - (char*)((coro)->alloc_ptr) \
            ); \
            __CORO_CTX_INIT(coro, nf, start); \
        }
#       define __CORO_SWITCH(from, to) swapcontext(&(from), &(to));
#   else
#       error "No coroutine implementation available in execution environment."
#   endif
#elif !defined(_USES_WINFIBERS)
#   define __CORO_SETUP(coro, nf, start) { \
        uintptr_t* stkptr = \
            ((uintptr_t*)(coro)->alloc_ptr) - __CORO_STKADJUST \
        ; \
        __CORO_CTX_INIT(coro, (coro)->ctx, start, stkptr, nf); \
    }
#   define __CORO_RESUME(coro)  { __CORO_SWITCH(&(coro)->back, &(coro)->ctx) }
#   define __CORO_SUSPEND(coro) { __CORO_SWITCH(&(coro)->ctx, &(coro)->back) }
#endif

#ifndef __CORO_STKADJUST
#   define __CORO_STKADJUST 1
#endif /* ! __CORO_STKADJUST */
#ifndef __CORO_STATE_HEAD
#   define __CORO_STATE_HEAD
#endif /* !__CORO_STATE_HEAD */
#ifndef __CORO_STARTDECL
#   define __CORO_STARTDECL CDECL
#endif /* !__CORO_STARTDECL */
#ifndef __CORO_STARTPARAMS
#   define __CORO_STARTPARAMS (Coro_Fiber* coro)
#endif /* !__CORO_STARTDECL */
#ifndef __CORO_STARTUNUSED
#   define __CORO_STARTUNUSED
#endif /* !__CORO_STARTUNUSED */
#ifndef __CORO_GETPTR
#   define __CORO_GETPTR
#endif /* !__CORO_GETPTR */
#ifndef CORO_DEFAULT_STACK_SIZE
#   define CORO_DEFAULT_STACK_SIZE 61440
#endif /* !CORO_DEFAULT_STACK_SIZE */
#ifndef CORO_MIN_STACK_SIZE
#   define CORO_MIN_STACK_SIZE 36864
#endif /* !CORO_MIN_STACK_SIZE */

#ifdef _USES_WINFIBERS
#   undef _USES_WINFIBERS
#else
#   if defined(CORO_USE_VALGRIND) || __has_include(<valgrind/valgrind.h>)
#       include <valgrind/valgrind.h>
#       define __CORO_VREG(coro, p, s) \
            (coro)->vid = VALGRIND_STACK_REGISTER((p), (p) + (sz));
#       define __CORO_VUNREG(coro) VALGRIND_STACK_DEREGISTER((coro)->vid);
#       define __CORO_VID unsigned int vid;
#   else
#       define __CORO_VREG(coro, p, s)
#       define __CORO_VUNREG(coro)
#       define __CORO_VID
#   endif

    struct Coro_Fiber {
        __CORO_STATE_HEAD
        __CORO_VID
        _Coro_Context ctx, back;
        Coro_Function fn;
        uintptr_t up;
        void* alloc_ptr;
        size_t alloc_size;
    };

#   ifdef __unix__
#       include <sys/mman.h>
#       include <unistd.h>
#       ifndef MAP_STACK
#           define MAP_STACK 0
#       endif
#       ifndef MAP_PRIVATE
#           define MAP_PRIVATE 0
#       endif

#       define __ALIGNED_END(p, s, t) \
            ((t*)(((char*)0) + ((((char*)(p)-(char*)0)+(s)-sizeof(t)) & -16)))
#       define __CORO_INIT(coro, start, param, stksz) do { \
            if (!pagesize) \
                pagesize = sysconf(_SC_PAGESIZE); \
            coro->alloc_size = MAX(stksz, pagesize); \
            coro->alloc_size = !(coro->alloc_size % pagesize) ? \
                coro->alloc_size : \
                coro->alloc_size + \
                    (pagesize - coro->alloc_size % pagesize); \
            if (((coro)->alloc_ptr = mmap( \
                NULL, coro->alloc_size, \
                PROT_READ | PROT_WRITE, \
                MAP_ANON | MAP_STACK | MAP_PRIVATE, \
                0, 0 \
            )) == MAP_FAILED) \
                return false; \
            __CORO_VREG(coro, (coro)->alloc_ptr, stksz) \
            __CORO_SETUP(coro, param, start) \
            return true; \
        } while (0)
#       define __CORO_DESTROY(coro) { \
            __CORO_VUNREG(coro) \
            munmap((coro)->alloc_ptr, (coro)->alloc_size); \
            (coro)->alloc_ptr = NULL; \
        }
#   else
#       define __ALIGNED_END(p, s, t) \
            ((t*)(((char*)0) + ((((char*)(p)-(char*)0)+(s)-sizeof(t)) & -16)))
#       define __CORO_INIT(coro, start, param, stksz) do { \
            if (!((coro)->alloc_ptr = malloc(stksz))) \
                return false; \
            __CORO_VREG(coro, (coro)->alloc_ptr, stksz) \
            coro->alloc_size = (stksz); \
            __CORO_SETUP(coro, param, start) \
            return true; \
        } while (0)
#       define __CORO_DESTROY(coro) { \
            __CORO_VUNREG(coro) \
            free((coro)->alloc_ptr); \
            (coro)->alloc_ptr = NULL; \
        }
#   endif
#endif

static void __CORO_STARTDECL __coro_start __CORO_STARTPARAMS {
    __CORO_STARTUNUSED __CORO_GETPTR
    exit((*coro->fn)(coro, coro->up));
}

static_force_inline bool coro_init(
    Coro_Fiber *const coro,
    Coro_Function func,
    uintptr_t param,
    size_t stack_size
) {
#ifdef __unix__
    static long pagesize;
#endif

    if (!stack_size)
        stack_size = CORO_DEFAULT_STACK_SIZE;
    else if (stack_size < CORO_MIN_STACK_SIZE)
        stack_size = CORO_MIN_STACK_SIZE;

    coro->fn = func;
    coro->up = param;
    __CORO_INIT(
        coro,
        __coro_start,
        (uintptr_t)coro,
        stack_size
    );
}

static_force_inline void coro_destroy(
    Coro_Fiber *const coro
) __CORO_DESTROY(coro)

static_force_inline void coro_resume(
    Coro_Fiber *const coro
) __CORO_RESUME(coro)

static_force_inline void coro_suspend(
    Coro_Fiber *const coro
) __CORO_SUSPEND(coro)

#define __coro_entry
#define __coro_switch
#define __coro_start
#undef __CORO_VREG
#undef __CORO_VUNREG
#undef __CORO_VID
#undef __CORO_INIT
#undef __CORO_DESTROY
#undef __CORO_RESUME
#undef __CORO_SUSPEND
#undef __CORO_GETPTR
#undef __CORO_STARTDECL
#undef __CORO_STARTDECL
#undef __CORO_STARTPARAMS
#undef __CORO_STARTUNUSED
#undef __CORO_STKADJUST
#undef __CORO_STATE_HEAD
#ifdef __ALIGNED_END
#   undef __ALIGNED_END
#endif /* __ALIGNED_END */
#ifdef __CORO_SWITCH
#   undef __CORO_SWITCH
#endif /* __CORO_SWITCH */
#ifdef __CORO_JMPBUF
#   undef __CORO_JMPBUF
#endif /* __CORO_JMPBUF */
#ifdef __CORO_CTX_PATCH
#   undef __CORO_CTX_PATCH
#endif /* __CORO_CTX_PATCH */
#ifdef __CORO_CTX_EXTRA
#   undef __CORO_CTX_EXTRA
#endif /* __CORO_CTX_EXTRA */
#ifdef __CORO_CTX_INIT
#   undef __CORO_CTX_INIT
#endif /* __CORO_CTX_INIT */

#endif /* CORO_H_ */
