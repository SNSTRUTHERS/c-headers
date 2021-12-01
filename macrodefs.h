/**
 * @file macrodefs.h
 * @author Simon Bolivar
 * @date 01 Dec 2021
 * 
 * @brief File containing general-use definitions, annotations, and
 *        macro definitions.
 * 
 * @copyright LGPL3
 */

#ifndef MACRODEFS_H_
#define MACRODEFS_H_

/* == C & C++ VERSION CHECK MACROS ========================================== */

/**
 * @def CPP_PREREQ(ver)
 * @brief Checks the C++ version, even when not compiling in C++.
 * 
 * @param[in] ver The C++ version to check against.
 */
/**
 * @def STDC_PREREQ(ver)
 * @brief Checks the standard C version, even when not compiling in standard C.
 * 
 * @param[in] ver The standard C version to check against.
 */
#ifdef __cplusplus
#   define __MACRODEFS_CPP_VERSION __cplusplus
#   define __MACRODEFS_C_VERSION 0L
#else
#   define __MACRODEFS_CPP_VERSION 0L
#endif
#define CPP_PREREQ(ver) ((ver) <= __MACRODEFS_CPP_VERSION)
#ifndef __MACRODEFS_C_VERSION
#   if defined(__STDC_VERSION__)
#       define __MACRODEFS_C_VERSION __STDC_VERSION__
#   elif defined(__STDC__) || (defined(_MSC_VER) && (_MSC_VER >= 1))
#       define __MACRODEFS_C_VERSION 198901L
#   else
#       define __MACRODEFS_C_VERSION 0L
#   endif
#endif
#define STDC_PREREQ(ver) ((ver) <= __MACRODEFS_C_VERSION)

#if !STDC_PREREQ(1L) && !CPP_PREREQ(1L)
#   error "macrodefs.h only supports standard C or C++ compilers."
    /*  if we can't force an error via a preprocessor directive,
        we'll brute force one instead */
    int }}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
#endif

/* == MAJOR COMPILER VERSION CHECK MACROS =================================== */

/**
 * @def GCC_PREREQ(ver)
 * @brief Checks whether the compiler supports a given version of the GCC ABI.
 * 
 * @note M = major version, m = minor version, P = patch level
 * 
 * @param ver A GCC version number in the format MMmmPP.
 */
/**
 * @def CLANG_PREREQ(ver)
 * @brief Checks whether the compiler is at or a above a given Clang version.
 * 
 * @note M = major version, m = minor version, P = patch level
 * 
 * @param ver A Clang version number in the format MMmmPP.
 */
/**
 * @def MSVC_PREREQ(ver)
 * @brief Checks whether the compiler is at or a above a given MSVC version.
 * 
 * @param ver A _MSC_VER-style version number.
 */
#ifdef __GNUC__
#   ifndef __GNUC_PATCHLEVEL__
#       define __GNUC_PATCHLEVEL__ 0
#   endif
#   define GCC_PREREQ(ver) ((ver) <= ( \
        (__GNUC__ * 10000) + (__GNUC_MINOR__ * 100) + __GNUC_PATCHLEVEL__ \
    ))
#else
#   define GCC_PREREQ(ver) 0
#endif
#ifdef __clang__
#   define CLANG_PREREQ(ver) ((ver) <= ( \
        (__clang_major__ * 10000) + (__clang_minor__ * 100) + \
        __clang_patchlevel__ \
    ))
#else
#   define CLANG_PREREQ(ver) 0
#endif
#ifdef __SUNPRO_C
#   define SUN_PREREQ(ver) ((ver) <= __SUNPRO_C)
#else
#   define SUN_PREREQ(ver) 0
#endif
#ifdef _MSC_VER
#   define MSVC_PREREQ(ver) ((ver) <= _MSC_VER)
#   ifndef _MSVC_TRADITIONAL
#       define _MSVC_TRADITIONAL 1
#   endif
#else
#   define MSVC_PREREQ(ver) 0
#endif /* ICC <1400 lies and reports GCC4.3 compatibility when it doesn't */
#if defined(__ICC) && (__ICC < 1400) && GCC_PREREQ(40300)
#   undef __GNUC_MINOR__
#   define __GNUC_MINOR__ 2
#   undef __GNUC_PATCHLEVEL__
#   define __GNUC_PATCHLEVEL__ 0
#endif

#if !GCC_PREREQ(1)
#   define __extension__
#endif

/* == DISABLE STUPID WARNINGS =============================================== */

#ifdef __GNUC__
#   ifdef __clang__
#       pragma clang diagnostic ignored "-Wnon-literal-null-conversion"
#       pragma clang diagnostic ignored "-Wswitch-bool"
#       pragma clang diagnostic ignored "-Wunknown-pragmas"
#   else
#       pragma GCC diagnostic ignored "-Wmissing-braces"
#       pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#       pragma GCC diagnostic ignored "-Wunknown-pragmas"
#       ifdef __OPEN64__
#           pragma GCC diagnostic ignored "-Wswitch-bool"
#       endif
#   endif
#elif MSVC_PREREQ(1500)
#   pragma warning(disable: 4068) /* ignore unknown pragmas */
#endif

/* == METAPROGRAMMING MACROS ================================================ */

/**
 * @def CONCATENATE(x, y)
 * @brief Concatenate two expanded tokens together.
 * 
 * @param[in] x Left token.
 * @param[in] y Right token.
 */
/**
 * @def STRINGIFY(x)
 * @brief Expands and converts a token into a string literal.
 * 
 * @param[in] x Token to stringify.
 */
#define __CONCATENATE_(x, y) x ##y
#define _CONCATENATE(x, y) __CONCATENATE_(x, y)
#define CONCATENATE(x, y) _CONCATENATE(x, y)
#define __STRINGIFY_(x) #x
#define _STRINGIFY(x) __STRINGIFY_(x)
#define STRINGIFY(x) _STRINGIFY(x)

/* == VARIADIC MACRO METAPROGRAMMING ======================================== */

/**
 * @def VARGPACK(...)
 * @brief Unpacks a set of variadic arguments to be used as a single token.
 * 
 * @param[in] ... Parameters to unpack.
 */
/**
 * @def VARGCOUNT(...)
 * @brief Counts how many arguments there are in a variadic macro.
 * @note Can only count up to 15 parameters. Cannot count less than 1
 *       parameter.
 * 
 * @param[in] ... Parameters to count.
 */
#if MSVC_PREREQ(1) || STDC_PREREQ(199901L) || CPP_PREREQ(201103L)
#   define _VARGCOUNT( \
        _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _a_, _b_, _c_, _d_, _e_, \
        _f_,  c, ...) c
#   define VARGPACK(...) __VA_ARGS__
#   define VARGCOUNT(...) _VARGCOUNT( \
        __VA_ARGS__, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 \
    )
#elif GCC_PREREQ(30000) && !(STDC_PREREQ(199901L) || CPP_PREREQ(201103L))
    __extension__
#   define _VARGCOUNT( \
        _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _a_, _b_, _c_, _d_, _e_, \
        _f_,  c, ...) c
    ;__extension__
#   define VARGPACK(...) __VA_ARGS__
    ;__extension__
#   define VARGCOUNT(...) _VARGCOUNT( \
        __VA_ARGS__, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 \
    )
    ;
#   define _EXT_VA_ARGS 1
#elif GCC_PREREQ(1) /* GNU C varargs */
#   define _VARGCOUNT( \
        _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _a_, _b_, _c_, _d_, _e_, \
        _f_,  c, args...) c
#   define VARGPACK(args...) args
#   define VARGCOUNT(args...) _VARGCOUNT( \
        args, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 \
    )
#   define _GNUC_VA_ARGS 1
#else
#   define _NO_VA_ARGS 1
#endif

/* == COMPILER & ARCHITECTURE STRING ======================================== */

/**
 * @def COMPILER_NAME
 * @brief Name of the compiler processing the source code.
 */
/**
 * @def OS_NAME
 * @brief Name of the operating system the source code is being compiled for.
 */
/**
 * @def ARCH_NAME
 * @brief Name of the processor or machine architecture the source code is being
 *        compiled for.
 */
#if (defined(_WIN64) || defined(__WIN32__) || defined(__WIN32) || \
    defined(__WINDOWS__) ||  defined(__WIN64) || defined(__WIN64__) || \
    defined(__TOS_WIN__)) && !defined(_WIN32)
#   define _WIN32 1
#endif
#if defined(_WIN32) && (defined(__x86_64__) || defined(__aarch64__) || \
    defined(__ia64__) || defined(__powerpc64__) || defined(__WIN64) || \
    defined(__WIN64__)) && !defined(_WIN64)
#   define _WIN64 1
#endif
#if (defined(unix) || defined(__unix)) && !defined(__unix__)
#   define __unix__ 1
#endif
#if defined(sun) && !defined(__sun)
#   define __sun 1
#endif
#if (defined(OS2) || defined(_OS2) || defined(__TOS_OS2__)) && !defined(__OS2__)
#   define __OS2__ 1
#endif
#if defined(__LP64__) || defined(_LP64) || defined(__64BIT__)
#   ifndef __LP64__ /* long and void* are 64-bits wide */
#       define __LP64__ 1
#   endif
#endif
#ifdef __INTEL_COMPILER
#   if __INTEL_COMPILER == 500
#       define COMPILER_NAME "Intel C++ Compiler 5.0"
#   elif __INTEL_COMPILER == 600
#       define COMPILER_NAME "Intel C++ Compiler 6.0"
#   elif __INTEL_COMPILER == 700
#       define COMPILER_NAME "Intel C++ Compiler 7.0"
#   elif __INTEL_COMPILER == 800
#       define COMPILER_NAME "Intel C++ Compiler 8.0"
#   elif __INTEL_COMPILER == 810
#       define COMPILER_NAME "Intel C++ Compiler 8.1"
#   elif __INTEL_COMPILER == 900
#       define COMPILER_NAME "Intel C++ Compiler 9.0"
#   elif __INTEL_COMPILER == 1000
#       define COMPILER_NAME "Intel C++ Compiler 10.0"
#   elif __INTEL_COMPILER == 1010
#       define COMPILER_NAME "Intel C++ Compiler 10.1"
#   elif __INTEL_COMPILER == 1100
#       define COMPILER_NAME "Intel C++ Compiler 11.0"
#   elif __INTEL_COMPILER == 1110
#       define COMPILER_NAME "Intel C++ Compiler 11.1"
#   elif __INTEL_COMPILER == 1200
#       define COMPILER_NAME "Intel C++ Composer XE 2011"
#   elif __INTEL_COMPILER == 1210
#       define COMPILER_NAME "Intel C++ Composer XE 2011 (Update 6)"
#   elif __INTEL_COMPILER == 1300
#       define COMPILER_NAME "Intel C++ Composer XE 2013"
#   elif __INTEL_COMPILER / 100 == 14
#       define COMPILER_NAME "Intel C++ Composer XE 2013 SP1"
#   elif __INTEL_COMPILER / 100 == 15
#       define COMPILER_NAME "Intel C++ Composer XE 2015"
#   elif __INTEL_COMPILER == 1600
#       define COMPILER_NAME "Intel C++ 16.0"
#   elif __INTEL_COMPILER == 1700
#       define COMPILER_NAME "Intel C++ 17.0"
#   elif __INTEL_COMPILER == 1800
#       define COMPILER_NAME "Intel C++ 18.0"
#   elif __INTEL_COMPILER == 1900
#       define COMPILER_NAME "Intel C++ 19.0"
#   elif __INTEL_COMPILER == 1910
#       define COMPILER_NAME "Intel C++ Compiler Classic 19.1"
#   elif __INTEL_COMPILER == 2021
#       define COMPILER_NAME "Intel C++ Compiler Classic 2021"
#   else
#       define COMPILER_NAME "Intel C/C++"
#   endif
#elif defined(__DMC__)
#   if __DMC__ & 0xf00 == 0x900
#       define __MACRODEFS_DMC_MAJOR 9
#   elif __DMC__ & 0xf00 == 0x800
#       define __MACRODEFS_DMC_MAJOR 8
#   elif __DMC__ & 0xf00 == 0x700
#       define __MACRODEFS_DMC_MAJOR 7
#   elif __DMC__ & 0xf00 == 0x600
#       define __MACRODEFS_DMC_MAJOR 6
#   elif __DMC__ & 0xf00 == 0x500
#       define __MACRODEFS_DMC_MAJOR 5
#   elif __DMC__ & 0xf00 == 0x400
#       define __MACRODEFS_DMC_MAJOR 4
#   elif __DMC__ & 0xf00 == 0x300
#       define __MACRODEFS_DMC_MAJOR 3
#   elif __DMC__ & 0xf00 == 0x200
#       define __MACRODEFS_DMC_MAJOR 2
#   elif __DMC__ & 0xf00 == 0x100
#       define __MACRODEFS_DMC_MAJOR 1
#   else
#       define __MACRODEFS_DMC_MAJOR 0
#   endif
#   if __DMC__ & 0x0f0 == 0x090
#       define __MACRODEFS_DMC_MINOR 9
#   elif __DMC__ & 0x0f0 == 0x080
#       define __MACRODEFS_DMC_MINOR 8
#   elif __DMC__ & 0x0f0 == 0x070
#       define __MACRODEFS_DMC_MINOR 7
#   elif __DMC__ & 0x0f0 == 0x060
#       define __MACRODEFS_DMC_MINOR 6
#   elif __DMC__ & 0x0f0 == 0x050
#       define __MACRODEFS_DMC_MINOR 5
#   elif __DMC__ & 0x0f0 == 0x040
#       define __MACRODEFS_DMC_MINOR 4
#   elif __DMC__ & 0x0f0 == 0x030
#       define __MACRODEFS_DMC_MINOR 3
#   elif __DMC__ & 0x0f0 == 0x020
#       define __MACRODEFS_DMC_MINOR 2
#   elif __DMC__ & 0x0f0 == 0x010
#       define __MACRODEFS_DMC_MINOR 1
#   else
#       define __MACRODEFS_DMC_MINOR 0
#   endif
#   define COMPILER_NAME \
        "Digital Mars C/C++ " STRINGIFY(__MACRODEFS_DMC_MAJOR) "." \
        STRINGIFY(__MACRODEFS_DMC_MINOR)
#elif defined(__BORLANDC__)
#   if __BORLANDC__ == 0x200
#       define COMPILER_NAME "Borland C++ 2.0"
#   elif __BORLANDC__ == 0x400
#       define COMPILER_NAME "Borland C++ 3.0"
#   elif __BORLANDC__ == 0x410
#       define COMPILER_NAME "Borland C++ 3.1"
#   elif __BORLANDC__ == 0x452
#       define COMPILER_NAME "Borland C++ 4.0"
#   elif __BORLANDC__ == 0x500
#       define COMPILER_NAME "Borland C++ 5.0"
#   elif __BORLANDC__ == 0x520
#       define COMPILER_NAME "Borland C++Builder 1.0"
#   elif __BORLANDC__ == 0x530
#       define COMPILER_NAME "Borland C++Builder 3.0"
#   elif __BORLANDC__ == 0x540
#       define COMPILER_NAME "Borland C++Builder 4.0"
#   elif __BORLANDC__ == 0x550
#       define COMPILER_NAME "Borland C++Builder 5.0"
#   elif __BORLANDC__ == 0x551
#       define COMPILER_NAME "Borland C++ 5.5.1"
#   elif __BORLANDC__ == 0x562
#       define COMPILER_NAME "Borland C++ 5.6.4"
#   elif __BORLANDC__ == 0x570
#       define COMPILER_NAME "Borland C++Builder 2006"
#   elif __BORLANDC__ == 0x590
#       define COMPILER_NAME "Borland C++Builder 2007"
#   elif __BORLANDC__ == 0x613
#       define COMPILER_NAME "Borland C++Builder 2009"
#   elif __BORLANDC__ == 0x621
#       define COMPILER_NAME "C++Builder 2010"
#   elif __BORLANDC__ == 0x630
#       define COMPILER_NAME "C++Builder XE"
#   elif __BORLANDC__ == 0x640
#       define COMPILER_NAME "C++Builder XE2"
#   elif __BORLANDC__ == 0x650
#       define COMPILER_NAME "C++Builder XE3"
#   elif __BORLANDC__ == 0x660
#       define COMPILER_NAME "C++Builder XE4"
#   elif __BORLANDC__ == 0x670
#       define COMPILER_NAME "C++Builder XE5"
#   elif __BORLANDC__ == 0x680
#       define COMPILER_NAME "C++Builder XE6"
#   elif __BORLANDC__ == 0x690
#       define COMPILER_NAME "C++Builder XE7"
#   else
#       define COMPILER_NAME "C++Builder"
#   endif
#elif defined(SDCC)
#   if SDCC / 100 == 1
#       define __MACRODEFS_SDCC_MAJOR 1
#   elif SDCC / 100 == 2
#       define __MACRODEFS_SDCC_MAJOR 2
#   elif SDCC / 100 == 3
#       define __MACRODEFS_SDCC_MAJOR 3
#   elif SDCC / 100 == 4
#       define __MACRODEFS_SDCC_MAJOR 4
#   elif SDCC / 100 == 5
#       define __MACRODEFS_SDCC_MAJOR 5
#   elif SDCC / 100 == 6
#       define __MACRODEFS_SDCC_MAJOR 6
#   elif SDCC / 100 == 7
#       define __MACRODEFS_SDCC_MAJOR 7
#   elif SDCC / 100 == 8
#       define __MACRODEFS_SDCC_MAJOR 8
#   elif SDCC / 100 == 9
#       define __MACRODEFS_SDCC_MAJOR 9
#   else
#       define __MACRODEFS_SDCC_MAJOR 0
#   endif
#   if (SDCC % 100) / 10 == 1
#       define __MACRODEFS_SDCC_MINOR 1
#   elif (SDCC % 100) / 10 == 2
#       define __MACRODEFS_SDCC_MINOR 2
#   elif (SDCC % 100) / 10 == 3
#       define __MACRODEFS_SDCC_MINOR 3
#   elif (SDCC % 100) / 10 == 4
#       define __MACRODEFS_SDCC_MINOR 4
#   elif (SDCC % 100) / 10 == 5
#       define __MACRODEFS_SDCC_MINOR 5
#   elif (SDCC % 100) / 10 == 6
#       define __MACRODEFS_SDCC_MINOR 6
#   elif (SDCC % 100) / 10 == 7
#       define __MACRODEFS_SDCC_MINOR 7
#   elif (SDCC % 100) / 10 == 8
#       define __MACRODEFS_SDCC_MINOR 8
#   elif (SDCC % 100) / 10 == 9
#       define __MACRODEFS_SDCC_MINOR 9
#   else
#       define __MACRODEFS_SDCC_MINOR 0
#   endif
#   if SDCC % 100 == 1
#       define __MACRODEFS_SDCC_PATCH 1
#   elif SDCC % 100 == 2
#       define __MACRODEFS_SDCC_PATCH 2
#   elif SDCC % 100 == 3
#       define __MACRODEFS_SDCC_PATCH 3
#   elif SDCC % 100 == 4
#       define __MACRODEFS_SDCC_PATCH 4
#   elif SDCC % 100 == 5
#       define __MACRODEFS_SDCC_PATCH 5
#   elif SDCC % 100 == 6
#       define __MACRODEFS_SDCC_PATCH 6
#   elif SDCC % 100 == 7
#       define __MACRODEFS_SDCC_PATCH 7
#   elif SDCC % 100 == 8
#       define __MACRODEFS_SDCC_PATCH 8
#   elif SDCC % 100 == 9
#       define __MACRODEFS_SDCC_PATCH 9
#   else
#       define __MACRODEFS_SDCC_PATCH 0
#   endif
#   define COMPILER_NAME \
        "Small Device C " STRINGIFY(__MACRODEFS_SDCC_MAJOR) "." \
        STRINGIFY(__MACRODEFS_SDCC_MINOR) "." STRINGIFY(__MACRODEFS_SDCC_PATCH)
#elif defined(__ghs__)
#   if __GHS_VERSION_NUMBER__ / 100 == 9
#       define __MACRODEFS_GHS_MAJOR 9
#   elif __GHS_VERSION_NUMBER__ / 100 == 8
#       define __MACRODEFS_GHS_MAJOR 8
#   elif __GHS_VERSION_NUMBER__ / 100 == 7
#       define __MACRODEFS_GHS_MAJOR 7
#   elif __GHS_VERSION_NUMBER__ / 100 == 6
#       define __MACRODEFS_GHS_MAJOR 6
#   elif __GHS_VERSION_NUMBER__ / 100 == 5
#       define __MACRODEFS_GHS_MAJOR 5
#   elif __GHS_VERSION_NUMBER__ / 100 == 4
#       define __MACRODEFS_GHS_MAJOR 4
#   elif __GHS_VERSION_NUMBER__ / 100 == 3
#       define __MACRODEFS_GHS_MAJOR 3
#   elif __GHS_VERSION_NUMBER__ / 100 == 2
#       define __MACRODEFS_GHS_MAJOR 2
#   elif __GHS_VERSION_NUMBER__ / 100 == 1
#       define __MACRODEFS_GHS_MAJOR 1
#   else
#       define __MACRODEFS_GHS_MAJOR 0
#   endif
#   if (__GHS_VERSION_NUMBER__ % 100) / 10 == 9
#       define __MACRODEFS_GHS_MINOR 9
#   elif (__GHS_VERSION_NUMBER__ % 100) / 10 == 8
#       define __MACRODEFS_GHS_MINOR 8
#   elif (__GHS_VERSION_NUMBER__ % 100) / 10 == 7
#       define __MACRODEFS_GHS_MINOR 7
#   elif (__GHS_VERSION_NUMBER__ % 100) / 10 == 6
#       define __MACRODEFS_GHS_MINOR 6
#   elif (__GHS_VERSION_NUMBER__ % 100) / 10 == 5
#       define __MACRODEFS_GHS_MINOR 5
#   elif (__GHS_VERSION_NUMBER__ % 100) / 10 == 4
#       define __MACRODEFS_GHS_MINOR 4
#   elif (__GHS_VERSION_NUMBER__ % 100) / 10 == 3
#       define __MACRODEFS_GHS_MINOR 3
#   elif (__GHS_VERSION_NUMBER__ % 100) / 10 == 2
#       define __MACRODEFS_GHS_MINOR 2
#   elif (__GHS_VERSION_NUMBER__ % 100) / 10 == 1
#       define __MACRODEFS_GHS_MINOR 1
#   else
#       define __MACRODEFS_GHS_MINOR 0
#   endif
#   if __GHS_VERSION_NUMBER__ % 10 == 9
#       define __MACRODEFS_GHS_PATCH 9
#   elif __GHS_VERSION_NUMBER__ % 10 == 8
#       define __MACRODEFS_GHS_PATCH 8
#   elif __GHS_VERSION_NUMBER__ % 10 == 7
#       define __MACRODEFS_GHS_PATCH 7
#   elif __GHS_VERSION_NUMBER__ % 10 == 6
#       define __MACRODEFS_GHS_PATCH 6
#   elif __GHS_VERSION_NUMBER__ % 10 == 5
#       define __MACRODEFS_GHS_PATCH 5
#   elif __GHS_VERSION_NUMBER__ % 10 == 4
#       define __MACRODEFS_GHS_PATCH 4
#   elif __GHS_VERSION_NUMBER__ % 10 == 3
#       define __MACRODEFS_GHS_PATCH 3
#   elif __GHS_VERSION_NUMBER__ % 10 == 2
#       define __MACRODEFS_GHS_PATCH 2
#   elif __GHS_VERSION_NUMBER__ % 10 == 1
#       define __MACRODEFS_GHS_PATCH 1
#   else
#       define __MACRODEFS_GHS_PATCH 0
#   endif
#   define COMPILER_NAME \
        "Green Hills C/C++ " STRINGIFY(__MACRODEFS_GHS_MAJOR) "." \
        STRINGIFY(__MACRODEFS_GHS_MINOR) "." STRINGIFY(__MACRODEFS_GHS_PATCH)
#elif defined(__SUNPRO_C)
#   if __SUNPRO_C == 0x420
#       define COMPILER_NAME "Sun Workshop 4.0"
#   elif __SUNPRO_C == 0x500
#       define COMPILER_NAME "Sun Workshop 5.0"
#   elif __SUNPRO_C == 0x510
#       define COMPILER_NAME "Forte Developer 6"
#   elif __SUNPRO_C == 0x520
#       define COMPILER_NAME "Forte Developer 6 Update 1"
#   elif __SUNPRO_C == 0x530
#       define COMPILER_NAME "Forte Developer 6 Update 2"
#   elif __SUNPRO_C == 0x540
#       define COMPILER_NAME "Sun ONE Studio 7"
#   elif __SUNPRO_C == 0x550
#       define COMPILER_NAME "Sun ONE Studio 8"
#   elif __SUNPRO_C == 0x560
#       define COMPILER_NAME "Sun Studio 9"
#   elif __SUNPRO_C == 0x570
#       define COMPILER_NAME "Sun Studio 10"
#   elif __SUNPRO_C == 0x580
#       define COMPILER_NAME "Sun Studio 11"
#   elif __SUNPRO_C == 0x590
#       define COMPILER_NAME "Sun Studio 12"
#   elif __SUNPRO_C == 0x5100
#       define COMPILER_NAME "Sun Studio 12 Update 1"
#   elif __SUNPRO_C == 0x5110
#       define COMPILER_NAME "Oracle Solaris Studio 12.2"
#   elif __SUNPRO_C == 0x5120
#       define COMPILER_NAME "Oracle Solaris Studio 12.3"
#   elif __SUNPRO_C == 0x5130
#       define COMPILER_NAME "Oracle Solaris Studio 12.4"
#   elif __SUNPRO_C == 0x5140
#       define COMPILER_NAME "Oracle Solaris Studio 12.5"
#   elif __SUNPRO_C == 0x5150
#       define COMPILER_NAME "Oracle Solaris Studio 12.6"
#   else
#       define COMPILER_NAME "Oracle Developer Studio"
#   endif
#elif defined(__CC_ARM)
#   if __ARMCC_VERSION / 100000 == 1
#       define __MACRODEFS_ARMCC_MAJOR 1
#   elif __ARMCC_VERSION / 100000 == 2
#       define __MACRODEFS_ARMCC_MAJOR 2
#   elif __ARMCC_VERSION / 100000 == 3
#       define __MACRODEFS_ARMCC_MAJOR 3
#   else
#       define __MACRODEFS_ARMCC_MAJOR 0
#   endif
#   if (__ARMCC_VERSION % 10000) / 10 == 1
#       define __MACRODEFS_ARMCC_MINOR 1
#   elif (__ARMCC_VERSION % 10000) / 10 == 2
#       define __MACRODEFS_ARMCC_MINOR 2
#   elif (__ARMCC_VERSION % 10000) / 10 == 3
#       define __MACRODEFS_ARMCC_MINOR 3
#   elif (__ARMCC_VERSION % 10000) / 10 == 4
#       define __MACRODEFS_ARMCC_MINOR 4
#   elif (__ARMCC_VERSION % 10000) / 10 == 5
#       define __MACRODEFS_ARMCC_MINOR 5
#   elif (__ARMCC_VERSION % 10000) / 10 == 6
#       define __MACRODEFS_ARMCC_MINOR 6
#   elif (__ARMCC_VERSION % 10000) / 10 == 7
#       define __MACRODEFS_ARMCC_MINOR 7
#   elif (__ARMCC_VERSION % 10000) / 10 == 8
#       define __MACRODEFS_ARMCC_MINOR 8
#   elif (__ARMCC_VERSION % 10000) / 10 == 9
#       define __MACRODEFS_ARMCC_MINOR 9
#   else
#       define __MACRODEFS_ARMCC_MINOR 0
#   endif
#   define COMPILER_NAME \
        "ARM RealView " STRINGIFY(__MACRODEFS_ARMCC_MAJOR) \
        "." STRINGIFY(__MACRODEFS_ARMCC_MINOR)
#elif defined(__WATCOMC__)
#   if __WATCOMC__ / 100 == 1
#       define __MACRODEFS_WATCOM_MAJOR 1
#   elif __WATCOMC__ / 100 == 2
#       define __MACRODEFS_WATCOM_MAJOR 2
#   elif __WATCOMC__ / 100 == 3
#       define __MACRODEFS_WATCOM_MAJOR 3
#   elif __WATCOMC__ / 100 == 4
#       define __MACRODEFS_WATCOM_MAJOR 4
#   elif __WATCOMC__ / 100 == 5
#       define __MACRODEFS_WATCOM_MAJOR 5
#   elif __WATCOMC__ / 100 == 6
#       define __MACRODEFS_WATCOM_MAJOR 6
#   elif __WATCOMC__ / 100 == 7
#       define __MACRODEFS_WATCOM_MAJOR 7
#   elif __WATCOMC__ / 100 == 8
#       define __MACRODEFS_WATCOM_MAJOR 8
#   elif __WATCOMC__ / 100 == 9
#       define __MACRODEFS_WATCOM_MAJOR 9
#   elif __WATCOMC__ / 100 == 10
#       define __MACRODEFS_WATCOM_MAJOR 10
#   elif __WATCOMC__ / 100 == 11
#       define __MACRODEFS_WATCOM_MAJOR 11
#   elif __WATCOMC__ / 100 == 12
#       define __MACRODEFS_WATCOM_MAJOR 1
#   elif __WATCOMC__ / 100 == 13
#       define __MACRODEFS_WATCOM_MAJOR 2
#   else
#       define __MACRODEFS_WATCOM_MAJOR 0
#   endif
#   if (__WATCOMC__ % 100) / 10 == 1
#       define __MACRODEFS_WATCOM_MINOR 1
#   elif (__WATCOMC__ % 100) / 10 == 2
#       define __MACRODEFS_WATCOM_MINOR 2
#   elif (__WATCOMC__ % 100) / 10 == 3
#       define __MACRODEFS_WATCOM_MINOR 3
#   elif (__WATCOMC__ % 100) / 10 == 4
#       define __MACRODEFS_WATCOM_MINOR 4
#   elif (__WATCOMC__ % 100) / 10 == 5
#       define __MACRODEFS_WATCOM_MINOR 5
#   elif (__WATCOMC__ % 100) / 10 == 6
#       define __MACRODEFS_WATCOM_MINOR 6
#   elif (__WATCOMC__ % 100) / 10 == 7
#       define __MACRODEFS_WATCOM_MINOR 7
#   elif (__WATCOMC__ % 100) / 10 == 8
#       define __MACRODEFS_WATCOM_MINOR 8
#   elif (__WATCOMC__ % 100) / 10 == 9
#       define __MACRODEFS_WATCOM_MINOR 9
#   endif
#   if __WATCOMC__ < 1200
#       define __MACRODEFS_WATCOM_PREFIX
#   else
#       define __MACRODEFS_WATCOM_PREFIX "Open "
#   endif
#   define COMPILER_NAME \
        __MACRODEFS_WATCOM_PREFIX "Watcom C++ " \
        STRINGIFY(__MACRODEFS_WATCOM_MAJOR) "." \
        STRINGIFY(__MACRODEFS_WATCOM_MINOR)
#elif defined(_MSC_VER)
#   if _MSC_VER == 1000
#       define __MACRODEFS_MSVC "4.0"
#   elif _MSC_VER == 1020
#       define __MACRODEFS_MSVC "4.2"
#   elif _MSC_VER == 1100
#       define __MACRODEFS_MSVC "5.0"
#   elif _MSC_VER == 1200
#       define __MACRODEFS_MSVC "6.0"
#   elif _MSC_VER == 1300
#       define __MACRODEFS_MSVC ".NET 2002 7.0"
#   elif _MSC_VER == 1310
#       define __MACRODEFS_MSVC ".NET 2003 7.1"
#   elif _MSC_VER == 1400
#       define __MACRODEFS_MSVC "2005 8.0"
#   elif _MSC_VER == 1500
#       define __MACRODEFS_MSVC "2008 9.0"
#   elif _MSC_VER == 1600
#       define __MACRODEFS_MSVC "2010 10.0"
#   elif _MSC_VER == 1700
#       define __MACRODEFS_MSVC "2012 11.0"
#   elif _MSC_VER == 1800
#       define __MACRODEFS_MSVC "2013 12.0"
#   elif _MSC_VER == 1900
#       define __MACRODEFS_MSVC "2015 14.0"
#   elif _MSC_VER == 1910
#       define __MACRODEFS_MSVC "2017 15.0"
#   elif _MSC_VER == 1911
#       define __MACRODEFS_MSVC "2017 15.3"
#   elif _MSC_VER == 1912
#       define __MACRODEFS_MSVC "2017 15.5"
#   elif _MSC_VER == 1913
#       define __MACRODEFS_MSVC "2017 15.6"
#   elif _MSC_VER == 1914
#       define __MACRODEFS_MSVC "2017 15.7"
#   elif _MSC_VER == 1915
#       define __MACRODEFS_MSVC "2017 15.8"
#   elif _MSC_VER == 1916
#       define __MACRODEFS_MSVC "2017 15.9"
#   elif _MSC_VER == 1920
#       define __MACRODEFS_MSVC "2019 16.0"
#   elif _MSC_VER == 1921
#       define __MACRODEFS_MSVC "2019 16.1"
#   elif _MSC_VER == 1922
#       define __MACRODEFS_MSVC "2019 16.2"
#   elif _MSC_VER == 1923
#       define __MACRODEFS_MSVC "2019 16.3"
#   elif _MSC_VER == 1924
#       define __MACRODEFS_MSVC "2019 16.4"
#   elif _MSC_VER == 1925
#       define __MACRODEFS_MSVC "2019 16.5"
#   elif _MSC_VER == 1926
#       define __MACRODEFS_MSVC "2019 16.6"
#   elif _MSC_VER == 1927
#       define __MACRODEFS_MSVC "2019 16.7"
#   elif _MSC_VER == 1928 && _MSC_FULL_VER <= 192829913L
#       define __MACRODEFS_MSVC "2019 16.8"
#   elif _MSC_VER == 1928
#       define __MACRODEFS_MSVC "2019 16.9"
#   elif _MSC_VER == 1929
#       define __MACRODEFS_MSVC "2019 16.10"
#   endif
#   ifdef __MACRODEFS_MSVC
#       define COMPILER_NAME "Microsoft Visual C/C++ " __MACRODEFS_MSVC
#   else
#       define COMPILER_NAME "Microsoft Visual C/C++"
#   endif
#elif defined(__TINYC__)
#   define COMPILER_NAME "Tiny C Compiler"
#elif defined(__LCC__)
#   define COMPILER_NAME "Local C Compiler"
#elif defined(__PGI)
#   define COMPILER_NAME "Portland Group C/C++"
#elif defined(__HP_cc)
#   define COMPILER_NAME "HP ANSI C"
#elif defined(__HP_aCC)
#   define COMPILER_NAME "HP aC++"
#elif defined(__sgi)
#   define COMPILER_NAME "SGI"
#elif defined(__EMSCRIPTEN__)
#   define COMPILER_NAME "Emscripten " \
        STRINGIFY(__EMSCRIPTEN_major__) "." \
        STRINGIFY(__EMSCRIPTEN_minor__) "." \
        STRINGIFY(__EMSCRIPTEN_tiny__)
#elif defined(__clang__)
#   define COMPILER_NAME \
        "Clang " STRINGIFY(__clang_major__) "." STRINGIFY(__clang_minor__) "." \
        STRINGIFY(__clang_patchlevel__)
#elif defined(__GNUC__)
#   if __GNUC_PATCHLEVEL__ > 0
#       define COMPILER_NAME \
            "GCC " STRINGIFY(__GNUC__) "." STRINGIFY(__GNUC_MINOR__) "." \
            STRINGIFY(__GNUC_PATCHLEVEL__)
#   else
#       define COMPILER_NAME \
            "GCC " STRINGIFY(__GNUC__) "." STRINGIFY(__GNUC_MINOR__)
#   endif
#else
#   define COMPILER_NAME "(unknown)"
#endif

#if defined(__asmjs__) || defined(__wasm__)
#   define OS_NAME "JavaScript"
#elif defined(__ANDROID__)
#   include <android/api-level.h>
#   if __ANDROID_API__ == 1
#       define __MACRODEFS_ANDROID "1.0"
#   elif __ANDROID_API__ == 2
#       define __MACRODEFS_ANDROID "1.1"
#   elif __ANDROID_API__ == 3
#       define __MACRODEFS_ANDROID "Cupcake 1.5"
#   elif __ANDROID_API__ == 4
#       define __MACRODEFS_ANDROID "Donut 1.6"
#   elif __ANDROID_API__ == 5
#       define __MACRODEFS_ANDROID "Eclair 2.0"
#   elif __ANDROID_API__ == 6
#       define __MACRODEFS_ANDROID "Eclair 2.0.1"
#   elif __ANDROID_API__ == 7
#       define __MACRODEFS_ANDROID "Eclair 2.1"
#   elif __ANDROID_API__ == 8
#       define __MACRODEFS_ANDROID "Froyo 2.2"
#   elif __ANDROID_API__ == 9
#       define __MACRODEFS_ANDROID "Gingerbread 2.3"
#   elif __ANDROID_API__ == 10
#       define __MACRODEFS_ANDROID "Gingerbread 2.3.3"
#   elif __ANDROID_API__ == 11
#       define __MACRODEFS_ANDROID "Honeycomb 3.0"
#   elif __ANDROID_API__ == 12
#       define __MACRODEFS_ANDROID "Honeycomb 3.1"
#   elif __ANDROID_API__ == 13
#       define __MACRODEFS_ANDROID "Honeycomb 3.2"
#   elif __ANDROID_API__ == 14
#       define __MACRODEFS_ANDROID "Ice Cream Sandwich 4.0"
#   elif __ANDROID_API__ == 15
#       define __MACRODEFS_ANDROID "Ice Cream Sandwich 4.0.3"
#   elif __ANDROID_API__ == 16
#       define __MACRODEFS_ANDROID "Jelly Bean 4.1"
#   elif __ANDROID_API__ == 17
#       define __MACRODEFS_ANDROID "Jelly Bean 4.2"
#   elif __ANDROID_API__ == 18
#       define __MACRODEFS_ANDROID "Jelly Bean 4.3"
#   elif __ANDROID_API__ == 19
#       define __MACRODEFS_ANDROID "Kitkat 4.4"
#   elif __ANDROID_API__ == 20
#       define __MACRODEFS_ANDROID "Kitkat Watch 4.4"
#   elif __ANDROID_API__ == 21
#       define __MACRODEFS_ANDROID "Lollipop 5.0"
#   elif __ANDROID_API__ == 22
#       define __MACRODEFS_ANDROID "Lollipop 5.1"
#   elif __ANDROID_API__ == 23
#       define __MACRODEFS_ANDROID "Marshmallow 6.0"
#   elif __ANDROID_API__ == 24
#       define __MACRODEFS_ANDROID "Nougat 7.0"
#   elif __ANDROID_API__ == 25
#       define __MACRODEFS_ANDROID "Nougat 7.1"
#   elif __ANDROID_API__ == 26
#       define __MACRODEFS_ANDROID "Oreo 8.0"
#   elif __ANDROID_API__ == 27
#       define __MACRODEFS_ANDROID "Oreo 8.1"
#   elif __ANDROID_API__ == 28
#       define __MACRODEFS_ANDROID "Pie 9.0"
#   elif __ANDROID_API__ == 29
#       define __MACRODEFS_ANDROID "Q 10.0"
#   elif __ANDROID_API__ == 30
#       define __MACRODEFS_ANDROID "R 11.0"
#   elif __ANDROID_API__ == 31
#       define __MACRODEFS_ANDROID "S 12.0"
#   endif
#   ifdef __MACRODEFS_ANDROID
#       define OS_NAME "Android " __MACRODEFS_ANDROID
#   else
#       define OS_NAME "Android"
#   endif
#elif defined(__linux__)
#   define OS_NAME "Linux"
#elif defined(__DragonFly__)
#   define OS_NAME "DragonFly BSD"
#elif defined(__FreeBSD__)
#   define OS_NAME "FreeBSD"
#elif defined(__OpenBSD__)
#   define OS_NAME "OpenBSD"
#elif defined(__NetBSD__)
#   define OS_NAME "NetBSD"
#elif defined(__Fuchsia__)
#   define OS_NAME "Fuchsia"
#elif defined(__QNX__) || defined(__QNXNTO__)
#   ifdef __QNXNTO__
#       define OS_NAME "QNX 6+"
#   else
#       define OS_NAME "QNX 4"
#   endif
#elif defined(_AIX) || defined(__AIX__) || defined(__TOS_AIX__)
#   ifndef __AIX__
#       define __AIX__ 1
#   endif
#   define OS_NAME "AIX"
#elif defined(sgi) || defined(__sgi) || defined(__sgi__) || \
    defined(_SGI_SOURCE) || defined(__IRIX__)
#   ifndef __IRIX__
#       define __IRIX__ 1
#   endif
#   define OS_NAME "Irix"
#elif defined(__ros__)
#   define OS_NAME "Akaros"
#elif defined(riscos) || defined(__riscos) || defined(__riscos__) || \
    defined(__RISCOS__)
#   ifndef __riscos__
#       define __riscos__ 1
#   endif
#   define OS_NAME "RiscOS"
#elif defined(__APPLE__)
#   include <TargetConditionals.h>
#   if !defined(TARGET_OS_SIMULATOR) && defined(TARGET_IPHONE_SIMULATOR)
#       define TARGET_OS_SIMULATOR TARGET_IPHONE_SIMULATOR
#   endif
#   if !defined(TARGET_OS_WATCH) && defined(TARGET_OS_NANO)
#       define TARGET_OS_WATCH TARGET_OS_NANO
#   endif
#   if TARGET_OS_MAC
#       ifndef __MACOSX__
#           define __MACOSX__ 1
#       endif
#       define OS_NAME "macOS"
#   elif TARGET_OS_WATCH
#       define OS_NAME "watchOS"
#   elif TARGET_OS_TV
#       ifndef __TVOS__
#           define __TVOS__ 1
#       endif
#       define OS_NAME "tvOS"
#   elif TARGET_OS_IOS || TARGET_OS_IPHONE
#       ifndef __IPHONEOS__
#           define __IPHONEOS__ 1
#       endif
#       define OS_NAME "iOS"
#   elif TARGET_OS_SIMULATOR
#       define OS_NAME "iOS [simulated]"
#   endif
#elif defined(__sun)
#   if defined(__SVR4) || defined(__svr4__) || defined(_SYSTYPE_SVR4) || \
        defined(__SOLARIS__)
#       ifndef __SOLARIS__
#           define __SOLARIS__ 1
#       endif
#       define OS_NAME "Solaris"
#   else
#       define OS_NAME "SunOS"
#   endif
#elif defined(__CYGWIN__)
#   define OS_NAME "Cygwin"
#elif defined(__MSYS__)
#   define OS_NAME "MSYS"
#elif defined(__serenity__)
#   define OS_NAME "Serenity"
#elif defined(__vita__) || defined(__VITA__)
#   ifndef __vita__
#       define __vita__ __VITA__
#   endif
#   define OS_NAME "PSVita"
#elif defined(__PSP__)
#   define OS_NAME "PSP"
#elif defined(__WINRT__)
#   define OS_NAME "WinRT"
#elif defined(_WIN32)
#   ifdef _WIN32_WINNT
#       if _WIN32_WINNT == 0x0400
#           define OS_NAME "Win32 (NT 4.0+)"
#       elif _WIN32_WINNT == 0x0500
#           define OS_NAME "Win32 (2000+)"
#       elif _WIN32_WINNT == 0x0501
#           define OS_NAME "Win32 (XP+)"
#       elif _WIN32_WINNT == 0x0502
#           define OS_NAME "Win32 (Server 2003+)"
#       elif _WIN32_WINNT == 0x0600
#           define OS_NAME "Win32 (Vista+)"
#       elif _WIN32_WINNT == 0x0601
#           define OS_NAME "Win32 (7+)"
#       elif _WIN32_WINNT == 0x0602
#           define OS_NAME "Win32 (8+)"
#       elif _WIN32_WINNT == 0x0603
#           define OS_NAME "Win32 (8.1+)"
#       elif _WIN32_WINNT == 0x0a00
#           define OS_NAME "Win32 (10+)"
#       endif
#   endif
#   ifndef OS_NAME
#       define OS_NAME "Win32"
#   endif
#elif defined(__OS2__)
#   define OS_NAME "OS/2"
#elif defined(__BEOS__)
#   define OS_NAME "BeOS"
#elif defined(__HAIKU__)
#   define OS_NAME "Haiku"
#elif defined(AMIGA) || defined(__amigaos__)
#   ifndef __amigaos__
#       define __amigaos__ 1
#   endif
#   define OS_NAME "AmigaOS"
#elif defined(__SYMBIAN32__)
#   define OS_NAME "Symbian OS"
#elif defined(__unix__)
#   define OS_NAME "Generic Unix"
#else
#   define OS_NAME "Bare Metal"
#endif

#ifdef __asmjs__
#   define ARCH_NAME "asm.js"
#elif defined(__wasm__)
#   define ARCH_NAME "wasm32"
#elif defined(__riscv)
#   define ARCH_NAME "RISC-V" STRINGIFY(__riscv_xlen)
#elif defined(__x86_64__) || defined(_M_X64) || defined(__x86_64) || \
    defined(__amd64__) || defined(__amd64) || defined(_M_AMD64)
#   define ARCH_NAME "x64"
#   ifndef __x86_64__
#       define __x86_64__ 1
#   endif
#   ifndef __amd64__
#       define __amd64__ 1
#   endif
#   ifndef __SSE2__
#       define __SSE2__ 1
#   endif
#   ifndef __SSE__
#       define __SSE__ 1
#   endif
#elif defined(__i386__) || defined(__i386) || defined(_M_IX86) || \
    defined(__THW_INTEL__) || defined(_M_I86) || defined(__386) || \
    defined(_X86_) || defined(__i386) || defined(i386) || defined(__IA32__) || \
    defined(__X86__) || defined(__INTEL__) || defined(__386__)
#   define ARCH_NAME "i386"
#   ifndef __i386__
#       define __i386__ 1
#   endif
#   if defined(_M_IX86_FP) && !defined(__SSE__)
#       define __SSE__ 1
#   endif
#elif defined(_M_ARM64) || defined(__aarch64__)
#   define ARCH_NAME "ARM64"
#   ifndef __aarch64__
#       define __aarch64__ 1
#   endif
#elif defined(_M_ARM) || defined(__arm__) || defined(_ARM) || \
    defined(_M_ARM) || defined(__arm)
#   define ARCH_NAME "ARM32"
#   ifndef __arm__
#       define __arm__ 1
#   endif
#elif defined(__ia64__) || defined(_IA64) || defined(__IA64__) || \
    defined(__ia64) || defined(_M_IA64) || defined(__itanium__)
#   define ARCH_NAME "Itanium"
#   ifndef __ia64__
#       define __ia64__ 1
#   endif
#elif defined(__powerpc64__) || defined(__ppc64__) || defined(__PPC64__) || \
    defined(_ARCH_PPC64)
#   define ARCH_NAME "Power64"
#   ifndef __powerpc64__
#       define __powerpc64__ 1
#   endif
#elif defined(__powerpc) || defined(__powerpc__) || defined(__POWERPC__) || \
    defined(__ppc__) || defined(__PPC__) || defined(_ARCH_PPC) || \
    defined(_M_PPC) || defined(__ppc)
#   define ARCH_NAME "PowerPC"
#   ifndef __powerpc__
#       define __powerpc__ 1
#   endif
#elif defined(__sh__) || defined(__sh1__) || defined(__sh2__) || \
    defined(__sh3__) || defined(__SH3__) || defined(__SH4__) || defined(__SH5__)
#   define ARCH_NAME "SuperH"
#   ifndef __sh__
#       define __sh__ 1
#   endif
#elif defined(__mips) || defined(mips) || defined(_MIPS_ISA) || \
    defined(_R3000) || defined(_R4000) || defined(_R5900) || \
    defined(__MIPS__) || defined(__mips__)
#   define ARCH_NAME "MIPS"
#   ifndef __mips__
#       define __mips__ 1
#   endif
#elif defined(__AVR_ARCH__)
#   if __AVR_ARCH__ == 100
#       define ARCH_NAME "AVRTiny"
#   elif __AVR_ARCH__ == 102
#       define ARCH_NAME "AVRXMega2"
#   elif __AVR_ARCH__ == 103
#       define ARCH_NAME "AVRXMega3"
#   elif __AVR_ARCH__ == 104
#       define ARCH_NAME "AVRXMega4"
#   elif __AVR_ARCH__ == 105
#       define ARCH_NAME "AVRXMega5"
#   elif __AVR_ARCH__ == 106
#       define ARCH_NAME "AVRXMega6"
#   elif __AVR_ARCH__ == 107
#       define ARCH_NAME "AVRXMega7"
#   else
#       define ARCH_NAME "AVR" STRINGIFY(__AVR_ARCH__)
#   endif
#elif defined(__sparc__) || defined(__sparc)
#   define ARCH_NAME "SPARC"
#   ifndef __sparc__
#       define __sparc__ __sparc
#   endif
#   if defined(__sparcv8) && !defined(__sparc_v8__)
#       define __sparc_v8__ __sparcv8
#   endif
#   if defined(__sparcv9) && !defined(__sparc_v9__)
#       define __sparc_v9__ __sparcv9
#   endif
#elif defined(__m68k__) || defined(M68000) || defined(__MC68K__) || \
    defined(__mc68000__) || defined(__MC68000__) || defined(__mc68010__) || \
    defined(__mc68020__) || defined(__MC68020__) || defined(__mc68030__) || \
    defined(__MC68030__) || defined(__mc68040__) || defined(__mc68060__)
#   define ARCH_NAME "M68000"
#   ifndef __m68k__
#       define __m68k__ 1
#   endif
#else
#   define ARCH_NAME "(unknown)"
#endif /* check for ARM thumb instruction support */
#if (defined(__arm__) || defined(__aarch64__)) && \
    (defined(_M_ARMT) || defined(__TARGET_ARCH_THUMB)) && !defined(__thumb__)
#   define __thumb__ 1
#endif

#if defined(__aarch64__) || defined(__x86_64__) || defined(__ia64__) || \
    defined(__powerpc64__) || (defined(__riscv_xlen) && (__riscv_xlen == 64))
#   define WORD_SIZE 64
#else
#   define WORD_SIZE 32
#endif

/* == PREPROCESSOR CHECKERS ================================================= */

/**
 * @def __has_attribute(x)
 * @brief Checks whether a given GNU-style attribute is supported by the
 *        compiler.
 * 
 * @param x The GNU attribute to check for.
 */
/**
 * @def __has_builtin(x)
 * @brief Checks whether a given builtin/intrinsic is supported by the compiler.
 * 
 * @note Is defined as a no-op on compilers that don't support it.
 * 
 * @param x The name of the builtin to check for.
 */
/**
 * @def __has_c_attribute(x)
 * @brief Checks whether a given C2x-style attribute is supported by the
 *        compiler.
 * 
 * @note Is defined as a no-op on compilers that don't support it.
 * 
 * @param x The C attribute to check for.
 */
/**
 * @def __has_cpp_attribute(x)
 * @brief Checks whether a given C++ attribute is supported by the compiler.
 * 
 * @param x The C++ attribute to check for.
 */
/**
 * @def __has_declspec_attribute(x)
 * @brief Checks whether a given MSVC attribute is supported by the compiler.
 * 
 * @param x The __declspec attribute to check for.
 */
/**
 * @def __has_extension(x)
 * @brief Checks whether a given language extension is supported by the
 *        compiler.
 * 
 * @param x The language extension to check for.
 */
/**
 * @def __has_feature(x)
 * @brief Checks whether a given language feature is supported by the compiler.
 * 
 * @param x The language feature to check for.
 */
/**
 * @def __has_include(x)
 * @brief Checks whether a given include file/header is avaliable.
 * 
 * @note Is defined as a no-op on compilers that don't support it.
 * 
 * @param x The name of the include header to check for.
 */
#ifndef __has_attribute
#   ifdef __TINYC__
#       define __macrodefs_attribute_aligned                1
#       define __macrodefs_attribute_cdecl                  1
#       define __macrodefs_attribute_packed                 1
#       define __macrodefs_attribute_regparm                1
#       define __macrodefs_attribute_section                1
#       define __macrodefs_attribute_stdcall                1
#       define __macrodefs_attribute_unused                 1
#       ifdef _WIN32
#           define __macrodefs_attribute_dllexport          1
#       endif
#   elif defined(__CC_ARM)
#       define __macrodefs_attribute_aligned                1
#       define __macrodefs_attribute_always_inline          1
#       define __macrodefs_attribute_deprecated             1
#       define __macrodefs_attribute_noreturn               1
#       define __macrodefs_attribute_weak                   1
#       define __macrodefs_attribute_weakref                1
#   elif defined(__GNUC__) /* GCC didn't get __has_attribute until GCC5 */
#       define __macrodefs_attribute_alias                  1
#       define __macrodefs_attribute_always_inline          1
#       define __macrodefs_attribute_cdecl                  1
#       define __macrodefs_attribute_constructor            1
#       define __macrodefs_attribute_deprecated             1
#       define __macrodefs_attribute_destructor             1
#       define __macrodefs_attribute_dllimport              1
#       define __macrodefs_attribute_dllexport              1
#       define __macrodefs_attribute_mode                   1
#       define __macrodefs_attribute_no_instrument_function 1
#       define __macrodefs_attribute_nocommon               1
#       define __macrodefs_attribute_noinline               1
#       define __macrodefs_attribute_packed                 1
#       define __macrodefs_attribute_regparm                1
#       define __macrodefs_attribute_section                1
#       define __macrodefs_attribute_shared                 1
#       define __macrodefs_attribute_stdcall                1
#       define __macrodefs_attribute_transparent_union      1
#       define __macrodefs_attribute_warn_unused_result     1
#       define __macrodefs_attribute_weak                   1
#       define __macrodefs_attribute_weakref                1
#       if defined(__powerpc__) || defined(__powerpc64__)
#           define __macrodefs_attribute_longcall           1
#       endif
#       if GCC_PREREQ(20000)
#           define __macrodefs_attribute_aligned            1
#           define __macrodefs_attribute_format_arg         1
#           define __macrodefs_attribute_unused             1
#           define __macrodefs_attribute_used               1
#       endif
#       if GCC_PREREQ(20500)
#           define __macrodefs_attribute_const              1
#           define __macrodefs_attribute_noreturn           1
#       endif
#       if GCC_PREREQ(29600)
#           define __macrodefs_attribute_pure               1
#       endif
#       if GCC_PREREQ(30000)
#           define __macrodefs_attribute_format             1
#           define __macrodefs_attribute_may_alias          1
#       endif
#       if GCC_PREREQ(30100)
#           define __macrodefs_attribute_malloc             1
#       endif
#       if GCC_PREREQ(30200)
#           define __macrodefs_attribute_malloc             1
#           define __macrodefs_attribute_vector_size        1
#       endif
#       if GCC_PREREQ(40000)
#           define __macrodefs_attribute_visibility         1
#       endif
#       if GCC_PREREQ(40300)
#           define __macrodefs_attribute_error              1
#       endif
#   else
#       define __attribute__(x)
#   endif
#   define __has_attribute(x) __macrodefs_attribute_ ##x
#endif
#ifndef __has_builtin
#   define __has_builtin(x) 0L
#endif
#ifndef __has_c_attribute /* C18- doesn't have C attributes */
#   define __has_c_attribute(x) 0L
#endif
#ifndef __has_cpp_attribute /* C++17- doesn't have __has_cpp_attribute */
#   if STDC_PREREQ(1L)
#       define __has_cpp_attribute(x) 0L
#   elif CPP_PREREQ(201103L)
#       define __macrodefs_cpp_attribute_carries_dependency             200809L
#       define __macrodefs_cpp_attribute_noreturn                       200809L
#       if CPP_PREREQ(201403L)
#           define __macrodefs_cpp_attribute_deprecated                 201309L
#           if CPP_PREREQ(201703L)
#               define __macrodefs_cpp_attribute_fallthrough            201603L
#               define __macrodefs_cpp_attribute_maybe_unused           201603L
#               define __macrodefs_cpp_attribute_nodiscard              201603L
#               if CPP_PREREQ(202002L)
#                   define __macrodefs_cpp_attribute_likely             201803L
#                   define __macrodefs_cpp_attribute_no_unique_address  201803L
#                   undef  __macrodefs_cpp_attribute_nodiscard
#                   define __macrodefs_cpp_attribute_nodiscard          201907L
#               endif
#           endif
#       endif
#       define __has_cpp_attribute(x) __macrodefs_cpp_attribute ##x
#   endif
#endif
#ifndef __has_declspec_attribute /* only clang has __has_declspec_attribute */
#   if MSVC_PREREQ(1)
#       define __macrodefs_declspec_attribute_alllocate         1
#       define __macrodefs_declspec_attribute_allocator         1
#       define __macrodefs_declspec_attribute_appdomain         1
#       define __macrodefs_declspec_attribute_code_seg          1
#       define __macrodefs_declspec_attribute_dllimport         1
#       define __macrodefs_declspec_attribute_dllexport         1
#       define __macrodefs_declspec_attribute_jitintrinsic      1
#       define __macrodefs_declspec_attribute_naked             1
#       define __macrodefs_declspec_attribute_noalias           1
#       define __macrodefs_declspec_attribute_noreturn          1
#       define __macrodefs_declspec_attribute_nothrow           1
#       define __macrodefs_declspec_attribute_novtable          1
#       define __macrodefs_declspec_attribute_property          1
#       define __macrodefs_declspec_attribute_restrict          1
#       define __macrodefs_declspec_attribute_safebuffers       1
#       define __macrodefs_declspec_attribute_thread            1
#       define __macrodefs_declspec_attribute_uuid              1
#       if MSVC_PREREQ(1100)
#           define __macrodefs_declspec_attribute_selectany     1
#       endif
#       if MSVC_PREREQ(1300)
#           define __macrodefs_declspec_attribute_align         1
#           define __macrodefs_declspec_attribute_noinline      1
#       endif
#       if MSVC_PREREQ(1310)
#           define __macrodefs_declspec_attribute_deprecated    1
#       endif
#       if MSVC_PREREQ(1912)
#           define __macrodefs_declspec_attribute_spectre       1
#       endif
#       ifdef __CLR_VER
#           define __macrodefs_declspec_attribute_attr_process  1
#       endif
#   elif defined(__DMC__)
#       define __macrodefs_declspec_attribute_dllimport         1
#       define __macrodefs_declspec_attribute_dllexport         1
#       define __macrodefs_declspec_attribute_naked             1
#       define __macrodefs_declspec_attribute_thread            1
#   elif defined(__BORLANDC__)
#       define __macrodefs_declspec_attribute_thread            1
#   elif GCC_PREREQ(20000)
#       ifndef __declspec
#           define __declspec(x) __attribute__((x))
#       endif
#       define __macrodefs_declspec_attribute_dllimport         1
#       define __macrodefs_declspec_attribute_dllexport         1
#   else
#       define __declspec(x)
#   endif
#   define __has_declspec_attribute(x) __macrodefs_declspec_attribute_ ##x
#endif
#ifndef __has_extension
#   ifdef __GNUC__
#       if GCC_PREREQ(40500)
#           define __macrodefs_extension_attribute_deprecated_with_message 1
#       endif
#   endif
#   define __has_extension(x) ((__macrodefs_extension_ ##x) || __has_feature(x))
#endif
#ifndef __has_feature
#   define __has_feature(x) 0
#endif
#ifndef __has_include
#   define __has_include(x) 0
#endif

/* == STANDARD MACROS TO DENOTE MISSING FEATURES ============================ */

/**
 * @def __STDC_NO_VLA__
 * @brief A standard macro that declares a C implementation which does not
 *        support variable-length arrays.
 */
/**
 * @def __STDC_NO_THREADS__
 * @brief A standard macro that declares a C implementation which does not
 *        support the standard thread support library via @c <threads.h>.
 */
/**
 * @def __STDC_NO_ATOMICS__
 * @brief A standard macro that declares a C implementation which does not
 *        support standard atomics via the @c _Atomic keyword or
 *        @c <stdatomic.h>.
 */
#if (STDC_PREREQ(1L) && (!STDC_PREREQ(199901L) || defined(SDCC))) && \
    !defined(__STDC_NO_VLA__)
#   define __STDC_NO_VLA__ 1
#endif
#if ((STDC_PREREQ(1L) && !STDC_PREREQ(201112L)) || \
    (defined(__has_include) && !__has_include(<threads.h>))) && \
    !defined(__STDC_NO_THREADS__)
#   define __STDC_NO_THREADS__ 1
#endif
#if ((STDC_PREREQ(1L) && !STDC_PREREQ(201112L)) || \
    (defined(__has_include) && !__has_include(<stdatomic.h>))) && \
    !defined(__STDC_NO_ATOMICS__)
#   define __STDC_NO_ATOMICS__ 1
#endif

/* == DYNAMIC LIBRARY IMPORT/EXPORT ANNOTATIONS ============================= */

/**
 * @def EXPORT
 * @brief Annotates a function to be exported when building a dynamic library.
 */
/**
 * @def IMPORT
 * @brief Annotates a function to be imported from a dynamic library.
 */
/**
 * @def LOCAL
 * @brief Annotates a function to not be exported when building a dynamic
 *        library.
 */
#if defined(_WIN32) || defined(__WINRT__) || defined(__OS2__) || \
    defined(__CYGWIN__) || __has_declspec_attribute(dllexport) || \
    __has_declspec_attribute(dllimport)
#   if defined(_WIN32) || defined(__WINRT__) || defined(__OS2__) || \
        defined(__CYGWIN__) || __has_declspec_attribute(dllexport)
#       define EXPORT __declspec(dllexport)
#   endif
#   if defined(_WIN32) || defined(__WINRT__) || defined(__OS2__) || \
        defined(__CYGWIN__) || __has_declspec_attribute(dllimport)
#       define IMPORT __declspec(dllimport)
#   endif
#   define LOCAL
#elif GCC_PREREQ(40000) || __has_attribute(visibility)
#   define EXPORT __attribute__((__visibility__("default")))
#   define IMPORT
#   define LOCAL  __attribute__((__visibility__("hidden")))
#else
#   define EXPORT
#   define IMPORT
#   define LOCAL
#endif
#ifdef __SYMBIAN32__
#   undef EXPORT
#   define IMPORT
#   undef IMPORT
#   define IMPORT IMPORT_C
#   undef LOCAL
#   define LOCAL
#endif

/* == CALLING CONVENTION SPECIFIERS ========================================= */

#if defined(__i386__)
#   if defined(_MSC_VER) || defined(__DMC__) || defined(__BORLANDC__)
#       define CDECL __cdecl
#       define STDCALL __stdcall
#       define FASTCALL __fastcall
#       ifdef __DMC__ || (defined(__BORLANDC__) && (__BORLANDC__ < 1400))
#           undef FASTCALL
#       endif
#   else
#       if __has_attribute(cdecl)
#           define CDECL __attribute__((cdecl))
#       endif
#       if __has_attribute(stdcall)
#           define STDCALL __attribute__((stdcall))
#       endif
#       if __has_attribute(fastcall)
#           define FASTCALL __attribute__((fastcall))
#       endif
#   endif
#endif

#ifndef CDECL
#   define CDECL
#endif
#ifndef STDCALL
#   define STDCALL
#endif
#ifndef FASTCALL
#   define FASTCALL
#endif

/* == PRAGMA DIRECTIVE ====================================================== */

/**
 *  @def __pragma(dir)
 *  @brief Microsoft-style pragma directive.
 *  @details Due to the existence of __prgma, it's more easily made
 *           cross-platform than C99 _Pragma lul
 *  
 *  @param[in] dir Compiler pragma directive to give.
 */
#if !MSVC_PREREQ(1) && !defined(__INTEL_COMPILER)
#   if (STDC_PREREQ(199901L) || CPP_PREREQ(201103L)) /* C99+/C++11+ _Pragma */
#       define __pragma(dir) _Pragma(#dir)
#   elif !MSVC_PREREQ(1500) /* MSVC 2008+ __pragma */
#       define __pragma(dir)
#   endif
#endif

/* == FUNCTION ATTRIBUTES =================================================== */

/**
 * @def ALLOCATOR(deallocator)
 * @brief Denotes that a function allocates memory.
 * 
 * @param[in] deallocator Function to deallocate 
 */
/**
 * @def DEPRECATED(msg)
 * @brief Denotes that a function has been deprecated.
 * 
 * @param[in] msg A message to display.
 */
/**
 * @def NO_RETURN
 * @brief Denotes that a function does not return to the caller.
 */
/**
 * @def CONST_FUNC
 * @brief Denotes that a function's return value is based solely on the
 *        parameters passed into it. Implies @c PURE_FUNC.
 */
/**
 * @def PURE_FUNC
 * @brief Denotes that a function is pure (i.e. the same output given the
 *        same inputs).
 */
/**
 * @def CHECK_RESULT
 * @brief Denotes that a function's return value must be read after evaluation.
 */
/**
 * @def RETURNS_NOTNULL
 * @brief Denotes that a function's return value doesn't return @c NULL.
 */
/**
 * @def PRINTF_FUNC(fstr_index, arg_index)
 * @brief Denotes a function has printf semantics.
 * 
 * @param[in] fstr_index The argument number of the printf format string.
 * @param[in] arg_index  The argument number where the printf arguments start.
 */
/**
 * @def SCANF_FUNC(fstr_index, arg_index)
 * @brief Denotes that a function has scanf semantics.
 * 
 * @param[in] fstr_index The argument number of the scanf format string.
 * @param[in] arg_index  The argument number where the scanf arguments start.
 */
#if __has_attribute(malloc)
    /* GCC 11+ has extended malloc attribute w/ specified deallocator */
#   if GCC_PREREQ(110000)
#       define ALLOCATOR(deallocator) \
            __attribute__((malloc, malloc(deallocator)))
#   else
#       define ALLOCATOR(deallocator) __attribute__((malloc))
#   endif
#elif MSVC_PREREQ(1) || __has_declspec_attribute(allocator) || \
    __has_declspec_attribute(restrict)
#   if __has_declspec_attribute(allocator) && __has_declspec_attribute(restrict)
#       define ALLOCATOR(deallocator) __declspec(allocator) __declspec(restrict)
#   elif __has_declspec_attribute(allocator)
#       define ALLOCATOR(deallocator) __declspec(allocator)
#   elif __has_declspec_attribute(restrict)
#       define ALLOCATOR(deallocator) __declspec(restrict)
#   else
#       define ALLOCATOR(deallocator)
#   endif
#else
#   define ALLOCATOR(deallocator)
#endif
#if __has_c_attribute(deprecated) || __has_cpp_attribute(deprecated)
#   define DEPRECATED(msg) [[deprecated(msg)]]
#elif GCC_PREREQ(30100) || __has_attribute(depreceated)
#   if __has_extension(attribute_deprecated_with_message)
#       define DEPRECATED(msg) __attribute__((depreceated(msg)))
#   else
#       define DEPRECATED(msg) __attribute__((depreceated))
#   endif
#elif __has_declspec_attribute(deprecated)
#   if MSVC_PREREQ(1400)
#       define DEPRECATED(msg) __declspec(deprecated(msg))
#   else
#       define DEPRECATED(msg) __declspec(deprecated)
#   endif
#else
#   define DEPRECATED(msg)
#endif
#if CPP_PREREQ(201103L) /* C++11+ attribute noreturn */
#   define NO_RETURN [[noreturn]]
#elif STDC_PREREQ(201112L) /* C11+ _Noreturn */
#   define NO_RETURN _Noreturn
#elif __has_attribute(noreturn) /* GCC 2.5+ noreturn */
#   define NO_RETURN __attribute__((noreturn))
#elif __has_declspec_attribute(noreturn) /* MSVC noreturn */
#   define NO_RETURN __declspec(noreturn)
#else
#   define NO_RETURN
#endif
#if __has_attribute(const) /* GCC 2.5+ const */
#   define CONST_FUNC __attribute__((const))
#else
#   define CONST_FUNC
#endif
#if __has_attribute(pure) /* GCC 2.95+ pure */
#   define PURE_FUNC __attribute__((pure))
#else
#   define PURE_FUNC
#endif
#if (__has_c_attribute(nodiscard) && STDC_PREREQ(201800L)) || \
    (__has_cpp_attribute(nodiscard) && CPP_PREREQ(201103L))
#   define CHECK_RESULT [[nodiscard]] /* C2x+ / C++17+ nodiscard */
#elif __has_attribute(warn_unused_result) /* GCC warn_unused_result */
#   define CHECK_RESULT __attribute__((warn_unused_result))
#elif MSVC_PREREQ(1400) || __has_include(<sal.h>) /* MSVC sal.h */
#   include <sal.h>
#   define _USE_SAL 1
#endif
#if GCC_PREREQ(30400) || __has_attribute(returns_nonnull)
#   define RETURNS_NOTNULL __attribute__((returns_nonnull))
#endif
#ifdef _USE_SAL
#   ifndef CHECK_RESULT
#       define CHECK_RESULT _Check_return_
#   endif
#   ifndef RETURNS_NOTNULL
#       define RETURNS_NOTNULL _Ret_notnull_
#   endif
#   undef _USE_SAL
#else
#   ifndef CHECK_RESULT
#       define CHECK_RESULT
#   endif
#   ifndef RETURNS_NOTNULL
#       define RETURNS_NOTNULL
#   endif
#endif
#if __has_attribute(format) /* GCC3 printf/scanf attrs */
#   define PRINTF_FUNC(fstr_index, arg_index) \
        __attribute__((format(printf, fstr_index, arg_index)))
#   define SCANF_FUNC(fstr_index, arg_index) \
        __attribute__((format(scanf, fstr_index, arg_index)))
#else
#   define PRINTF_FUNC(fstr_index, arg_index)
#   define SCANF_FUNC(fstr_index, arg_index)
#endif

/* == INLINE KEYWORDS ======================================================= */

/**
 * @def inline
 * @brief Specifies that a function should be inlined by the compiler.
 */
/**
 * @def force_inline
 * @brief Denotes a function that must be inlined by the compiler.
 */
/**
 * @def static_inline
 * @brief Denotes that a function has static linkage and should be inlined by
 *        the compiler.
 */
/**
 * @def static_force_inline
 * @brief Denotes that a function has static linkage and must be inlined by the
 *        compiler.
 */
/**
 * @def no_inline
 * @brief Prevents a function from being inlined by the compiler.
 */
#if !CPP_PREREQ(1L) && !STDC_PREREQ(199901L) /* C++ & C99+ have inline */
#   if MSVC_PREREQ(1) || defined(__BORLANDC__) || defined(__DMC__) || \
        defined(__WATCOMC__) || defined(__LCC__) || defined(__CC_ARM)
#       define inline __inline /* MSVC __inline */
#   elif GCC_PREREQ(1) /* GCC __inline__ */
#       define inline __inline__ __attribute__((__gnu_inline__))
#   else /* set inline as static if unavailable */
#       define inline static
#       define _NO_INLINE
#   endif
#endif
#if MSVC_PREREQ(1200) /* MSVC __forceinline */
#   define force_inline __forceinline
#elif GCC_PREREQ(40000) || defined(__clang__) /* GCC4+/clang always_inline */
#   ifdef __cplusplus /* with __inline__ in C++... */
#       define force_inline __inline__ __attribute__((__always_inline__))
#   else /* ...whilst adding gnu inline semantics in C */
#       define force_inline \
            __inline__ __attribute__((__always_inline__, __gnu_inline__))
#   endif
#elif __has_attribute(always_inline) /* GCC-esque always_inline */
#   define force_inline inline __attribute__((always_inline))
#else /* hope it gets inlined */
#   define force_inline inline
#endif
#if (MSVC_PREREQ(1) && defined(__EDG__) && !CPP_PREREQ(1L)) || \
    defined(_NO_INLINE) /* MSVC can't do static+inline... */
#   define static_inline        inline
#   define static_force_inline  force_inline
#   ifdef _NO_INLINE /* ...plus resolves to static if no inline available */
#       undef _NO_INLINE
#   endif
#else /* remove underscore on sane compilers */
#   define static_inline        static inline
#   define static_force_inline  static force_inline
#endif
#if __has_attribute(noinline)
#   define no_inline __attribute__((noinline))
#elif __has_declspec_attribute(noinline)
#   define no_inline __declspec(noinline)
#else
#   define no_inline
#endif

/* == PARAMETER ATTRIBUTES ================================================== */

/**
 * @def MAYBE_UNUSED
 * @brief Denotes a potentially unused variable, parameter, or function.
 */
#if (CPP_PREREQ(201703L) && __has_cpp_attribute(maybe_unused)) || \
    (STDC_PREREQ(201800L) && __has_c_attribute(maybe_unused)) 
#   define MAYBE_UNUSED [[maybe_unused]] /* C++17/C2x+ maybe_unused */
#elif __has_attribute(unused) /* GCC unused */
#   define MAYBE_UNUSED __attribute__((unused))
#else
#   define MAYBE_UNUSED
#endif

/* == COMPILER HINTS ======================================================== */

/**
 * @def LIKELY(cond)
 * @brief Denotes a branch which is more likely to be taken than not.
 * 
 * @param[in] cond The condition to check for.
 */
/**
 * @def UNLIKELY(cond)
 * @brief Denotes a branch which is less likely to be taken than not.
 * 
 * @param[in] cond The condition to check for.
 */
/**
 * @def UNREACHABLE()
 * @brief Used to specify that a section cannot be reached.
 */
#if CPP_PREREQ(201704L) || /* C++17+ likely/unlikely */ \
    (__has_cpp_attribute(likely) && __has_cpp_attribute(unlikely))
#   define LIKELY(cond)     (cond) [[likely]]
#   define UNLIKELY(cond)   (cond) [[unlikely]]
#elif GCC_PREREQ(30000) || __has_builtin(__builtin_expect) /* GCC3+ expect */
#   define LIKELY(cond)     (__builtin_expect((cond), 1))
#   define UNLIKELY(cond)   (__builtin_expect((cond), 0))
#else
#   define LIKELY(cond)     (cond)
#   define UNLIKELY(cond)   (cond)
#endif /* GCC4+ builtin unreachable */
#if GCC_PREREQ(4) || __has_builtin(__builtin_unreachable)
#   define UNREACHABLE() do { __builtin_unreachable(); } while (0)
#elif MSVC_PREREQ(1) /* MSVC assume intrinsic */
#   define UNREACHABLE() do { __assume(0); } while (0)
#else
#   define UNREACHABLE()
#endif

/* == RESTRICT KEYWORD ====================================================== */

/**
 * @def restrict
 * @brief Hints that a pointer isn't aliased by another variable.
 */
#if CPP_PREREQ(1L) || !defined(__STDC_VERSION__) || (__STDC_VERSION__ < 199901L)
#   if MSVC_PREREQ(1)
#       define restrict __restrict
#   elif GCC_PREREQ(1)
#       define restrict __restrict__
#   else
#       define restrict
#   endif
#endif

/* == THREAD LOCAL KEYWORD ================================================== */

/**
 * @def thread_local
 * @brief Specifies a variable has thread-local storage.
 */
#if !CPP_PREREQ(201103L)
#   if STDC_PREREQ(201112L) /* C11+ _Thread_local */
#       define thread_local _Thread_local
#   elif GCC_PREREQ(1) || SUN_PREREQ(0x580) /* GCC/Solaris __thread */
#       define thread_local __thread
#   elif MSVC_PREREQ(1) || __has_declspec_attribute(thread) /* MSVC declspec */
#       define thread_local __declspec(thread)
#   else
#       define _NO_THREAD_LOCAL 1
#   endif
#endif

/* == OFFSETOF ============================================================== */

/**
 * @def offsetof(type, field)
 * @brief Macro which retrieves the offset of a given field in a struct or union
 *        type in bytes.
 * 
 * @param[in] type  The type containing @e field.
 * @param[in] field The field to find the relative offset of within @e type.
 */
#if CPP_PREREQ(1L)
#   include <cstddef>
#else
#   include <stddef.h>
#endif
#ifndef offsetof
#   if GCC_PREREQ(4) || __has_builtin(__builtin_offsetof)
#       define offsetof(type, field) __builtin_offsetof(type, field)
#   else
#       define offsetof(type, field) \
            ((uintptr_t)((char*)&((type*)0)->field - (char*)0))
#   endif
#endif

#define CONTAINER_OF(ptr, type, member) ( \
    (type*)((char*)(1 ? (ptr) : &((type*)0)->member) - offsetof(type, member)) \
)

/* == NULL ================================================================== */

#ifndef __MACH__ /* some Windows compilers need this for some fucking reason */
#   ifndef NULL
#       ifdef __cplusplus
#           define NULL 0
#       else
#           define NULL ((void*)0)
#       endif
#   endif
#endif

/* == ALIGNMENT ============================================================= */

/**
 * @def ALIGN_OF(type)
 * @brief Retrieves the alignment of a given type.
 * 
 * @param[in] type The type to retrieve the alignment of.
 */
/**
 * @def ALIGN_TO(size)
 * @brief Denotes that an associated type's alignment must be based on a given 
 *        power of two.
 * 
 * @param[in] size Bytes to align to. Must be a power of 2. 
 */
/**
 * @def ALIGN_TYPE(type)
 * @brief Denotes that an associated type's alignment must be based on a given
 *        type's alignment.
 * 
 * @param[in] type Type to align to.
 */
#if !CPP_PREREQ(201103L)
#   if STDC_PREREQ(201112L) /* C11+ stdalign */
#       include <stdalign.h>
#       define ALIGN_OF(type) _Alignof(type)
#   elif GCC_PREREQ(20000) /* GCC2+ __alignof__ */
#       define ALIGN_OF(type) __alignof__(type)
#   elif MSVC_PREREQ(1) /* MSVC __alignof */
#       define ALIGN_OF(type) __alignof(type)
#   else /* offsetof fallback */
#       define ALIGN_OF(type) offsetof(struct { char _c; type _t; }, _t)
#   endif
#else
#   define ALIGN_OF(type) alignof(type)
#endif
#if CPP_PREREQ(201103L) || __alignas_is_defined /* C11+/C++11+ alignas */
#   define ALIGN_TO(size)   alignas(size)
#   define ALIGN_TYPE(type) alignas(size)
#elif __has_declspec_attribute(align) /* MSVC declspec */
#   define ALIGN_TO(size)   __declspec(align(size))
#   define ALIGN_TYPE(type) __declspec(align(ALIGN_OF(type)))
#elif __has_attribute(aligned) /* GCC2+ aligned */
#   define ALIGN_TO(size)   __attribute__((aligned(size)))
#   define ALIGN_TYPE(type) __attribute__((aligned(ALIGN_OF(type))))
#else
#   define _NO_ALIGNTO
#endif

/* == STATIC ASSERTIONS ===================================================== */

/**
 * @def static_assert(...)
 * @brief Compile-time assertion statement.
 * 
 * @param[in] cond The condition to check for.
 * @param[in] msg  (optional) A message to display on assertion failure.
 */
/**
 * @def static_assert1(cond)
 * @brief Single-expression compile-time assertion statement.
 * 
 * @param[in] cond The condition to check for.
 */
/**
 * @def static_assert2(cond, msg)
 * @brief Double-expression compile-time assertion statement.
 * 
 * @param[in] cond The condition to check for.
 * @param[in] msg  A message to display on assertion failure.
 */
#if STDC_PREREQ(201112L) && !STDC_PREREQ(201800L)
#   define __MACRODEFS_STATIC_ASSERT2 _Static_assert
#elif CPP_PREREQ(201103L) && !CPP_PREREQ(201703L)
#   define __MACRODEFS_STATIC_ASSERT2 static_assert
#elif GCC_PREREQ(40300) && !defined(__STRICT_ANSI__)
#   define __MACRODEFS_STATIC_ASSERT2(cond, msg) ({ \
        extern int __attribute__((__error__(msg))) \
        CONCATENATE(__macrodefs_static_assert, __COUNTER__)(); \
    })
#elif defined(__COUNTER__)
#   define __MACRODEFS_STATIC_ASSERT1(cond) \
        typedef char CONCATENATE(__macrodefs_static_assert_, __COUNTER__) \
        [(cond) ? 1 : -1]
#else
#   define __MACRODEFS_STATIC_ASSERT1(cond) \
        typedef char CONCATENATE(__macrodefs_static_assert_, __LINE__) \
        [(cond) ? 1 : -1]
#endif
#ifndef __MACRODEFS_STATIC_ASSERT1
#   define __MACRODEFS_STATIC_ASSERT1(cond) \
        __MACRODEFS_STATIC_ASSERT2(cond, "Condition failed.")
#elif !defined(__MACRODEFS_STATIC_ASSERT2)
#   define __MACRODEFS_STATIC_ASSERT2(cond, msg) \
        __MACRODEFS_STATIC_ASSERT1(cond)
#endif
#if !(STDC_PREREQ(201800L) || CPP_PREREQ(201703L))
#   ifdef _GNUC_VA_ARGS
        __extension__
#       define static_assert(args...) CONCATENATE( \
            __MACRODEFS_STATIC_ASSERT, VARGCOUNT(args) \
        )(args)
        ;
#   elif defined(_EXT_VA_ARGS)
        __extension__
#       define static_assert(...) CONCATENATE( \
            __MACRODEFS_STATIC_ASSERT, VARGCOUNT(__VA_ARGS__) \
        )(__VA_ARGS__)
        ;
#   elif !defined(_NO_VA_ARGS)
#       define static_assert(...) CONCATENATE( \
            __MACRODEFS_STATIC_ASSERT, VARGCOUNT(__VA_ARGS__) \
        )(__VA_ARGS__)
#   endif
#   define static_assert1(cond)      __MACRODEFS_STATIC_ASSERT1(cond)
#   define static_assert2(cond, msg) __MACRODEFS_STATIC_ASSERT2(cond, msg)
#else
#   if STDC_PREREQ(201800L)
#       define static_assert _Static_assert
#   endif
#   define static_assert1(cond)      static_assert(cond)
#   define static_assert2(cond, msg) static_assert(cond, msg)
#endif

/* == RUNTIME ASSERTIONS ==================================================== */

/**
 * @def assert(cond)
 * @brief Runtime assertion statement.
 * 
 * @param[in] cond The condition to check for.
 */
/**
 * @def ASSERT_NOT_REACHED()
 * @brief Raises a runtime assertion if the statement is reached.
 */
#ifdef _DEBUG /* MSVC /DEBUG options */
#   define DEBUG 1
#endif
#ifdef NDEBUG /* stdc NDEBUG */
#   ifdef DEBUG
#       undef DEBUG
#   endif
#   ifdef _DEBUG
#       undef _DEBUG
#   endif
#endif
#ifdef DEBUG
#   if CPP_PREREQ(1L)
    extern "C" {
#   endif
#       ifdef EXTERN_ASSERT_HANDLER
        extern
#       endif
        NO_RETURN void __assert_handler(
            char const* cond,
            char const* file,
            int line
        );
#   if CPP_PREREQ(1L)
    }
#   endif
#   define assert(cond) do { \
        if UNLIKELY(!(cond)) __assert_handler(#cond, __FILE__, __LINE__); \
    } while (0)
#   define ASSERT_NOT_REACHED() do { assert(0); UNREACHABLE(); } while (0)
#else
#   define assert(cond)
#   define ASSERT_NOT_REACHED() UNREACHABLE()
#endif

/* == FUNCTION NAME IDENTIFIERS ============================================= */

/**
 * @def __func__
 * @brief Identifier containing the function name.
 */
/**
 * @def __PRETTY_FUNCTION__
 * @brief Identifier containing the full function signature in C++ mode.
 *        Identical to @c __func__ in C mode.
 */
#if MSVC_PREREQ(1300) || (GCC_PREREQ(1) && (__GNUC__ < 3))
#   define __func__ __FUNCTION__ /* MSVC 2002+ / GCC2.99- __FUNCTION__ */
#elif !(GCC_PREREQ(3)) && !STDC_PREREQ(199409L) && !CPP_PREREQ(201103L)
#   ifndef __func__
#       define __func__ "???"
#   endif
#endif
#if MSVC_PREREQ(1300) /* MSVC 2002+ __FUNCSIG__ */
#   define __PRETTY_FUNCTION__ __FUNCSIG__
#elif !GCC_PREREQ(1) /* GCC __PRETTY_FUNCTION__ */
#   define __PRETTY_FUNCTION__ __func__
#endif

/* == STANDARD BOOLEAN TYPE ================================================= */

/**
 * @def bool
 * @brief A type which can store only two values: @c true or @c false.
 */
/**
 * @def true
 * @brief Expands to boolean value 1.
 */
/**
 * @def false
 * @brief Expands to boolean value 0.
 */
#if !CPP_PREREQ(1L)
#   if STDC_PREREQ(199901L) || MSVC_PREREQ(1800) || __has_include(<stdbool.h>)
#       include <stdbool.h> /* C99+/MSVC 1800+ */
#   else
        typedef uint8_t __macrodef_bool;
#       define bool  __macrodef_bool
#       define false ((bool)0)
#       define true  ((bool)1)
#   endif
#endif

/* == STANDARD SIZED INTEGER TYPES ========================================== */

/**
 * @typedef int8_t
 * @brief A signed 8-bit integral type.
 */
/**
 * @typedef uint8_t
 * @brief An unsigned 8-bit integral type.
 */
/**
 * @typedef int16_t
 * @brief A signed 16-bit integral type.
 */
/**
 * @typedef uint16_t
 * @brief An unsigned 16-bit integral type.
 */
/**
 * @typedef int32_t
 * @brief A signed 32-bit integral type.
 */
/**
 * @typedef uint32_t
 * @brief An unsigned 32-bit integral type.
 */
/**
 * @typedef int64_t
 * @brief A signed 64-bit integral type.
 */
/**
 * @typedef uint64_t
 * @brief An unsigned 64-bit integral type.
 */
/**
 * @typedef int_fast8_t
 * @brief A fast signed integral type for performing 8-bit operations.
 */
/**
 * @typedef uint_fast8_t
 * @brief A fast unsigned integral type for performing 8-bit operations.
 */
/**
 * @typedef int_fast16_t
 * @brief A fast signed integral type for performing 16-bit operations.
 */
/**
 * @typedef uint_fast16_t
 * @brief A fast unsigned integral type for performing 16-bit operations.
 */
/**
 * @typedef int_fast32_t
 * @brief A fast signed integral type for performing 32-bit operations.
 */
/**
 * @typedef uint_fast32_t
 * @brief A fast unsigned integral type for performing 32-bit operations.
 */
/**
 * @typedef int_fast64_t
 * @brief A fast signed integral type for performing 64-bit operations.
 */
/**
 * @typedef uint_fast64_t
 * @brief A fast unsigned integral type for performing 64-bit operations.
 */
/**
 * @typedef int_least8_t
 * @brief A signed integral type at least 8 bits wide.
 */
/**
 * @typedef uint_least8_t
 * @brief An unsigned integral type at least 8 bits wide.
 */
/**
 * @typedef int_least16_t
 * @brief A signed integral type at least 16 bits wide.
 */
/**
 * @typedef uint_least16_t
 * @brief An unsigned integral type at least 16 bits wide.
 */
/**
 * @typedef int_least32_t
 * @brief A signed integral type at least 32 bits wide.
 */
/**
 * @typedef uint_least32_t
 * @brief An unsigned integral type at least 32 bits wide.
 */
/**
 * @typedef int_least64_t
 * @brief A signed integral type at least 64 bits wide.
 */
/**
 * @typedef uint_least64_t
 * @brief An unsigned integral type at least 64 bits wide.
 */
/**
 * @typedef intptr_t
 * @brief A signed integral type sized to the machine's pointer size.
 */
/**
 * @typedef uintptr_t
 * @brief An unsigned integral type sized to the machine's pointer size.
 */
/**
 * @typedef intmax_t
 * @brief The largest available signed integral type.
 */
/**
 * @typedef uintmax_t
 * @brief The largest available unsigned integral type.
 */
#if CPP_PREREQ(201103L) || (!STDC_PREREQ(1L) && __has_include(<cstdint>))
#   include <cstdint> /* don't import C++ header in C mode */
#   include <cinttypes>
#   define _SIZED_TYPES_INCLUDED 1
#elif STDC_PREREQ(199901L) || defined(__GNUC__) || defined(__SCO__) || \
    defined(__USLC__) || __has_include(<stdint.h>)
#   include <stdint.h> /* do import C99 header where it's supported in C mode */
#   include <inttypes.h>
#   define _SIZED_TYPES_INCLUDED 1
#elif defined(__VMS) || defined(__sgi)
#   include <inttypes.h> /* these systems are wack & define sized ints here */
#   define _SIZED_TYPES_INCLUDED 1
#elif MSVC_PREREQ(1) || defined(__WATCOMC__) || defined(__BORLANDC__)
#   ifdef __cplusplus
    namespace std {
#   endif
#   if MSVC_PREREQ(1300) /* MSVC 2002+ have builtin sized ints */
        typedef   signed __int8    int8_t;
        typedef unsigned __int8   uint8_t;
        typedef   signed __int16  int16_t;
        typedef unsigned __int16 uint16_t;
        typedef   signed __int32  int32_t;
        typedef unsigned __int32 uint32_t;
#   else
        typedef   signed char    int8_t;
        typedef unsigned char   uint8_t;
        typedef   signed short  int16_t;
        typedef unsigned short uint16_t;
        typedef   signed int    int32_t;
        typedef unsigned int   uint32_t;
#   endif
#   define   INT8_C(val) val ##i8
#   define  UINT8_C(val) val ##ui8
#   define  INT16_C(val) val ##i16
#   define UINT16_C(val) val ##ui16
#   define  INT32_C(val) val ##i32
#   define UINT32_C(val) val ##ui32
#   if MSVC_PREREQ(1) || defined(__WATCOM_INT64__) || \
        (defined(__BORLANDC__) && __BORLANDC__ > 0x460) /* MSVC-style __int64 */
        typedef   signed __int64  int64_t;
        typedef unsigned __int64 uint64_t;
#       define  INT64_C(val) val ##i64
#       define UINT64_C(val) val ##ui64
#       define PRId64 "I64d"
#       define PRIi64 "I64i"
#       define PRIo64 "I64o"
#       define PRIu64 "I64u"
#       define PRIx64 "I64x"
#       define PRIX64 "I64X"
#       define SCNd64 "I64d"
#       define SCNi64 "I64i"
#       define SCNo64 "I64o"
#       define SCNu64 "I64u"
#       define SCNx64 "I64x"
#       define SCNX64 "I64X"
#       define _INT64_DEFINED 1
#   endif

#else
#   ifdef __cplusplus
    namespace std {
#   endif
    typedef signed   char    int8_t;
    typedef unsigned char   uint8_t;
    typedef signed   short  int16_t;
    typedef unsigned short uint16_t;
    typedef signed   int    int32_t;
    typedef unsigned int   uint32_t;
#   define   INT8_C(val) val
#   define  UINT8_C(val) val
#   define  INT16_C(val) val
#   define UINT16_C(val) val
#   define  INT32_C(val) val
#   define UINT32_C(val) val ##u
#   ifdef __LP64__
        typedef   signed long  int64_t;
        typedef unsigned long uint64_t;
#       define  INT64_C(val) val ##l
#       define UINT64_C(val) val ##ul
#       define PRId64 "ld"
#       define PRIi64 "li"
#       define PRIo64 "lo"
#       define PRIu64 "lu"
#       define PRIx64 "lx"
#       define PRIX64 "lX"
#       define SCNd64 "ld"
#       define SCNi64 "li"
#       define SCNo64 "lo"
#       define SCNu64 "lu"
#       define SCNx64 "lx"
#       define SCNX64 "lX"
#       define _INT64_DEFINED 1
#   elif defined(__MWERKS__) || defined(__SUNPRO_C) || defined(__SUNPRO_CC) || \
        defined(_LONG_LONG) /* C99-style long long */
        typedef   signed long long  int64_t;
        typedef unsigned long long uint64_t;
#       define  INT64_C(val) val ##ll
#       define UINT64_C(val) val ##ull
#       define PRId64 "lld"
#       define PRIi64 "lli"
#       define PRIo64 "llo"
#       define PRIu64 "llu"
#       define PRIx64 "llx"
#       define PRIX64 "llX"
#       define SCNd64 "lld"
#       define SCNi64 "lli"
#       define SCNo64 "llo"
#       define SCNu64 "llu"
#       define SCNx64 "llx"
#       define SCNX64 "llX"
#       define _INT64_DEFINED 1
#   endif
#endif
#ifdef _SIZED_TYPES_INCLUDED
#   undef _SIZED_TYPES_INCLUDED
#   if defined(UINT64_C) || defined(UINT64_MAX) || MSVC_PREREQ(1) || \
        STDC_PREREQ(199901L) /* detect 64-bit int support */
#       define _INT64_DEFINED 1
#   endif
#else /* fast_t, least_t, ptr_t, max_t, C, MIN, MAX, PRI, and SCN defines */
#   define PRId8 "d"
#   define PRIi8 "i"
#   define PRIo8 "o"
#   define PRIu8 "u"
#   define PRIx8 "x"
#   define PRIX8 "X"
#   define SCNd8 "d"
#   define SCNi8 "i"
#   define SCNo8 "o"
#   define SCNu8 "u"
#   define SCNx8 "x"
#   define SCNX8 "X"
#   define PRId16 "d"
#   define PRIi16 "i"
#   define PRIo16 "o"
#   define PRIu16 "u"
#   define PRIx16 "x"
#   define PRIX16 "X"
#   define SCNd16 "hd"
#   define SCNi16 "hi"
#   define SCNo16 "ho"
#   define SCNu16 "hu"
#   define SCNx16 "hx"
#   define SCNX16 "hX"
#   define PRId32 "d"
#   define PRIi32 "i"
#   define PRIo32 "o"
#   define PRIu32 "u"
#   define PRIx32 "x"
#   define PRIX32 "X"
#   define SCNd32 "d"
#   define SCNi32 "i"
#   define SCNo32 "o"
#   define SCNu32 "u"
#   define SCNx32 "x"
#   define SCNX32 "X"
#   if defined(__arm__) || defined(__aarch64__) || defined(__powerpc__) || \
        defined(__powerpc64__)
        typedef  int32_t   int_fast8_t;
        typedef uint32_t  uint_fast8_t;
        typedef  int32_t  int_fast16_t;
        typedef uint32_t uint_fast16_t;
        typedef  int32_t  int_fast32_t;
        typedef uint32_t uint_fast32_t;
#       define PRIdFAST8 PRId32
#       define PRIiFAST8 PRIi32
#       define PRIoFAST8 PRIo32
#       define PRIuFAST8 PRIu32
#       define PRIxFAST8 PRIx32
#       define PRIXFAST8 PRIX32
#       define SCNdFAST8 SCNd32
#       define SCNiFAST8 SCNi32
#       define SCNoFAST8 SCNo32
#       define SCNuFAST8 SCNu32
#       define SCNxFAST8 SCNx32
#       define SCNXFAST8 SCNX32
#       define PRIdFAST16 PRId32
#       define PRIiFAST16 PRIi32
#       define PRIoFAST16 PRIo32
#       define PRIuFAST16 PRIu32
#       define PRIxFAST16 PRIx32
#       define PRIXFAST16 PRIX32
#       define SCNdFAST16 SCNd32
#       define SCNiFAST16 SCNi32
#       define SCNoFAST16 SCNo32
#       define SCNuFAST16 SCNu32
#       define SCNxFAST16 SCNx32
#       define SCNXFAST16 SCNX32
#       define PRIdFAST32 PRId32
#       define PRIiFAST32 PRIi32
#       define PRIoFAST32 PRIo32
#       define PRIuFAST32 PRIu32
#       define PRIxFAST32 PRIx32
#       define PRIXFAST32 PRIX32
#       define SCNdFAST32 SCNd32
#       define SCNiFAST32 SCNi32
#       define SCNoFAST32 SCNo32
#       define SCNuFAST32 SCNu32
#       define SCNxFAST32 SCNx32
#       define SCNXFAST32 SCNX32
#   else
        typedef   int8_t   int_fast8_t;
        typedef  uint8_t  uint_fast8_t;
        typedef  int16_t  int_fast16_t;
        typedef uint16_t uint_fast16_t;
        typedef  int32_t  int_fast32_t;
        typedef uint32_t uint_fast32_t;
#       define PRIdFAST8 PRId8
#       define PRIiFAST8 PRIi8
#       define PRIoFAST8 PRIo8
#       define PRIuFAST8 PRIu8
#       define PRIxFAST8 PRIx8
#       define PRIXFAST8 PRIX8
#       define SCNdFAST8 SCNd8
#       define SCNiFAST8 SCNi8
#       define SCNoFAST8 SCNo8
#       define SCNuFAST8 SCNu8
#       define SCNxFAST8 SCNx8
#       define SCNXFAST8 SCNX8
#       define PRIdFAST16 PRId16
#       define PRIiFAST16 PRIi16
#       define PRIoFAST16 PRIo16
#       define PRIuFAST16 PRIu16
#       define PRIxFAST16 PRIx16
#       define PRIXFAST16 PRIX16
#       define SCNdFAST16 SCNd16
#       define SCNiFAST16 SCNi16
#       define SCNoFAST16 SCNo16
#       define SCNuFAST16 SCNu16
#       define SCNxFAST16 SCNx16
#       define SCNXFAST16 SCNX16
#       define PRIdFAST32 PRId32
#       define PRIiFAST32 PRIi32
#       define PRIoFAST32 PRIo32
#       define PRIuFAST32 PRIu32
#       define PRIxFAST32 PRIx32
#       define PRIXFAST32 PRIX32
#       define SCNdFAST32 SCNd32
#       define SCNiFAST32 SCNi32
#       define SCNoFAST32 SCNo32
#       define SCNuFAST32 SCNu32
#       define SCNxFAST32 SCNx32
#       define SCNXFAST32 SCNX32
#   endif
    typedef   int_fast8_t   int_least8_t;
    typedef  uint_fast8_t  uint_least8_t;
    typedef  int_fast16_t  int_least16_t;
    typedef uint_fast16_t uint_least16_t;
    typedef  int_fast32_t  int_least32_t;
    typedef uint_fast32_t uint_least32_t;
#   define PRIdLEAST8 PRIdFAST32
#   define PRIiLEAST8 PRIiFAST32
#   define PRIoLEAST8 PRIoFAST32
#   define PRIuLEAST8 PRIuFAST32
#   define PRIxLEAST8 PRIxFAST32
#   define PRIXLEAST8 PRIXFAST32
#   define SCNdLEAST8 SCNdFAST32
#   define SCNiLEAST8 SCNiFAST32
#   define SCNoLEAST8 SCNoFAST32
#   define SCNuLEAST8 SCNuFAST32
#   define SCNxLEAST8 SCNxFAST32
#   define SCNXLEAST8 SCNXFAST32
#   define PRIdLEAST16 PRIdFAST32
#   define PRIiLEAST16 PRIiFAST32
#   define PRIoLEAST16 PRIoFAST32
#   define PRIuLEAST16 PRIuFAST32
#   define PRIxLEAST16 PRIxFAST32
#   define PRIXLEAST16 PRIXFAST32
#   define SCNdLEAST16 SCNdFAST32
#   define SCNiLEAST16 SCNiFAST32
#   define SCNoLEAST16 SCNoFAST32
#   define SCNuLEAST16 SCNuFAST32
#   define SCNxLEAST16 SCNxFAST32
#   define SCNXLEAST16 SCNXFAST32
#   define PRIdLEAST32 PRIdFAST32
#   define PRIiLEAST32 PRIiFAST32
#   define PRIoLEAST32 PRIoFAST32
#   define PRIuLEAST32 PRIuFAST32
#   define PRIxLEAST32 PRIxFAST32
#   define PRIXLEAST32 PRIXFAST32
#   define SCNdLEAST32 SCNdFAST32
#   define SCNiLEAST32 SCNiFAST32
#   define SCNoLEAST32 SCNoFAST32
#   define SCNuLEAST32 SCNuFAST32
#   define SCNxLEAST32 SCNxFAST32
#   define SCNXLEAST32 SCNXFAST32
#   define   INT8_MIN   INT8_C(-128)
#   define   INT8_MAX   INT8_C(127)
#   define  UINT8_MIN  UINT8_C(0)
#   define  UINT8_MAX  UINT8_C(255)
#   define  INT16_MIN  INT16_C(-32768)
#   define  INT16_MAX  INT16_C(32767)
#   define UINT16_MIN UINT16_C(0)
#   define UINT16_MAX UINT16_C(65535)
#   define  INT32_MIN  INT32_C(-2147483648)
#   define  INT32_MAX  INT32_C(2147483647)
#   define UINT32_MIN UINT32_C(0)
#   define UINT32_MAX UINT32_C(4294967295)
#   if defined(_INT64_DEFINED)
        typedef  int64_t        intmax_t;
        typedef  int64_t    int_fast64_t;
        typedef  int64_t   int_least64_t;
        typedef uint64_t       uintmax_t;
        typedef uint64_t   uint_fast64_t;
        typedef uint64_t  uint_least64_t;
#       define  INT64_MIN   INT64_C(-9223372036854775808)
#       define  INT64_MAX   INT64_C(9223372036854775807)
#       define UINT64_MIN  UINT64_C(0)
#       define UINT64_MAX  UINT64_C(18446744073709551615)
#       define  INTMAX_C    INT64_C
#       define  INTMAX_MIN  INT64_MIN
#       define  INTMAX_MAX  INT64_MAX
#       define UINTMAX_C   UINT64_C
#       define UINTMAX_MIN UINT64_MIN
#       define UINTMAX_MAX UINT64_MAX
#       define PRIdMAX PRId64
#       define PRIiMAX PRIi64
#       define PRIoMAX PRIo64
#       define PRIuMAX PRIu64
#       define PRIxMAX PRIx64
#       define PRIXMAX PRIX64
#       define SCNdMAX SCNd64
#       define SCNiMAX SCNi64
#       define SCNoMAX SCNo64
#       define SCNuMAX SCNu64
#       define SCNxMAX SCNx64
#       define SCNXMAX SCNX64
#       define PRIdFAST64 PRId64
#       define PRIiFAST64 PRIi64
#       define PRIoFAST64 PRIo64
#       define PRIuFAST64 PRIu64
#       define PRIxFAST64 PRIx64
#       define PRIXFAST64 PRIX64
#       define SCNdFAST64 SCNd64
#       define SCNiFAST64 SCNi64
#       define SCNoFAST64 SCNo64
#       define SCNuFAST64 SCNu64
#       define SCNxFAST64 SCNx64
#       define SCNXFAST64 SCNX64
#       define PRIdLEAST64 PRId64
#       define PRIiLEAST64 PRIi64
#       define PRIoLEAST64 PRIo64
#       define PRIuLEAST64 PRIu64
#       define PRIxLEAST64 PRIx64
#       define PRIXLEAST64 PRIX64
#       define SCNdLEAST64 SCNd64
#       define SCNiLEAST64 SCNi64
#       define SCNoLEAST64 SCNo64
#       define SCNuLEAST64 SCNu64
#       define SCNxLEAST64 SCNx64
#       define SCNXLEAST64 SCNX64
#   else
        typedef  int32_t  intmax_t;
        typedef uint32_t uintmax_t;
#       define  INTMAX_C    INT32_C
#       define  INTMAX_MIN  INT32_MIN
#       define  INTMAX_MAX  INT32_MAX
#       define UINTMAX_C   UINT32_C
#       define UINTMAX_MIN UINT32_MIN
#       define UINTMAX_MAX UINT32_MAX
#       define PRIdMAX PRId32
#       define PRIiMAX PRIi32
#       define PRIoMAX PRIo32
#       define PRIuMAX PRIu32
#       define PRIxMAX PRIx32
#       define PRIXMAX PRIX32
#       define SCNdMAX SCNd32
#       define SCNiMAX SCNi32
#       define SCNoMAX SCNo32
#       define SCNuMAX SCNu32
#       define SCNxMAX SCNx32
#       define SCNXMAX SCNX32
#   endif
#   if (defined(_WIN64) || defined(__aarch64__) || defined(__powerpc64__) || \
        defined(__x86_64__) || defined(__ia64__)) && defined(_INT64_DEFINED)
        typedef  int64_t  intptr_t;
        typedef uint64_t uintptr_t;
#       define  INTPTR_MIN  INT64_MIN
#       define  INTPTR_MAX  INT64_MAX
#       define UINTPTR_MIN UINT64_MIN
#       define UINTPTR_MAX UINT64_MAX
#       define PRIdPTR PRId64
#       define PRIiPTR PRIi64
#       define PRIoPTR PRIo64
#       define PRIuPTR PRIu64
#       define PRIxPTR PRIx64
#       define PRIXPTR PRIX64
#       define SCNdPTR SCNd64
#       define SCNiPTR SCNi64
#       define SCNoPTR SCNo64
#       define SCNuPTR SCNu64
#       define SCNxPTR SCNx64
#       define SCNXPTR SCNX64
#   else
        /* __w64 informs that the pointer size changes on 64-bit machines */
#       if !MSVC_PREREQ(1300)
#           define __w64
#       endif
        typedef  int32_t __w64  intptr_t;
        typedef uint32_t __w64 uintptr_t;
#       define  INTPTR_MIN  INT32_MIN
#       define  INTPTR_MAX  INT32_MAX
#       define UINTPTR_MIN UINT32_MIN
#       define UINTPTR_MAX UINT32_MAX
#       define PRIdPTR PRId32
#       define PRIiPTR PRIi32
#       define PRIoPTR PRIo32
#       define PRIuPTR PRIu32
#       define PRIxPTR PRIx32
#       define PRIXPTR PRIX32
#       define SCNdPTR SCNd32
#       define SCNiPTR SCNi32
#       define SCNoPTR SCNo32
#       define SCNuPTR SCNu32
#       define SCNxPTR SCNx32
#       define SCNXPTR SCNX32
#   endif
#   ifdef __cplusplus
    }
#   endif
#endif

#ifndef SIZE_MAX
#   define SIZE_MAX ((size_t)-1)
#endif

/* == MINMAX MACROS ========================================================= */

/**
 * @def MIN(x, y)
 * @brief Retrieves the minimum of two values.
 * 
 * @param[in] x Left hand of the comparison.
 * @param[in] y Right hand of the comparison.
 * 
 * @warning In older/non-extended C implementations, this macro can't account
 *          for side-effects.
 */
/**
 * @def MAX(x, y)
 * @brief Retrieves the maximum of two values.
 * 
 * @param[in] x Left hand of the comparison.
 * @param[in] y Right hand of the comparison.
 * 
 * @warning In older/non-extended C implementations, this macro can't account
 *          for side-effects.
 */
#if CPP_PREREQ(1L) /* C++ minmax */
#   if !CPP_PREREQ(201103L) /* no constexpr in C++03- */
#       define constexpr
#   endif
        template <typename T>
        constexpr static_force_inline T const& __macrodefs_min(
            T const& a,
            T const& b
        ) {
            return (a < b) ? a : b;
        }

        template <typename T>
        constexpr static_force_inline T const& __macrodefs_max(
            T const& a,
            T const& b
        ) {
            return (a > b) ? a : b;
        }
#   if !CPP_PREREQ(201103L)
#       undef constexpr
#   endif
#   define MIN(a, b) __macrodefs_min(a, b)
#   define MAX(a, b) __macrodefs_max(a, b)
#elif GCC_PREREQ(1) /* GNU C minmax */
#   define MIN(a, b) __extension__ ({ \
        __typeof__(a + b) _a = (__typeof__(a + b))(a); \
        __typeof__(a + b) _b = (__typeof__(a + b))(b); \
        (_a < _b) ? _a : _b; \
    })
#   define MAX(a, b) __extension__ ({ \
        __typeof__(a + b) _a = (__typeof__(a + b))(a); \
        __typeof__(a + b) _b = (__typeof__(a + b))(b); \
        (_a > _b) ? _a : _b; \
    })
#elif STDC_PREREQ(201112L) /* C11+ minmax */
#   define __ENUMERATE_MINMAX_FUNCTIONS(macro) \
        macro(signed char,                b) \
        macro(unsigned char,             ub) \
        macro(char,                       c) \
        macro(signed short,               s) \
        macro(unsigned short,            us) \
        macro(signed int,                 i) \
        macro(unsigned int,              ui) \
        macro(signed long int,            l) \
        macro(unsigned long int,         ul) \
        macro(signed long long int,      ll) \
        macro(unsigned long long int,   ull) \
        macro(float,                      f) \
        macro(double,                     d) \
        macro(long double,               ld)
#   define __GENERATE_MINMAX_FUNCTIONS(type, suffix) \
        static_force_inline type __macrodefs_min_ ##suffix(type a, type b) { \
            return (a < b) ? a : b; \
        } \
        static_force_inline type __macrodefs_max_ ##suffix(type a, type b) { \
            return (a > b) ? a : b; \
        }
    __ENUMERATE_MINMAX_FUNCTIONS(__GENERATE_MINMAX_FUNCTIONS)
    __GENERATE_MINMAX_FUNCTIONS(void*, p)
#   undef __GENERATE_MINMAX_FUNCTIONS
#   define __GENERATE_GENERICSEL_LABEL_MIN(type, suffix) \
        type: __macrodefs_min_ ##suffix,
#   define __GENERATE_GENERICSEL_LABEL_MAX(type, suffix) \
        type: __macrodefs_max_ ##suffix,
#   define MIN(a, b) (_Generic((a), \
        __ENUMERATE_MINMAX_FUNCTIONS(__GENERATE_GENERICSEL_LABEL_MIN) \
        default: __macrodefs_min_p \
    )((a), (b)))
#   define MAX(a, b) (_Generic((a), \
        __ENUMERATE_MINMAX_FUNCTIONS(__GENERATE_GENERICSEL_LABEL_MAX) \
        default: __macrodefs_max_p \
    )((a), (b)))
#else /* legacy/janky minmax */
#   define MIN(a, b) (((a) < (b)) ? (a) : (b))
#   define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

/* == STATIC ARRAY LENGTH =================================================== */

/**
 * @def ARRAY_LENGTH(arr)
 * @brief Retrieves the length of a statically allocated array.
 * 
 * @param[in] arr Static array to retrieve the length of.
 */
#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof*(arr))

/* == BYTE ORDER SWAP OPERATIONS ============================================ */

/**
 * @def BSWAP16(x)
 * @brief Swaps the byte order of a 16-bit integral value.
 * 
 * @param[in] x A 16-bit number.
 * 
 * @returns The byte-reversed version of @e x.
 */
/**
 * @def BSWAP32(x)
 * @brief Swaps the byte order of a 32-bit integral value.
 * 
 * @param[in] x A 32-bit number.
 * 
 * @returns The byte-reversed version of @e x.
 */
/**
 * @def BSWAP64(x)
 * @brief Swaps the byte order of a 64-bit integral value.
 * 
 * @param[in] x A 64-bit number.
 * 
 * @returns The byte-reversed version of @e x.
 */
#if GCC_PREREQ(40300) || (__has_builtin(__builtin_bswap16) && \
    __has_builtin(__builtin_bswap32)) /* GCC4.3+ bswap builtins */
#   define BSWAP16(x) __builtin_bswap16(x)
#   define BSWAP32(x) __builtin_bswap32(x)
#   if GCC_PREREQ(40300) || __has_builtin(__builtin_bswap64)
#       define BSWAP64(x) __builtin_bswap64(x)
#   endif
#elif defined(_MSC_VER) /* MSVC byteswap funcdefs */
#   include <stdlib.h>
#   define BSWAP16(x) _byteswap_ushort(x)
#   define BSWAP32(x) _byteswap_ulong(x)
#   define BSWAP64(x) _byteswap_uint64(x)
#elif defined(__linux__) /* linux bswap utilities */
#   include <byteswap.h>
#   define BSWAP16(x) bswap_16(x)
#   define BSWAP32(x) bswap_32(x)
#   define BSWAP64(x) bswap_64(x)
#elif defined(__APPLE__) /* macOS libkern */
#   include <libkern/OSByteOrder.h>
#   define BSWAP16(x) OSSwapInt16(x)
#   define BSWAP32(x) OSSwapInt32(x)
#   define BSWAP64(x) OSSwapInt64(x)
#else /* manual fallback */
    static_force_inline uint16_t __macrodefs_bswap16(uint16_t x) {
        return ((x & 0xff) << 8) | ((x >> 8) & 0xff);
    }
    static_force_inline uint32_t __macrodefs_bswap32(uint32_t x) {
        return
            ((x & 0x000000ffU) << 24) |
            ((x & 0x0000ff00U) << 8)  |
            ((x & 0x00ff0000U) >> 8)  |
            ((x & 0xff000000U) >> 24)
        ;
    }
#   ifdef _INT64_DEFINED
        static_force_inline uint64_t __macrodefs_bswap64(uint64_t x) {
            return
                ((x & UINT64_C(0x00000000000000ff)) << 56) |
                ((x & UINT64_C(0x000000000000ff00)) << 40) |
                ((x & UINT64_C(0x0000000000ff0000)) << 24) |
                ((x & UINT64_C(0x00000000ff000000)) << 8)  |
                ((x & UINT64_C(0x000000ff00000000)) >> 8)  |
                ((x & UINT64_C(0x0000ff0000000000)) >> 24) |
                ((x & UINT64_C(0x00ff000000000000)) >> 40) |
                ((x & UINT64_C(0xff00000000000000)) >> 56)
            ;
        }
#   endif
#   define BSWAP16(x) __macrodefs_bswap16(x)
#   define BSWAP32(x) __macrodefs_bswap32(x)
#   define BSWAP64(x) __macrodefs_bswap64(x)
#endif
#ifndef _INT64_DEFINED
#   undef BSWAP64
#endif

/* == BYTE ORDER MACROS AND HOST-TO-ENDIAN-AND-BACK OPERATIONS ============== */

/**
 * @def htobe16(x)
 * @brief Converts from the machine's byte order to big-endian byte order.
 * 
 * @param[in] x A 16-bit number in the local byte order.
 * 
 * @returns @e x in big-endian byte order.
 */
/**
 * @def htole16(x)
 * @brief Converts from the machine's byte order to little-endian byte order.
 * 
 * @param[in] x A 16-bit number in the local byte order.
 * 
 * @returns @e x in little-endian byte order.
 */
/**
 * @def htobe32(x)
 * @brief Converts from the machine's byte order to big-endian byte order.
 * 
 * @param[in] x A 32-bit number in the local byte order.
 * 
 * @returns @e x in big-endian byte order.
 */
/**
 * @def htole32(x)
 * @brief Converts from the machine's byte order to little-endian byte order.
 * 
 * @param[in] x A 32-bit number in the local byte order.
 * 
 * @returns @e x in little-endian byte order.
 */
/**
 * @def htobe64(x)
 * @brief Converts from the machine's byte order to big-endian byte order.
 * 
 * @param[in] x A 16-bit number in the local byte order.
 * 
 * @returns @e x in big-endian byte order.
 */
/**
 * @def htole64(x)
 * @brief Converts from the machine's byte order to little-endian byte order.
 * 
 * @param[in] x A 64-bit number in the local byte order.
 * 
 * @returns @e x in little-endian byte order.
 */
/**
 * @def be16toh(x)
 * @brief Converts from big-endian byte order to the machine's byte order.
 * 
 * @param[in] x A 16-bit number in big-endian byte order.
 * 
 * @returns @e x in the local byte order.
 */
/**
 * @def le16toh(x)
 * @brief Converts from little-endian byte order to the machine's byte order.
 * 
 * @param[in] x A 16-bit number in little-endian byte order.
 * 
 * @returns @e x in the local byte order.
 */
/**
 * @def be32toh(x)
 * @brief Converts from big-endian byte order to the machine's byte order.
 * 
 * @param[in] x A 32-bit number in big-endian byte order.
 * 
 * @returns @e x in the local byte order.
 */
/**
 * @def le32toh(x)
 * @brief Converts from little-endian byte order to the machine's byte order.
 * 
 * @param[in] x A 32-bit number in little-endian byte order.
 * 
 * @returns @e x in the local byte order.
 */
/**
 * @def be64toh(x)
 * @brief Converts from big-endian byte order to the machine's byte order.
 * 
 * @param[in] x A 64-bit number in big-endian byte order.
 * 
 * @returns @e x in the local byte order.
 */
/**
 * @def le64toh(x)
 * @brief Converts from little-endian byte order to the machine's byte order.
 * 
 * @param[in] x A 64-bit number in little-endian byte order.
 * 
 * @returns @e x in the local byte order.
 */
/**
 * @def BIG_ENDIAN
 * @brief Constant denoting a byte order where the most significant byte is the
 *        largest part of a given number.
 */
/**
 * @def LITTLE_ENDIAN
 * @brief Constant denoting a byte order where the most significant byte is the
 *        smallest part of a given number.
 */
/**
 * @def PDP_ENDIAN
 * @brief Constant denoting a byte order where the most significant word is the
 *        largest part of a given number.
 */
/**
 * @def BYTE_ORDER
 * @brief The byte order of the execution environment.
 */
#if defined(__linux__) || defined(__CYGWIN__) /* linux/cygwin endian utils */
#   include <endian.h>
#elif defined(__APPLE__) /* macOS endian utils */
#   include <machine/endian.h>
#   define htobe16(x) OSSwapHostToBigInt16(x)
#   define htole16(x) OSSwapHostToLittleInt16(x)
#   define be16toh(x) OSSwapBigToHostInt16(x)
#   define le16toh(x) OSSwapLittleToHostInt16(x)
#   define htobe32(x) OSSwapHostToBigInt32(x)
#   define htole32(x) OSSwapHostToLittleInt32(x)
#   define be32toh(x) OSSwapBigToHostInt32(x)
#   define le32toh(x) OSSwapLittleToHostInt32(x)
#   define htobe64(x) OSSwapHostToBigInt64(x)
#   define htole64(x) OSSwapHostToLittleInt64(x)
#   define be64toh(x) OSSwapBigToHostInt64(x)
#   define le64toh(x) OSSwapLittleToHostInt64(x)
#elif defined(__OpenBSD__) || defined(__NetBSD__) || defined(__FreeBSD__) || \
    defined(__DragonFly__) /* BSD endian utils, but it has wack defines */
#   include <sys/endian.h>
#   ifndef __OpenBSD__
#       define be16toh(x) betoh16(x)
#       define le16toh(x) letoh16(x)
#       define be32toh(x) betoh32(x)
#       define le32toh(x) letoh32(x)
#       define be64toh(x) betoh64(x)
#       define le64toh(x) letoh64(x)
#   endif
#else /* manually guess which endianness we are */
#   ifdef __ORDER_BIG_ENDIAN__
#       define BIG_ENDIAN       __ORDER_BIG_ENDIAN__
#   else
#       define BIG_ENDIAN       4321
#   endif
#   ifdef __ORDER_LITTLE_ENDIAN__
#       define LITTLE_ENDIAN   __ORDER_LITTLE_ENDIAN__
#   else
#       define LITTLE_ENDIAN    1234
#   endif
#   ifdef __ORDER_PDP_ENDIAN__
#       define PDP_ENDIAN       __ORDER_PDP_ENDIAN__
#   else
#       define PDP_ENDIAN       3412
#   endif
#   ifndef BYTE_ORDER
#       ifdef __BYTE_ORDER__ /* if on GCC, use compiler-defined byte-order */
#           define BYTE_ORDER   __BYTE_ORDER__
#       elif defined(__x86_64__) || defined(__i386__) || \
            defined(__aarch64__) || defined(__arm__) /* otherwise guess */
#           define BYTE_ORDER   LITTLE_ENDIAN
#       else
#           define BYTE_ORDER   BIG_ENDIAN
#       endif
#   endif
#   if BYTE_ORDER == BIG_ENDIAN
#       define htobe16(x) (x)
#       define htole16(x) BSWAP16(x)
#       define be16toh(x) (x)
#       define le16toh(x) BSWAP16(x)
#       define htobe32(x) (x)
#       define htole32(x) BSWAP32(x)
#       define be32toh(x) (x)
#       define le32toh(x) BSWAP32(x)
#       define htobe64(x) (x)
#       define htole64(x) BSWAP64(x)
#       define be64toh(x) (x)
#       define le64toh(x) BSWAP64(x)
#   elif BYTE_ORDER == LITTLE_ENDIAN
#       define htobe16(x) BSWAP16(x)
#       define htole16(x) (x)
#       define be16toh(x) BSWAP16(x)
#       define le16toh(x) (x)
#       define htobe32(x) BSWAP32(x)
#       define htole32(x) (x)
#       define be32toh(x) BSWAP32(x)
#       define le32toh(x) (x)
#       define htobe64(x) BSWAP64(x)
#       define htole64(x) (x)
#       define be64toh(x) BSWAP64(x)
#       define le64toh(x) (x)
#   else
#       error "Endianness not supported." /* ripperoni pepperoni */
#   endif
#endif
#if defined(__BYTE_ORDER) && !defined(BYTE_ORDER)
#   define BYTE_ORDER __BYTE_ORDER
#endif
#if defined(__BIG_ENDIAN) && !defined(BIG_ENDIAN)
#   define BIG_ENDIAN __BIG_ENDIAN
#endif
#if defined(__LITTLE_ENDIAN) && !defined(LITTLE_ENDIAN)
#   define LITTLE_ENDIAN __LITTLE_ENDIAN
#endif
#if defined(__PDP_ENDIAN) && !defined(PDP_ENDIAN)
#   define PDP_ENDIAN __PDP_ENDIAN
#endif
#ifndef _INT64_DEFINED /* don't define 64-bit operations if unsupported */
#   undef htobe64
#   undef htole64
#   undef be64toh
#   undef le64toh
#endif

/* ========================================================================== */

#endif /* MACRODEFS_H_ */
