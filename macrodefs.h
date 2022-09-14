/**
 * @file macrodefs.h
 * @author Simon Bolivar
 * @date 13 Sep 2022
 * 
 * @brief File containing general-use definitions, annotations, and
 *        macro definitions.
 * 
 * @copyright LGPL-3.0
 */

#ifndef MACRODEFS_H_
#define MACRODEFS_H_

/* == C & C++ VERSION CHECK MACROS ========================================== */

#ifndef __MACRODEFS_C_VERSION

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
#   if defined(_MSC_VER) && defined(_MSVC_LANG) && (_MSVC_LANG > __cplusplus)
#       define __MACRODEFS_CPP_VERSION _MSVC_LANG
#   else
#       define __MACRODEFS_CPP_VERSION __cplusplus
#   endif
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

#endif

/* == MAJOR COMPILER VERSION CHECK MACROS =================================== */

#ifndef GCC_PREREQ

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
#ifdef __TINYC__
#   define TINYC_PREREQ(ver) ((ver) <= __TINYC__)
#else
#   define TINYC_PREREQ(ver) 0
#endif
#ifdef __SUNPRO_C
#   define SUN_PREREQ(ver) ((ver) <= __SUNPRO_C)
#else
#   define SUN_PREREQ(ver) 0
#endif
#ifdef __DMC__
#   define DMC_PREREQ(ver) ((ver) <= )
#else
#   define DMC_PREREQ(ver) 0
#endif
#ifdef _MSC_VER
#   define MSVC_PREREQ(ver) ((ver) <= _MSC_VER)
#   ifndef _MSVC_TRADITIONAL
#       define _MSVC_TRADITIONAL 1
#   endif
#else
#   define MSVC_PREREQ(ver) 0
#endif /* ICC <1400 reports GCC4.3 compatibility when it isn't */
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
#   elif GCC_PREREQ(30000)
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

#endif

/* == METAPROGRAMMING MACROS ================================================ */

#ifndef STRINGIFY

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

#endif

/* == VARIADIC MACRO METAPROGRAMMING ======================================== */

#if !defined(VARGPACK) || !defined(_NO_VA_ARGS)

/**
 * @def VARGPACK(...)
 * @brief Unpacks a set of variadic arguments to be used as a single token.
 * 
 * @param[in] ... Parameters to unpack.
 */
/**
 * @def VARGCOUNT(...)
 * @brief Counts how many arguments there are in a variadic macro.
 * @note Credit goes to Jens Gustedt, H Walters, and Luiz Martins
 * @link https://stackoverflow.com/a/66556553
 * 
 * @param[in] ... Parameters to count.
 */
/**
 * @def VARGAPPLY(macro, args)
 * @brief Applies a macro to a sequence of arguments.
 * 
 * @name[in] macro The name of a macro to repeat.
 * @name[in] extra
 * @name[in] args  List of arguments.
 */
#if GCC_PREREQ(30000) || defined(__TINYC__)
    __extension__
#   define VARGPACK(...) __VA_ARGS__
    ;
#   define _EXT_VA_ARGS 1
#elif MSVC_PREREQ(1400) || STDC_PREREQ(199901L) || CPP_PREREQ(201103L) \
    || (defined(__CC_ARM) && !defined(__GNUC__)) || defined(__DMC__)
#   define VARGPACK(...) __VA_ARGS__
#elif GCC_PREREQ(1) /* GNU C varargs */
#   define VARGPACK(args...) args
#   define _GNUC_VA_ARGS 1
#else
#   define _NO_VA_ARGS 1
#endif
#ifndef _NO_VA_ARGS
#   define _COMMA_1
#   define _COMMA_0 ,
#   define COMMA() ,
#   define SEMICOLON() ;
#   define SPACE()
#   define LOG_AND() &&
#   define LOG_OR() ||
#   define BIN_AND() &
#   define BIT_OR() |
#   define BIT_XOR() ^
#   define _EXPAND(x) x
#   define __PASTE3_(_0, _1, _2) _0 ## _1 ## _2
#   define _PASTE3(_0, _1, _2) __PASTE3_(_0, _1, _2)
#   define _PASTE5(_0, _1, _2, _3, _4) _0 ## _1 ## _2 ## _3 ## _4
#   define _IS_EMPTY_CASE_0001 ,
#   define _INVOKE_IF_NOT_LAST_11(x)
#   define _INVOKE_IF_NOT_LAST_10(x)
#   define _INVOKE_IF_NOT_LAST_01(x)
#   define _INVOKE_IF_NOT_LAST_00(x) x()
#   define __IS_EMPTY_(_0, _1, _2, _3) \
        _HAS_COMMA(_PASTE5(_IS_EMPTY_CASE_, _0, _1, _2, _3))
#   define _VARGISEMPTY_0 0
#   define _VARGISEMPTY_1 1
#   ifdef _GNUC_VA_ARGS
#       define __TUPHEAD_(x, args...) x
#       define _TUPHEAD(args...) VARGPACK(__TUPHEAD_(args,))
#       define __TUPTAIL_(x, args...) (args)
#       define _TUPTAIL(args...) VARGPACK(__TUPTAIL_(args))
#       define _ARG_100(_,\
            _100,_99,_98,_97,_96,_95,_94,_93,_92,_91,_90,_89,_88,_87,_86,_85, \
            _84,_83,_82,_81,_80,_79,_78,_77,_76,_75,_74,_73,_72,_71,_70,_69, \
            _68,_67,_66,_65,_64,_63,_62,_61,_60,_59,_58,_57,_56,_55,_54,_53, \
            _52,_51,_50,_49,_48,_47,_46,_45,_44,_43,_42,_41,_40,_39,_38,_37, \
            _36,_35,_34,_33,_32,_31,_30,_29,_28,_27,_26,_25,_24,_23,_22,_21, \
            _20,_19,_18,_17,_16,_15,_14,_13,_12,_11,_10,_9,_8,_7,_6,_5,_4,_3, \
            _2,X_,args...) X_
#       define _HAS_COMMA(args...) _EXPAND(_ARG_100(args, \
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, \
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0))
#       define _TRIGGER_PARENTHESIS_(args...) ,
#       define _IS_EMPTY(args...)  __IS_EMPTY_( \
            _HAS_COMMA(args), \
            _HAS_COMMA(_TRIGGER_PARENTHESIS_ args), \
            _HAS_COMMA(args (/*empty*/)), \
            _HAS_COMMA(_TRIGGER_PARENTHESIS_ args (/*empty*/)))
#       define _VARGCOUNT_EMPTY_1(args...) 0
#       define _VARGCOUNT_EMPTY_0(args...) _EXPAND(_ARG_100(args, \
            100,99,98,97,96,95,94,93,92,91,90,89,88,87,86,85,84,83,82,81, \
            80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,62,61, \
            60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41, \
            40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21, \
            20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1))
#       define VARGCOUNT(args...) CONCATENATE( \
            _VARGCOUNT_EMPTY_, _IS_EMPTY(args))(args)
#       define VARGEMPTY(args...) CONCATENATE(_VARGISEMPTY_, _IS_EMPTY(args))
#   else
        __extension__
#       define __TUPHEAD_(x, ...) x
        ;__extension__
#       define _TUPHEAD(...) VARGPACK(__TUPHEAD_(__VA_ARGS__,))
        ;__extension__
#       define __TUPTAIL_(x, ...) (__VA_ARGS__)
        ;__extension__
#       define _TUPTAIL(...) VARGPACK(__TUPTAIL_(__VA_ARGS__))
        ;__extension__
#       define _ARG_100(_,\
            _100,_99,_98,_97,_96,_95,_94,_93,_92,_91,_90,_89,_88,_87,_86,_85, \
            _84,_83,_82,_81,_80,_79,_78,_77,_76,_75,_74,_73,_72,_71,_70,_69, \
            _68,_67,_66,_65,_64,_63,_62,_61,_60,_59,_58,_57,_56,_55,_54,_53, \
            _52,_51,_50,_49,_48,_47,_46,_45,_44,_43,_42,_41,_40,_39,_38,_37, \
            _36,_35,_34,_33,_32,_31,_30,_29,_28,_27,_26,_25,_24,_23,_22,_21, \
            _20,_19,_18,_17,_16,_15,_14,_13,_12,_11,_10,_9,_8,_7,_6,_5,_4,_3, \
            _2,X_,...) X_
        ;__extension__
#       define _HAS_COMMA(...) _EXPAND(_ARG_100(__VA_ARGS__, \
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, \
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0))
        ;__extension__
#       define _TRIGGER_PARENTHESIS_(...) ,
        ;__extension__
#       define _IS_EMPTY(...)  __IS_EMPTY_( \
            _HAS_COMMA(__VA_ARGS__), \
            _HAS_COMMA(_TRIGGER_PARENTHESIS_ __VA_ARGS__), \
            _HAS_COMMA(__VA_ARGS__ (/*empty*/)), \
            _HAS_COMMA(_TRIGGER_PARENTHESIS_ __VA_ARGS__ (/*empty*/)))
        ;__extension__
#       define _VARGCOUNT_EMPTY_1(...) 0
        ;__extension__
#       define _VARGCOUNT_EMPTY_0(...) _EXPAND(_ARG_100(__VA_ARGS__, \
            100,99,98,97,96,95,94,93,92,91,90,89,88,87,86,85,84,83,82,81, \
            80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,62,61, \
            60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41, \
            40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21, \
            20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1))
        ;__extension__
#       define VARGCOUNT(...) CONCATENATE( \
            _VARGCOUNT_EMPTY_, _IS_EMPTY(__VA_ARGS__))(__VA_ARGS__)
        ;__extension__
#       define VARGEMPTY(...) CONCATENATE(_VARGISEMPTY_, _IS_EMPTY(__VA_ARGS__))
        ;__extension__
#       define PREFIX_COMMA(...) CONCATENATE(_COMMA_, VARGEMPTY(__VA_ARGS__))
        ;
#   endif
#   define _VARGAPPLY0(name, extra, sep, args)
#   define _VARGAPPLY1(name, extra, sep, args) name(extra, _TUPHEAD args)
#   define _VARGAPPLY2(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY1(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
		_VARGAPPLY1(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY3(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY2(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY2(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY4(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY3(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY3(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY5(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY4(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY4(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY6(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY5(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY5(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY7(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY6(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY6(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY8(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY7(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY7(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY9(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY8(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY8(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY10(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY9(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY9(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY11(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY10(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY10(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY12(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY11(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY11(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY13(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY12(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY12(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY14(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY13(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY13(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY15(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY14(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY14(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY16(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY15(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY15(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY17(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY16(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY16(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY18(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY17(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY17(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY19(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY18(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY18(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY20(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY19(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY19(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY21(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY20(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY20(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY22(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY21(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY21(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY23(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY22(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY22(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY24(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY23(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY23(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY25(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY24(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY24(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY26(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY25(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY25(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY27(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY26(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY26(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY28(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY27(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY27(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY29(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY28(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY28(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY30(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY29(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY29(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY31(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY30(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY30(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY32(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY31(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY31(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY33(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY32(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY32(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY34(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY33(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY33(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY35(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY34(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY34(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY36(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY35(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY35(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY37(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY36(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY36(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY38(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY37(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY37(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY39(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY38(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY38(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY40(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY39(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY39(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY41(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY40(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY40(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY42(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY41(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY41(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY43(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY42(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY42(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY44(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY43(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY43(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY45(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY44(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY44(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY46(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY45(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY45(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY47(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY46(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY46(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY48(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY47(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY47(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY49(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY48(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY48(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY50(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY49(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY49(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY51(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY50(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY50(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY52(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY51(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY51(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY53(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY52(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY52(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY54(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY53(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY53(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY55(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY54(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY54(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY56(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY55(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY55(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY57(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY56(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY56(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY58(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY57(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY57(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY59(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY58(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY58(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY60(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY59(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY59(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY61(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY60(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY60(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY62(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY61(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY61(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY63(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY62(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY62(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY64(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY63(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY63(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY65(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY64(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY64(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY66(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY65(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY65(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY67(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY66(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY66(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY68(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY67(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY67(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY69(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY68(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY68(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY70(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY69(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY69(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY71(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY70(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY70(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY72(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY71(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY71(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY73(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY72(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY72(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY74(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY73(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY73(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY75(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY74(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY74(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY76(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY75(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY75(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY77(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY76(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY76(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY78(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY77(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY77(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY79(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY78(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY78(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY80(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY79(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY79(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY81(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY80(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY80(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY82(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY81(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY81(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY83(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY82(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY82(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY84(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY83(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY83(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY85(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY84(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY84(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY86(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY85(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY85(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY87(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY86(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY86(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY88(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY87(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY87(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY89(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY88(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY88(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY90(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY89(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY89(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY91(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY90(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY90(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY92(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY91(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY91(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY93(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY92(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY92(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY94(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY93(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY93(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY95(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY94(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY94(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY96(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY95(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY95(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY97(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY96(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY96(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY98(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY97(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY97(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY99(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY98(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY98(name, extra, sep, _TUPTAIL args)
#   define _VARGAPPLY100(name, extra, sep, args) \
        name(extra, _TUPHEAD args) \
        _PASTE3(_INVOKE_IF_NOT_LAST_, \
            VARGEMPTY(name(extra, _TUPHEAD args)), \
            VARGEMPTY(_VARGAPPLY99(name, extra, sep, _TUPTAIL args)) \
        )(sep) \
        _VARGAPPLY99(name, extra, sep, _TUPTAIL args)
#   define VARGAPPLY(name, extra, args, sep) \
        CONCATENATE(_VARGAPPLY, VARGCOUNT args)(name, extra, sep, args)

#   define _VARGEACH(name, args) name(args)
#   define VARGEACH(name, args, sep) VARGAPPLY(_VARGEACH, name, args, sep)
#endif

#endif

/* == COMPILER & ARCHITECTURE STRING ======================================== */

#ifndef COMPILER_NAME

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
#if (defined(_WIN64) || defined(__WIN32__) || defined(__WIN32) \
    || defined(__WINDOWS__) ||  defined(__WIN64) || defined(__WIN64__) \
    || defined(__TOS_WIN__)) && !defined(_WIN32)
#   define _WIN32 1
#endif
#if defined(_WIN32) && (defined(__x86_64__) || defined(__aarch64__) \
    || defined(__ia64__) || defined(__powerpc64__) || defined(__WIN64) \
    || defined(__WIN64__)) && !defined(_WIN64)
#   define _WIN64 1
#endif
#if (defined(_WIN32) || defined(__MINGW32__)) && !defined(__WINRT__)
#   if defined(__has_include) && __has_include(<winapifamily.h>)
#       define _HAS_WINAPIFAMILY 1
#   elif MSVC_PREREQ(1700) && !_USING_V110_SDK71_
#       define _HAS_WINAPIFAMILY 1
#   endif
#   ifdef _HAS_WINAPIFAMILY
#       undef _HAS_WINAPIFAMILY
#       include <winapifamily.h>
#       if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) \
            && WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
#           define __WINRT__ 1
#       endif
#   endif
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
#elif defined(__IAR_SYSTEMS_ICC__)
#   define COMPILER_NAME "IAR C/C++ " STRINGIFY(__VER__)
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
#elif defined(__CA__)
#   if __CA__ / 100000 == 1
#       define __MACRODEFS_KEIL_MAJOR 1
#   elif __CA__ / 100000 == 2
#       define __MACRODEFS_KEIL_MAJOR 2
#   elif __CA__ / 100000 == 3
#       define __MACRODEFS_KEIL_MAJOR 3
#   elif __CA__ / 100000 == 4
#       define __MACRODEFS_KEIL_MAJOR 4
#   elif __CA__ / 100000 == 5
#       define __MACRODEFS_KEIL_MAJOR 5
#   elif __CA__ / 100000 == 6
#       define __MACRODEFS_KEIL_MAJOR 6
#   elif __CA__ / 100000 == 7
#       define __MACRODEFS_KEIL_MAJOR 7
#   elif __CA__ / 100000 == 8
#       define __MACRODEFS_KEIL_MAJOR 8
#   elif __CA__ / 100000 == 9
#       define __MACRODEFS_KEIL_MAJOR 9
#   else
#       define __MACRODEFS_KEIL_MAJOR 0
#   endif
#   if (__CA__ % 10000) / 10 == 1
#       define __MACRODEFS_KEIL_MINOR 1
#   elif (__CA__ % 10000) / 10 == 2
#       define __MACRODEFS_KEIL_MINOR 2
#   elif (__CA__ % 10000) / 10 == 3
#       define __MACRODEFS_KEIL_MINOR 3
#   elif (__CA__ % 10000) / 10 == 4
#       define __MACRODEFS_KEIL_MINOR 4
#   elif (__CA__ % 10000) / 10 == 5
#       define __MACRODEFS_KEIL_MINOR 5
#   elif (__CA__ % 10000) / 10 == 6
#       define __MACRODEFS_KEIL_MINOR 6
#   elif (__CA__ % 10000) / 10 == 7
#       define __MACRODEFS_KEIL_MINOR 7
#   elif (__CA__ % 10000) / 10 == 8
#       define __MACRODEFS_KEIL_MINOR 8
#   elif (__CA__ % 10000) / 10 == 9
#       define __MACRODEFS_KEIL_MINOR 9
#   else
#       define __MACRODEFS_KEIL_MINOR 0
#   endif
#   define COMPILER_NAME "KEIL CARM" STRINGIFY(__MACRODEFS_KEIL_MAJOR) \
        "." STRINGIFY(__MACRODEFS_KEIL_MINOR)
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
#   elif _MSC_VER == 1930
#       define __MACRODEFS_MSVC "2022 17.0"
#   elif _MSC_VER == 1931
#       define __MACRODEFS_MSVC "2022 17.1"
#   elif _MSC_VER == 1932
#       define __MACRODEFS_MSVC "2022 17.2"
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
#elif defined(__circle_build__)
#   define COMPILER_NAME "Circle Build " STRINGIFY(__circle_build__)
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
#elif defined(sgi) || defined(__sgi) || defined(__sgi__) \
    || defined(_SGI_SOURCE) || defined(__IRIX__)
#   ifndef __IRIX__
#       define __IRIX__ 1
#   endif
#   define OS_NAME "Irix"
#elif defined(__ros__)
#   define OS_NAME "Akaros"
#elif defined(__osf__) || defined(__osf)
#   ifndef __osf__
#       define __osf__ 1
#   endif
#   define OS_NAME "Tru64"
#elif defined(riscos) || defined(__riscos) || defined(__riscos__) \
    || defined(__RISCOS__)
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
#       ifndef __unix__
#           define __unix__ 1
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
#   if defined(__SVR4) || defined(__svr4__) || defined(_SYSTYPE_SVR4) \
    || defined(__SOLARIS__)
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
#   define OS_NAME "Universal Windows Platform"
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
#elif defined(__x86_64__) || defined(_M_X64) || defined(__x86_64) \
    || defined(__amd64__) || defined(__amd64) || defined(_M_AMD64)
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
#elif defined(__i386__) || defined(__i386) || defined(_M_IX86) \
    || defined(__THW_INTEL__) || defined(_M_I86) || defined(__386) \
    || defined(_X86_) || defined(__i386) || defined(i386) || defined(__IA32__) \
    || defined(__X86__) || defined(__INTEL__) || defined(__386__)
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
#elif defined(_M_ARM) || defined(__arm__) || defined(_ARM) \
    || defined(_M_ARM) || defined(__arm) \
    || (defined(__ARM_ARCH) && __ARM_ARCH == 7)
#   define ARCH_NAME "ARM32"
#   ifndef __arm__
#       define __arm__ 1
#   endif
#elif defined(__ia64__) || defined(_IA64) || defined(__IA64__) \
    || defined(__ia64) || defined(_M_IA64) || defined(__itanium__)
#   define ARCH_NAME "Itanium"
#   ifndef __ia64__
#       define __ia64__ 1
#   endif
#elif defined(__powerpc64__) || defined(__ppc64__) || defined(__PPC64__) \
    || defined(_ARCH_PPC64)
#   define ARCH_NAME "Power64"
#   ifndef __powerpc64__
#       define __powerpc64__ 1
#   endif
#elif defined(__powerpc) || defined(__powerpc__) || defined(__POWERPC__) \
    || defined(__ppc__) || defined(__PPC__) || defined(_ARCH_PPC) \
    || defined(_M_PPC) || defined(__ppc)
#   define ARCH_NAME "PowerPC"
#   ifndef __powerpc__
#       define __powerpc__ 1
#   endif
#elif defined(__sh__) || defined(__sh1__) || defined(__sh2__) \
    || defined(__sh3__) || defined(__SH3__) || defined(__SH4__) \
    || defined(__SH5__)
#   define ARCH_NAME "SuperH"
#   ifndef __sh__
#       define __sh__ 1
#   endif
#elif defined(__mips) || defined(mips) || defined(_MIPS_ISA) \
    || defined(_R3000) || defined(_R4000) || defined(_R5900) \
    || defined(__MIPS__) || defined(__mips__)
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
#elif defined(__m68k__) || defined(M68000) || defined(__MC68K__) \
    || defined(__mc68000__) || defined(__MC68000__) || defined(__mc68010__) \
    || defined(__mc68020__) || defined(__MC68020__) || defined(__mc68030__) \
    || defined(__MC68030__) || defined(__mc68040__) || defined(__mc68060__)
#   define ARCH_NAME "M68000"
#   ifndef __m68k__
#       define __m68k__ 1
#   endif
#else
#   define ARCH_NAME "(unknown)"
#endif /* check for ARM thumb instruction support */
#if (defined(__arm__) || defined(__aarch64__)) \
    && (defined(_M_ARMT) || defined(__TARGET_ARCH_THUMB)) && !defined(__thumb__)
#   define __thumb__ 1
#endif
#if ((defined(__arm__) && defined(__ARM_NEON__)) || defined(__aarch64__)) \
    && !defined(__ARM_NEON) /* check for ARM neon support */
#   define __ARM_NEON 1
#endif
#if defined(__VEC__) && !defined(__ALTIVEC__)
#   define __ALTIVEC__ 1
#endif
#if defined(__WINRT__) && (defined(__arm__) || defined(__aarch64__)) \
    && !defined(__ARM_NEON) /* winrt requires ARM neon support */
#   define __ARM_NEON 1
#endif
#if defined(__ARM_ARCH) && __ARM_ARCH >= 9
#   ifndef __ARM_FEATURE_SVE
#       define __ARM_FEATURE_SVE 1
#   endif
#   ifndef __ARM_FEATURE_SVE2
#       define __ARM_FEATURE_SVE2 1
#   endif
#endif

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
#if (STDC_PREREQ(1L) && (!STDC_PREREQ(199901L) || defined(SDCC))) \
    && !defined(__STDC_NO_VLA__)
#   define __STDC_NO_VLA__ 1
#endif
#if ((STDC_PREREQ(1L) && !STDC_PREREQ(201112L)) \
    || (defined(__has_include) && !__has_include(<threads.h>))) \
    && !defined(__STDC_NO_THREADS__)
#   define __STDC_NO_THREADS__ 1
#endif
#if ((STDC_PREREQ(1L) && !STDC_PREREQ(201112L)) \
    || (defined(__has_include) && !__has_include(<stdatomic.h>))) \
    && !defined(__STDC_NO_ATOMICS__)
#   define __STDC_NO_ATOMICS__ 1
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
#   elif defined(__IAR_SYSTEMS_ICC__)
#       define __macrodefs_attribute_alias                  1
#       define __macrodefs_attribute_aligned                1
#       define __macrodefs_attribute_always_inline          1
#       define __macrodefs_attribute_cmse_nonsecure_call    1
#       define __macrodefs_attribute_cmse_nonsecure_entry   1
#       define __macrodefs_attribute_const                  1
#       define __macrodefs_attribute_constructor            1
#       define __macrodefs_attribute_deprecated             1
#       define __macrodefs_attribute_naked                  1
#       define __macrodefs_attribute_noinline               1
#       define __macrodefs_attribute_noreturn               1
#       define __macrodefs_attribute_packed                 1
#       define __macrodefs_attribute_pcs                    1
#       define __macrodefs_attribute_pure                   1
#       define __macrodefs_attribute_section                1
#       define __macrodefs_attribute_target                 1
#       define __macrodefs_attribute_transparent_union      1
#       define __macrodefs_attribute_unused                 1
#       define __macrodefs_attribute_volatile               1
#       define __macrodefs_attribute_weak                   1
#   elif defined(__CC_ARM)
#       define __macrodefs_attribute_aligned                1
#       define __macrodefs_attribute_always_inline          1
#       define __macrodefs_attribute_deprecated             1
#       define __macrodefs_attribute_noreturn               1
#       define __macrodefs_attribute_weak                   1
#       define __macrodefs_attribute_weakref                1
#   elif defined(__GNUC__) /* GCC<5 doesn't have __has_attribute */
#       define __macrodefs_attribute_alias                      1
#       define __macrodefs_attribute___alias__                  1
#       define __macrodefs_attribute_always_inline              1
#       define __macrodefs_attribute___always_inline__          1
#       define __macrodefs_attribute_cdecl                      1
#       define __macrodefs_attribute___cdecl__                  1
#       define __macrodefs_attribute_constructor                1
#       define __macrodefs_attribute___constructor__            1
#       define __macrodefs_attribute_deprecated                 1
#       define __macrodefs_attribute___deprecated__             1
#       define __macrodefs_attribute_destructor                 1
#       define __macrodefs_attribute___destructor__             1
#       define __macrodefs_attribute_dllimport                  1
#       define __macrodefs_attribute___dllimport__              1
#       define __macrodefs_attribute_dllexport                  1
#       define __macrodefs_attribute___dllexport__              1
#       define __macrodefs_attribute_mode                       1
#       define __macrodefs_attribute___mode__                   1
#       define __macrodefs_attribute_no_instrument_function     1
#       define __macrodefs_attribute___no_instrument_function__ 1
#       define __macrodefs_attribute_nocommon                   1
#       define __macrodefs_attribute___nocommon__               1
#       define __macrodefs_attribute_noinline                   1
#       define __macrodefs_attribute___noinline__               1
#       define __macrodefs_attribute_packed                     1
#       define __macrodefs_attribute___packed__                 1
#       define __macrodefs_attribute_regparm                    1
#       define __macrodefs_attribute___regparm__                1
#       define __macrodefs_attribute_section                    1
#       define __macrodefs_attribute___section__                1
#       define __macrodefs_attribute_stdcall                    1
#       define __macrodefs_attribute___stdcall__                1
#       define __macrodefs_attribute_transparent_union          1
#       define __macrodefs_attribute___transparent_union__      1
#       define __macrodefs_attribute_warn_unused_result         1
#       define __macrodefs_attribute___warn_unused_result__     1
#       define __macrodefs_attribute_weak                       1
#       define __macrodefs_attribute___weak__                   1
#       define __macrodefs_attribute_weakref                    1
#       define __macrodefs_attribute___weakref__                1
#       if defined(__powerpc__) || defined(__powerpc64__) \
            || defined(__THW_RS6000) || defined(_IBMR2)
#           define __macrodefs_attribute_longcall               1
#           define __macrodefs_attribute___longcall__           1
#       endif
#       ifdef _WIN32
#           define __macrodefs_attribute_shared                 1
#           define __macrodefs_attribute___shared__             1
#       endif
#       if GCC_PREREQ(20000)
#           define __macrodefs_attribute_aligned                1
#           define __macrodefs_attribute___aligned__            1
#           define __macrodefs_attribute_format_arg             1
#           define __macrodefs_attribute___format_arg__         1
#           define __macrodefs_attribute_unused                 1
#           define __macrodefs_attribute___unused__             1
#           define __macrodefs_attribute_used                   1
#           define __macrodefs_attribute___used__               1
#       endif
#       if GCC_PREREQ(20500)
#           define __macrodefs_attribute_const                  1
#           define __macrodefs_attribute___const__              1
#           define __macrodefs_attribute_noreturn               1
#           define __macrodefs_attribute___noreturn__           1
#       endif
#       if GCC_PREREQ(29600)
#           define __macrodefs_attribute_pure                   1
#           define __macrodefs_attribute___pure__               1
#       endif
#       if GCC_PREREQ(30000)
#           define __macrodefs_attribute_format                 1
#           define __macrodefs_attribute___format__             1
#           define __macrodefs_attribute_may_alias              1
#           define __macrodefs_attribute___may_alias__          1
#           if CPP_PREREQ(1L)
#               define __macrodefs_attribute_init_priority      1
#               define __macrodefs_attribute___init_priority__  1
#               define __macrodefs_attribute_java_interface     1
#               define __macrodefs_attribute___java_interface__ 1
#           endif
#       endif
#       if GCC_PREREQ(30100)
#           define __macrodefs_attribute_malloc                 1
#           define __macrodefs_attribute___malloc__             1
#       endif
#       if GCC_PREREQ(30200)
#           define __macrodefs_attribute_vector_size            1
#           define __macrodefs_attribute___vector_size__        1
#       endif
#       if GCC_PREREQ(30300)
#           define __macrodefs_attribute_nothrow                1
#           define __macrodefs_attribute___nothrow__            1
#       endif
#       if GCC_PREREQ(30400) && CPP_PREREQ(1L)
#           define __macrodefs_attribute_strong                 1
#           define __macrodefs_attribute___strong__             1
#       endif
#       if GCC_PREREQ(40000)
#           define __macrodefs_attribute_visibility             1
#           define __macrodefs_attribute___visibility__         1
#       endif
#       if GCC_PREREQ(40103) || defined(__GNUC_GNU_INLINE__) \
            || defined(__GNUC_STDC_INLINE__)
#           define __macrodefs_attribute_gnu_inline             1
#           define __macrodefs_attribute___gnu_inline__         1
#       else /* notify that GCC is using GNU C inline semantics */
#           define __GNUC_GNU_INLINE__                          1
#       endif
#       if GCC_PREREQ(40300)
#           define __macrodefs_attribute_error                  1
#           define __macrodefs_attribute___error__              1
#           define __macrodefs_attribute_hot                    1
#           define __macrodefs_attribute___hot__                1
#           define __macrodefs_attribute_cold                   1
#           define __macrodefs_attribute___cold__               1
#       endif
#       if GCC_PREREQ(40600)
#           define __macrodefs_attribute_ifunc                  1
#           define __macrodefs_attribute___ifunc__              1
#       endif
#       if GCC_PREREQ(40800) && CPP_PREREQ(1L)
#           define __macrodefs_attribute_abi_tag                1
#           define __macrodefs_attribute___abi_tag__            1
#           if defined(__i386__) || defined(__x86_64__)
#               define __macrodefs_attribute_target             1
#               define __macrodefs_attribute___target__         1
#           endif
#       endif
#       if GCC_PREREQ(40900)
#           define __macrodefs_attribute_warn_unused            1
#           define __macrodefs_attribute___warn_unused__        1
#       endif
#   else
#       define __attribute__(x)
#   endif
#   define __has_attribute(x) __macrodefs_attribute_ ##x
#endif
#ifndef __has_builtin
#   ifdef __TINYC__
#       define __macrodefs_builtin___builtin_types_compatible_p 1
#       define __macrodefs_builtin___builtin_constant_p 1
#   elif defined(__GNUC__) /* GCC<10 doesn't have __has_builtin */
#       define __macrodefs_builtin___builtin_apply_args 1
#       define __macrodefs_builtin___builtin_apply 1
#       define __macrodefs_builtin___builtin_return 1
#       define __macrodefs_builtin___builtin_return_address 1
#       define __macrodefs_builtin___builtin_frame_address 1
#       define __macrodefs_builtin___builtin_constant_p 1
#       define __macrodefs_builtin___builtin_alloca 1
#       define __macrodefs_builtin___builtin_memcpy 1
#       define __macrodefs_builtin___builtin_memcmp 1
#       define __macrodefs_builtin___builtin_strcpy 1
#       define __macrodefs_builtin___builtin_strcmp 1
#       define __macrodefs_builtin___builtin_strlen 1
#       define __macrodefs_builtin___builtin_ffs 1
#       define __macrodefs_builtin___builtin_abs 1
#       define __macrodefs_builtin___builtin_fabs 1
#       define __macrodefs_builtin___builtin_labs 1
#       define __macrodefs_builtin___builtin_fabsf 1
#       define __macrodefs_builtin___builtin_fabsl 1
#       define __macrodefs_builtin___builtin_fabsl 1
#       define __macrodefs_builtin___builtin_sqrt 1
#       define __macrodefs_builtin___builtin_sqrtf 1
#       define __macrodefs_builtin___builtin_sqrtl 1
#       define __macrodefs_builtin___builtin_sin 1
#       define __macrodefs_builtin___builtin_sinf 1
#       define __macrodefs_builtin___builtin_sinl 1
#       define __macrodefs_builtin___builtin_cos 1
#       define __macrodefs_builtin___builtin_cosf 1
#       define __macrodefs_builtin___builtin_cosl 1
#       if GCC_PREREQ(30000)
#           define __macrodefs_builtin___builtin_bcmp 1
#           define __macrodefs_builtin___builtin_bzero 1
#           define __macrodefs_builtin___builtin_index 1
#           define __macrodefs_builtin___builtin_rindex 1
#           define __macrodefs_builtin___builtin_fprintf 1
#           define __macrodefs_builtin___builtin_fputs 1
#           define __macrodefs_builtin___builtin_memset 1
#           define __macrodefs_builtin___builtin_printf 1
#           define __macrodefs_builtin___builtin_strcat 1
#           define __macrodefs_builtin___builtin_strchr 1
#           define __macrodefs_builtin___builtin_strcspn 1
#           define __macrodefs_builtin___builtin_strncat 1
#           define __macrodefs_builtin___builtin_strncmp 1
#           define __macrodefs_builtin___builtin_strncpy 1
#           define __macrodefs_builtin___builtin_strpbrk 1
#           define __macrodefs_builtin___builtin_strrchr 1
#           define __macrodefs_builtin___builtin_strspn 1
#           define __macrodefs_builtin___builtin_strstr 1
#           define __macrodefs_builtin___builtin_isgreater 1
#           define __macrodefs_builtin___builtin_isgreaterequal 1
#           define __macrodefs_builtin___builtin_isless 1
#           define __macrodefs_builtin___builtin_islessequal 1
#           define __macrodefs_builtin___builtin_islessgreater 1
#           define __macrodefs_builtin___builtin_isunordered 1
#           define __macrodefs_builtin___builtin_expect 1
#           if STDC_PREREQ(199901L) || !defined(__STRICT_ANSI__)
#               define __macrodefs_builtin___builtin_conj 1
#               define __macrodefs_builtin___builtin_conjf 1
#               define __macrodefs_builtin___builtin_conjl 1
#               define __macrodefs_builtin___builtin_creal 1
#               define __macrodefs_builtin___builtin_crealf 1
#               define __macrodefs_builtin___builtin_creall 1
#               define __macrodefs_builtin___builtin_cimag 1
#               define __macrodefs_builtin___builtin_cimagf 1
#               define __macrodefs_builtin___builtin_cimagl 1
#               define __macrodefs_builtin___builtin_llabs 1
#               define __macrodefs_builtin___builtin_imaxabs 1
#           endif
#       endif
#       if GCC_PREREQ(30100)
#           define __macrodefs_builtin___builtin_fputs_unlocked 1
#           define __macrodefs_builtin___builtin_fprintf_unlocked 1
#           define __macrodefs_builtin___builtin_printf_unlocked 1
#           define __macrodefs_builtin___builtin_prefetch 1
#           if STDC_PREREQ(1L)
#               define __macrodefs_builtin___builtin_types_compatible_p 1
#               define __macrodefs_builtin___builtin_choose_expr 1
#           endif
#       endif
#       if GCC_PREREQ(30300)
#           define __macrodefs_builtin___builtin_abort 1
#           define __macrodefs_builtin___builtin_exit 1
#           define __macrodefs_builtin___builtin__exit 1
#           define __macrodefs_builtin___builtin_putchar 1
#           define __macrodefs_builtin___builtin_puts 1
#           define __macrodefs_builtin___builtin_scanf 1
#           define __macrodefs_builtin___builtin_sscanf 1
#           define __macrodefs_builtin___builtin_vprintf 1
#           define __macrodefs_builtin___builtin_vsprintf 1
#           define __macrodefs_builtin___builtin_log 1
#           define __macrodefs_builtin___builtin_logf 1
#           define __macrodefs_builtin___builtin_logl 1
#           define __macrodefs_builtin___builtin_huge_val 1
#           define __macrodefs_builtin___builtin_huge_valf 1
#           define __macrodefs_builtin___builtin_huge_vall 1
#           define __macrodefs_builtin___builtin_inf 1
#           define __macrodefs_builtin___builtin_inff 1
#           define __macrodefs_builtin___builtin_infl 1
#           define __macrodefs_builtin___builtin_nan 1
#           define __macrodefs_builtin___builtin_nanf 1
#           define __macrodefs_builtin___builtin_nanl 1
#           define __macrodefs_builtin___builtin_nans 1
#           define __macrodefs_builtin___builtin_nansf 1
#           define __macrodefs_builtin___builtin_nansl 1
#           if STDC_PREREQ(199901L) || !defined(__STRICT_ANSI__)
#               define __macrodefs_builtin___builtin__Exit 1
#               define __macrodefs_builtin___builtin_snprintf 1
#               define __macrodefs_builtin___builtin_vscanf 1
#               define __macrodefs_builtin___builtin_vsnprintf 1
#               define __macrodefs_builtin___builtin_vsscanf 1
#           endif
#           if defined(__osf__)
#               define __macrodefs_builtin___builtin_thread_pointer 1
#               define __macrodefs_builtin___builtin_set_thread_pointer 1
#           endif
#       endif
#       if GCC_PREREQ(30400)
#           define __macrodefs_builtin___builtin_dcgettext 1
#           define __macrodefs_builtin___builtin_dgettext 1
#           define __macrodefs_builtin___builtin_drem 1
#           define __macrodefs_builtin___builtin_dremf 1
#           define __macrodefs_builtin___builtin_dreml 1
#           define __macrodefs_builtin___builtin_exp10 1
#           define __macrodefs_builtin___builtin_exp10f 1
#           define __macrodefs_builtin___builtin_exp10l 1
#           define __macrodefs_builtin___builtin_ffs 1
#           define __macrodefs_builtin___builtin_ffsl 1
#           define __macrodefs_builtin___builtin_ffsll 1
#           define __macrodefs_builtin___builtin_gamma 1
#           define __macrodefs_builtin___builtin_gammaf 1
#           define __macrodefs_builtin___builtin_gammal 1
#           define __macrodefs_builtin___builtin_gettext 1
#           define __macrodefs_builtin___builtin_j0 1
#           define __macrodefs_builtin___builtin_j0f 1
#           define __macrodefs_builtin___builtin_j0l 1
#           define __macrodefs_builtin___builtin_j1 1
#           define __macrodefs_builtin___builtin_j1f 1
#           define __macrodefs_builtin___builtin_j1l 1
#           define __macrodefs_builtin___builtin_jn 1
#           define __macrodefs_builtin___builtin_jnf 1
#           define __macrodefs_builtin___builtin_jnl 1
#           define __macrodefs_builtin___builtin_mempcpy 1
#           define __macrodefs_builtin___builtin_pow10 1
#           define __macrodefs_builtin___builtin_pow10f 1
#           define __macrodefs_builtin___builtin_pow10l 1
#           define __macrodefs_builtin___builtin_scalb 1
#           define __macrodefs_builtin___builtin_scalbf 1
#           define __macrodefs_builtin___builtin_scalbl 1
#           define __macrodefs_builtin___builtin_significand 1
#           define __macrodefs_builtin___builtin_significandf 1
#           define __macrodefs_builtin___builtin_significandl 1
#           define __macrodefs_builtin___builtin_sincos 1
#           define __macrodefs_builtin___builtin_sincosf 1
#           define __macrodefs_builtin___builtin_sincosl 1
#           define __macrodefs_builtin___builtin_stpcpy 1
#           define __macrodefs_builtin___builtin_strdup 1
#           define __macrodefs_builtin___builtin_strfmon 1
#           define __macrodefs_builtin___builtin_y0 1
#           define __macrodefs_builtin___builtin_y0f 1
#           define __macrodefs_builtin___builtin_y0l 1
#           define __macrodefs_builtin___builtin_y1 1
#           define __macrodefs_builtin___builtin_y1f 1
#           define __macrodefs_builtin___builtin_y1l 1
#           define __macrodefs_builtin___builtin_yn 1
#           define __macrodefs_builtin___builtin_ynf 1
#           define __macrodefs_builtin___builtin_ynl 1
#           define __macrodefs_builtin___builtin_acos 1
#           define __macrodefs_builtin___builtin_acosf 1
#           define __macrodefs_builtin___builtin_acosl 1
#           define __macrodefs_builtin___builtin_asin 1
#           define __macrodefs_builtin___builtin_asinf 1
#           define __macrodefs_builtin___builtin_asinl 1
#           define __macrodefs_builtin___builtin_atan 1
#           define __macrodefs_builtin___builtin_atanf 1
#           define __macrodefs_builtin___builtin_atanl 1
#           define __macrodefs_builtin___builtin_atan2 1
#           define __macrodefs_builtin___builtin_atan2f 1
#           define __macrodefs_builtin___builtin_atan2l 1
#           define __macrodefs_builtin___builtin_ceil 1
#           define __macrodefs_builtin___builtin_ceilf 1
#           define __macrodefs_builtin___builtin_ceill 1
#           define __macrodefs_builtin___builtin_cosh 1
#           define __macrodefs_builtin___builtin_coshf 1
#           define __macrodefs_builtin___builtin_coshl 1
#           define __macrodefs_builtin___builtin_sinh 1
#           define __macrodefs_builtin___builtin_sinhf 1
#           define __macrodefs_builtin___builtin_sinhl 1
#           define __macrodefs_builtin___builtin_tanh 1
#           define __macrodefs_builtin___builtin_tanhf 1
#           define __macrodefs_builtin___builtin_tanhl 1
#           define __macrodefs_builtin___builtin_exp 1
#           define __macrodefs_builtin___builtin_expf 1
#           define __macrodefs_builtin___builtin_expl 1
#           define __macrodefs_builtin___builtin_floor 1
#           define __macrodefs_builtin___builtin_floorf 1
#           define __macrodefs_builtin___builtin_floorl 1
#           define __macrodefs_builtin___builtin_fmod 1
#           define __macrodefs_builtin___builtin_fmodf 1
#           define __macrodefs_builtin___builtin_fmodl 1
#           define __macrodefs_builtin___builtin_mod 1
#           define __macrodefs_builtin___builtin_modf 1
#           define __macrodefs_builtin___builtin_modl 1
#           define __macrodefs_builtin___builtin_frexp 1
#           define __macrodefs_builtin___builtin_frexpf 1
#           define __macrodefs_builtin___builtin_frexpl 1
#           define __macrodefs_builtin___builtin_ldexp 1
#           define __macrodefs_builtin___builtin_ldexpf 1
#           define __macrodefs_builtin___builtin_ldexpl 1
#           define __macrodefs_builtin___builtin_log10 1
#           define __macrodefs_builtin___builtin_log10f 1
#           define __macrodefs_builtin___builtin_log10l 1
#           define __macrodefs_builtin___builtin_log 1
#           define __macrodefs_builtin___builtin_logf 1
#           define __macrodefs_builtin___builtin_logl 1
#           define __macrodefs_builtin___builtin_pow 1
#           define __macrodefs_builtin___builtin_powf 1
#           define __macrodefs_builtin___builtin_powl 1
#           define __macrodefs_builtin___builtin_abort 1
#           define __macrodefs_builtin___builtin_malloc 1
#           define __macrodefs_builtin___builtin_calloc 1
#           define __macrodefs_builtin___builtin_fscanf 1
#           ifndef __macrodefs_builtin___builtin_snprintf
#               define __macrodefs_builtin___builtin_snprintf 1
#           endif
#           if STDC_PREREQ(199901L) || !defined(__STRICT_ANSI__)
#               define __macrodefs_builtin___builtin_acosh 1
#               define __macrodefs_builtin___builtin_acoshf 1
#               define __macrodefs_builtin___builtin_acoshl 1
#               define __macrodefs_builtin___builtin_asinh 1
#               define __macrodefs_builtin___builtin_asinhf 1
#               define __macrodefs_builtin___builtin_asinhl 1
#               define __macrodefs_builtin___builtin_atanh 1
#               define __macrodefs_builtin___builtin_atanhf 1
#               define __macrodefs_builtin___builtin_atanhl 1
#               define __macrodefs_builtin___builtin_cabs 1
#               define __macrodefs_builtin___builtin_cabsf 1
#               define __macrodefs_builtin___builtin_cabsl 1
#               define __macrodefs_builtin___builtin_carg 1
#               define __macrodefs_builtin___builtin_cargf 1
#               define __macrodefs_builtin___builtin_cargl 1
#               define __macrodefs_builtin___builtin_cacos 1
#               define __macrodefs_builtin___builtin_cacosf 1
#               define __macrodefs_builtin___builtin_cacosl 1
#               define __macrodefs_builtin___builtin_cacosh 1
#               define __macrodefs_builtin___builtin_cacoshf 1
#               define __macrodefs_builtin___builtin_cacoshl 1
#               define __macrodefs_builtin___builtin_casin 1
#               define __macrodefs_builtin___builtin_casinf 1
#               define __macrodefs_builtin___builtin_casinl 1
#               define __macrodefs_builtin___builtin_casinh 1
#               define __macrodefs_builtin___builtin_casinhf 1
#               define __macrodefs_builtin___builtin_casinhl 1
#               define __macrodefs_builtin___builtin_catan 1
#               define __macrodefs_builtin___builtin_catanf 1
#               define __macrodefs_builtin___builtin_catanl 1
#               define __macrodefs_builtin___builtin_catanh 1
#               define __macrodefs_builtin___builtin_catanhf 1
#               define __macrodefs_builtin___builtin_catanhl 1
#               define __macrodefs_builtin___builtin_cbrt 1
#               define __macrodefs_builtin___builtin_cbrtf 1
#               define __macrodefs_builtin___builtin_cbrtl 1
#               define __macrodefs_builtin___builtin_ccos 1
#               define __macrodefs_builtin___builtin_ccosf 1
#               define __macrodefs_builtin___builtin_ccosl 1
#               define __macrodefs_builtin___builtin_ccosh 1
#               define __macrodefs_builtin___builtin_ccoshf 1
#               define __macrodefs_builtin___builtin_ccoshl 1
#               define __macrodefs_builtin___builtin_csin 1
#               define __macrodefs_builtin___builtin_csinf 1
#               define __macrodefs_builtin___builtin_csinl 1
#               define __macrodefs_builtin___builtin_csinh 1
#               define __macrodefs_builtin___builtin_csinhf 1
#               define __macrodefs_builtin___builtin_csinhl 1
#               define __macrodefs_builtin___builtin_ctan 1
#               define __macrodefs_builtin___builtin_ctanf 1
#               define __macrodefs_builtin___builtin_ctanl 1
#               define __macrodefs_builtin___builtin_ctanh 1
#               define __macrodefs_builtin___builtin_ctanhf 1
#               define __macrodefs_builtin___builtin_ctanhl 1
#               define __macrodefs_builtin___builtin_cpow 1
#               define __macrodefs_builtin___builtin_cpowf 1
#               define __macrodefs_builtin___builtin_cpowl 1
#               define __macrodefs_builtin___builtin_cproj 1
#               define __macrodefs_builtin___builtin_cprojf 1
#               define __macrodefs_builtin___builtin_cprojl 1
#               define __macrodefs_builtin___builtin_copysign 1
#               define __macrodefs_builtin___builtin_copysignf 1
#               define __macrodefs_builtin___builtin_copysignl 1
#               define __macrodefs_builtin___builtin_erfc 1
#               define __macrodefs_builtin___builtin_erfcf 1
#               define __macrodefs_builtin___builtin_erfcl 1
#               define __macrodefs_builtin___builtin_erf 1
#               define __macrodefs_builtin___builtin_erff 1
#               define __macrodefs_builtin___builtin_erfl 1
#               define __macrodefs_builtin___builtin_exp2 1
#               define __macrodefs_builtin___builtin_exp2f 1
#               define __macrodefs_builtin___builtin_exp2l 1
#               define __macrodefs_builtin___builtin_expm1 1
#               define __macrodefs_builtin___builtin_expm1f 1
#               define __macrodefs_builtin___builtin_expm1l 1
#               define __macrodefs_builtin___builtin_fdim 1
#               define __macrodefs_builtin___builtin_fdimf 1
#               define __macrodefs_builtin___builtin_fdiml 1
#               define __macrodefs_builtin___builtin_fma 1
#               define __macrodefs_builtin___builtin_fmaf 1
#               define __macrodefs_builtin___builtin_fmal 1
#               define __macrodefs_builtin___builtin_fmax 1
#               define __macrodefs_builtin___builtin_fmaxf 1
#               define __macrodefs_builtin___builtin_fmaxl 1
#               define __macrodefs_builtin___builtin_fmin 1
#               define __macrodefs_builtin___builtin_fminf 1
#               define __macrodefs_builtin___builtin_fminl 1
#               define __macrodefs_builtin___builtin_hypot 1
#               define __macrodefs_builtin___builtin_hypotf 1
#               define __macrodefs_builtin___builtin_hypotl 1
#               define __macrodefs_builtin___builtin_ilogb 1
#               define __macrodefs_builtin___builtin_ilogbf 1
#               define __macrodefs_builtin___builtin_ilogbl 1
#               define __macrodefs_builtin___builtin_lgamma 1
#               define __macrodefs_builtin___builtin_lgammaf 1
#               define __macrodefs_builtin___builtin_lgammal 1
#               define __macrodefs_builtin___builtin_llrint 1
#               define __macrodefs_builtin___builtin_llrintf 1
#               define __macrodefs_builtin___builtin_llrintl 1
#               define __macrodefs_builtin___builtin_lrint 1
#               define __macrodefs_builtin___builtin_lrintf 1
#               define __macrodefs_builtin___builtin_lrintl 1
#               define __macrodefs_builtin___builtin_rint 1
#               define __macrodefs_builtin___builtin_rintf 1
#               define __macrodefs_builtin___builtin_rintl 1
#               define __macrodefs_builtin___builtin_llround 1
#               define __macrodefs_builtin___builtin_llroundf 1
#               define __macrodefs_builtin___builtin_llroundl 1
#               define __macrodefs_builtin___builtin_lround 1
#               define __macrodefs_builtin___builtin_lroundf 1
#               define __macrodefs_builtin___builtin_lroundl 1
#               define __macrodefs_builtin___builtin_round 1
#               define __macrodefs_builtin___builtin_roundf 1
#               define __macrodefs_builtin___builtin_roundl 1
#               define __macrodefs_builtin___builtin_log1pf 1
#               define __macrodefs_builtin___builtin_log1pff 1
#               define __macrodefs_builtin___builtin_log1pfl 1
#               define __macrodefs_builtin___builtin_log2 1
#               define __macrodefs_builtin___builtin_log2f 1
#               define __macrodefs_builtin___builtin_log2l 1
#               define __macrodefs_builtin___builtin_logb 1
#               define __macrodefs_builtin___builtin_logbf 1
#               define __macrodefs_builtin___builtin_logbl 1
#               define __macrodefs_builtin___builtin_nearbyint 1
#               define __macrodefs_builtin___builtin_nearbyintf 1
#               define __macrodefs_builtin___builtin_nearbyintl 1
#               define __macrodefs_builtin___builtin_nextafter 1
#               define __macrodefs_builtin___builtin_nextafterf 1
#               define __macrodefs_builtin___builtin_nextafterl 1
#               define __macrodefs_builtin___builtin_nexttoward 1
#               define __macrodefs_builtin___builtin_nexttowardf 1
#               define __macrodefs_builtin___builtin_nexttowardl 1
#               define __macrodefs_builtin___builtin_remainder 1
#               define __macrodefs_builtin___builtin_remainderf 1
#               define __macrodefs_builtin___builtin_remainderl 1
#               define __macrodefs_builtin___builtin_remquo 1
#               define __macrodefs_builtin___builtin_remquof 1
#               define __macrodefs_builtin___builtin_remquol 1
#               define __macrodefs_builtin___builtin_scalbln 1
#               define __macrodefs_builtin___builtin_scalblnf 1
#               define __macrodefs_builtin___builtin_scalblnl 1
#               define __macrodefs_builtin___builtin_scalbn 1
#               define __macrodefs_builtin___builtin_scalbnf 1
#               define __macrodefs_builtin___builtin_scalbnl 1
#               define __macrodefs_builtin___builtin_tgamma 1
#               define __macrodefs_builtin___builtin_tgammaf 1
#               define __macrodefs_builtin___builtin_tgammal 1
#               define __macrodefs_builtin___builtin_trunc 1
#               define __macrodefs_builtin___builtin_truncf 1
#               define __macrodefs_builtin___builtin_truncl 1
#               define __macrodefs_builtin___builtin_vfscanf 1
#           endif
#       endif
#       if GCC_PREREQ(40000)
#           define __macrodefs_builtin___builtin_signbit 1
#           define __macrodefs_builtin___builtin_signbitf 1
#           define __macrodefs_builtin___builtin_signbitl 1
#           define __macrodefs_builtin___builtin_toascii 1
#           define __macrodefs_builtin___builtin_isalnum 1
#           define __macrodefs_builtin___builtin_isalpha 1
#           define __macrodefs_builtin___builtin_iscntrl 1
#           define __macrodefs_builtin___builtin_isdigit 1
#           define __macrodefs_builtin___builtin_isgraph 1
#           define __macrodefs_builtin___builtin_islower 1
#           define __macrodefs_builtin___builtin_isprint 1
#           define __macrodefs_builtin___builtin_ispunct 1
#           define __macrodefs_builtin___builtin_isspace 1
#           define __macrodefs_builtin___builtin_isupper 1
#           define __macrodefs_buitlin___builtin_isxdigit 1
#           define __macrodefs_builtin___builtin_tolower 1
#           define __macrodefs_builtin___builtin_toupper 1
#           define __macrodefs_builtin___builtin_ffs 1
#           define __macrodefs_builtin___builtin_ffsl 1
#           define __macrodefs_builtin___builtin_ffsll 1
#           define __macrodefs_builtin___builtin_clz 1
#           define __macrodefs_builtin___builtin_clzl 1
#           define __macrodefs_builtin___builtin_clzll 1
#           define __macrodefs_builtin___builtin_ctz 1
#           define __macrodefs_builtin___builtin_ctzl 1
#           define __macrodefs_builtin___builtin_ctzll 1
#           define __macrodefs_builtin___builtin_popcount 1
#           define __macrodefs_builtin___builtin_popcountl 1
#           define __macrodefs_builtin___builtin_popcountll 1
#           define __macrodefs_builtin___builtin_parity 1
#           define __macrodefs_builtin___builtin_parityl 1
#           define __macrodefs_builtin___builtin_parityll 1
#           define __macrodefs_builtin___builtin_powi 1
#           define __macrodefs_builtin___builtin_powif 1
#           define __macrodefs_builtin___builtin_powil 1
#           define __macrodefs_builtin___builtin_offsetof 1
#           if STDC_PREREQ(199409L) || !defined(__STRICT_ANSI__)
#               define __macrodefs_builtin___builtin_iswalnum 1
#               define __macrodefs_builtin___builtin_iswalpha 1
#               define __macrodefs_builtin___builtin_iswcntrl 1
#               define __macrodefs_builtin___builtin_iswdigit 1
#               define __macrodefs_builtin___builtin_iswgraph 1
#               define __macrodefs_builtin___builtin_iswlower 1
#               define __macrodefs_builtin___builtin_iswprint 1
#               define __macrodefs_builtin___builtin_iswpunct 1
#               define __macrodefs_builtin___builtin_iswspace 1
#               define __macrodefs_builtin___builtin_iswupper 1
#               define __macrodefs_builtin___builtin_iswxdigit 1
#               define __macrodefs_builtin___builtin_towlower 1
#               define __macrodefs_builtin___builtin_towupper 1
#           endif
#           if STDC_PREREQ(199901L) || !defined(__STRICT_ANSI__)
#               define __macrodefs_builtin___builtin_isblank 1
#               define __macrodefs_builtin___builtin_iswblank 1
#           endif
#       endif
#       if GCC_PREREQ(40100)
#           define __macrodefs_builtin___builtin_va_start 1
#           define __macrodefs_builtin___builtin_va_arg 1
#           define __macrodefs_builtin___builtin_va_end 1
#           define __macrodefs_builtin___builtin_va_copy 1
#           define __macrodefs_builtin___builtin_stpncpy 1
#           define __macrodefs_builtin___builtin_strcasecmp 1
#           define __macrodefs_builtin___builtin_strncasecmp 1
#           define __macrodefs_builtin___builtin_strndup 1
#           define __macrodefs_builtin___builtin_object_size 1
#           define __macrodefs_builtin___builtin___memcpy_chk 1
#           define __macrodefs_builtin___builtin___mempcpy_chk 1
#           define __macrodefs_builtin___builtin___memmove_chk 1
#           define __macrodefs_builtin___builtin___memset_chk 1
#           define __macrodefs_builtin___builtin___strcpy_chk 1
#           define __macrodefs_builtin___builtin___stpcpy_chk 1
#           define __macrodefs_builtin___builtin___strncpy_chk 1
#           define __macrodefs_builtin___builtin___strcat_chk 1
#           define __macrodefs_builtin___builtin___strncat_chk 1
#           define __macrodefs_builtin___builtin___printf_chk 1
#           define __macrodefs_builtin___builtin___fprintf_chk 1
#           define __macrodefs_builtin___builtin___sprintf_chk 1
#           define __macrodefs_builtin___builtin___snprintf_chk 1
#           define __macrodefs_builtin___builtin___vprintf_chk 1
#           define __macrodefs_builtin___builtin___vfprintf_chk 1
#           define __macrodefs_builtin___builtin___vsprintf_chk 1
#           define __macrodefs_builtin___builtin___vsnprintf_chk 1
#           define __macrodefs_builtin___sync_fetch_and_add 1
#           define __macrodefs_builtin___sync_fetch_and_sub 1
#           define __macrodefs_builtin___sync_fetch_and_or 1
#           define __macrodefs_builtin___sync_fetch_and_and 1
#           define __macrodefs_builtin___sync_fetch_and_xor 1
#           define __macrodefs_builtin___sync_fetch_and_nand 1
#           define __macrodefs_builtin___sync_add_and_fetch 1
#           define __macrodefs_builtin___sync_sub_and_fetch 1
#           define __macrodefs_builtin___sync_or_and_fetch 1
#           define __macrodefs_builtin___sync_and_and_fetch 1
#           define __macrodefs_builtin___sync_xor_and_fetch 1
#           define __macrodefs_builtin___sync_nand_and_fetch 1
#           define __macrodefs_builtin___sync_bool_compare_and_swap 1
#           define __macrodefs_builtin___sync_val_compare_and_swap 1
#           define __macrodefs_builtin___sync_synchronize 1
#           define __macrodefs_builtin___sync_lock_test_and_set 1
#           define __macrodefs_builtin___sync_lock_release 1
#           if STDC_PREREQ(199901L) || !defined(__STRICT_ANSI__)
#               define __macrodefs_builtin___builtin_clog 1
#               define __macrodefs_builtin___builtin_clogf 1
#               define __macrodefs_builtin___builtin_clogl 1
#           endif
#       endif
#       if GCC_PREREQ(40200)
#           define __macrodefs_builtin___builtin_trap 1
#           define __macrodefs_builtin___builtin_nand32 1
#           define __macrodefs_builtin___builtin_nand64 1
#           define __macrodefs_builtin___builtin_nand128 1
#           define __macrodefs_builtin___builtin_infd32 1
#           define __macrodefs_builtin___builtin_infd64 1
#           define __macrodefs_builtin___builtin_infd128 1
#       endif
#       if GCC_PREREQ(40300)
#           define __macrodefs_builtin___builtin_gamma_r 1
#           define __macrodefs_builtin___builtin_gammaf_r 1
#           define __macrodefs_builtin___builtin_gammal_r 1
#           define __macrodefs_builtin___builtin_isfinite 1
#           define __macrodefs_builtin___builtin_isnormal 1
#           define __macrodefs_builtin___builtin_lgamma_r 1
#           define __macrodefs_builtin___builtin_lgammaf_r 1
#           define __macrodefs_builtin___builtin_lgammal_r 1
#           define __macrodefs_builtin___builtin___clear_cache 1
#           define __macrodefs_builtin___builtin_bswap32 1
#           define __macrodefs_builtin___builtin_bswap64 1
#           define __macrodefs_builtin___builtin_va_arg_pack 1
#           define __macrodefs_builtin___builtin_va_arg_pack_len 1
#           if defined(__i386__) || defined(__x86_64__)
#               define __macrodefs_builtin___builtin_fabsq 1
#               define __macrodefs_builtin___builtin_copysignq 1
#               define __macrodefs_builtin___builtin_infq 1
#           endif
#           if CPP_PREREQ(1L)
#               define __macrodefs_builtin___has_nothrow_assign 1
#               define __macrodefs_builtin___has_nothrow_copy 1
#               define __macrodefs_builtin___has_nothrow_constructor 1
#               define __macrodefs_builtin___has_trivial_assign 1
#               define __macrodefs_builtin___has_trivial_copy 1
#               define __macrodefs_builtin___has_trivial_constructor 1
#               define __macrodefs_builtin___has_trivial_destructor 1
#               define __macrodefs_builtin___has_virtual_destructor 1
#               define __macrodefs_builtin___is_abstract 1
#               define __macrodefs_builtin___is_base_of 1
#               define __macrodefs_builtin___is_class 1
#               define __macrodefs_builtin___is_empty 1
#               define __macrodefs_builtin___is_enum 1
#               define __macrodefs_builtin___is_pod 1
#               define __macrodefs_builtin___is_polymorphic 1
#               define __macrodefs_builtin___is_union 1
#           endif
#       endif
#       if GCC_PREREQ(40400)
#           define __macrodefs_builtin___builtin_fpclassify 1
#           define __macrodefs_builtin___builtin_isinf_sign 1
#           define __macrodefs_builtin___builtin_isinf 1
#           define __macrodefs_builtin___builtin_isnan 1
#           define __macrodefs_builtin_isinf 1
#           define __macrodefs_builtin_isnan 1
#       endif
#       if GCC_PREREQ(40500)
#           define __macrodefs_builtin___builtin_unreachable 1
#           define __macrodefs_builtin___builtin_extract_return_address 1
#           define __macrodefs_builtin___builtin_frob_return_address 1
#           if defined(__i386__) || defined(__x86_64__)
#               define __macrodefs_builtin___builtin_ms_va_start 1
#               define __macrodefs_builtin___builtin_ms_va_end 1
#               define __macrodefs_builtin___builtin_ms_va_copy 1
#               define __macrodefs_builtin___builtin_huge_valq 1
#           endif
#       endif
#       if GCC_PREREQ(40600) && CPP_PREREQ(1L)
#           define __macrodefs_builtin___is_literal_type 1
#           define __macrodefs_builtin___is_standard_layout 1
#           define __macrodefs_builtin___is_trivial 1
#       endif
#       if GCC_PREREQ(40700)
#           define __macrodefs_builtin___builtin_assume_aligned 1
#           define __macrodefs_builtin___builtin_complex 1
#           define __macrodefs_builtin___builtin_clrsb 1
#           define __macrodefs_builtin___builtin_clrsbl 1
#           define __macrodefs_builtin___builtin_clrsbll 1
#           define __macrodefs_builtin___builtin_shuffle 1
#           define __macrodefs_builtin___atomic_load_n 1
#           define __macrodefs_builtin___atomic_load 1
#           define __macrodefs_builtin___atomic_store_n 1
#           define __macrodefs_builtin___atomic_store 1
#           define __macrodefs_builtin___atomic_exchange_n 1
#           define __macrodefs_builtin___atomic_exchange 1
#           define __macrodefs_builtin___atomic_compare_exchange_n 1
#           define __macrodefs_builtin___atomic_compare_exchange 1
#           define __macrodefs_builtin___atomic_add_fetch 1
#           define __macrodefs_builtin___atomic_sub_fetch 1
#           define __macrodefs_builtin___atomic_and_fetch 1
#           define __macrodefs_builtin___atomic_or_fetch 1
#           define __macrodefs_builtin___atomic_xor_fetch 1
#           define __macrodefs_builtin___atomic_nand_fetch 1
#           define __macrodefs_builtin___atomic_fetch_add 1
#           define __macrodefs_builtin___atomic_fetch_sub 1
#           define __macrodefs_builtin___atomic_fetch_and 1
#           define __macrodefs_builtin___atomic_fetch_or 1
#           define __macrodefs_builtin___atomic_fetch_xor 1
#           define __macrodefs_builtin___atomic_fetch_nand 1
#           define __macrodefs_builtin___atomic_test_and_set 1
#           define __macrodefs_builtin___atomic_clear 1
#           define __macrodefs_builtin___atomic_thread_fence 1
#           define __macrodefs_builtin___atomic_signal_fence 1
#           define __macrodefs_builtin___atomic_always_lock_free 1
#           define __macrodefs_builtin___atomic_is_lock_free 1
#           if defined(__i386__) || defined(__x86_64__)
#               define __macrodefs_builtin___builtin_ia32_pause 1
#           endif
#           if CPP_PREREQ(1L)
#               define __macrodefs_builtin___underlying_type 1
#           endif
#       endif
#       if GCC_PREREQ(40800)
#           define __macrodefs_builtin___builtin_LINE 1
#           define __macrodefs_builtin___builtin_FUNCTION 1
#           define __macrodefs_builtin___builtin_FILE 1
#           define __macrodefs_builtin___builtin_bswap16 1
#           undef __macrodefs_builtin___builtin_extract_return_address
#           define __macrodefs_builtin___builtin_extract_return_addr 1
#       endif
#       if GCC_PREREQ(50000)
#           if !CPP_PREREQ(1)
#               define __macrodefs_builtin___builtin_call_with_static_chain 1
#           endif
#           define __macrodefs_builtin___builtin___bnd_set_ptr_bounds 1
#           define __macrodefs_builtin___builtin___bnd_narrow_ptr_bounds 1
#           define __macrodefs_builtin___builtin___bnd_copy_ptr_bounds 1
#           define __macrodefs_builtin___builtin___bnd_init_ptr_bounds 1
#           define __macrodefs_builtin___builtin___bnd_null_ptr_bounds 1
#           define __macrodefs_builtin___builtin___bnd_store_ptr_bounds 1
#           define __macrodefs_builtin___builtin___bnd_chk_ptr_lbounds 1
#           define __macrodefs_builtin___builtin___bnd_chk_ptr_ubounds 1
#           define __macrodefs_builtin___builtin___bnd_chk_ptr_bounds 1
#           define __macrodefs_builtin___builtin___bnd_get_ptr_lbound 1
#           define __macrodefs_builtin___builtin___bnd_get_ptr_ubound 1
#           define __macrodefs_builtin___builtin_add_overflow 1
#           define __macrodefs_builtin___builtin_sadd_overflow 1
#           define __macrodefs_builtin___builtin_saddl_overflow 1
#           define __macrodefs_builtin___builtin_saddll_overflow 1
#           define __macrodefs_builtin___builtin_uadd_overflow 1
#           define __macrodefs_builtin___builtin_uaddl_overflow 1
#           define __macrodefs_builtin___builtin_uaddll_overflow 1
#           define __macrodefs_builtin___builtin_sub_overflow 1
#           define __macrodefs_builtin___builtin_ssub_overflow 1
#           define __macrodefs_builtin___builtin_ssubl_overflow 1
#           define __macrodefs_builtin___builtin_ssubll_overflow 1
#           define __macrodefs_builtin___builtin_usub_overflow 1
#           define __macrodefs_builtin___builtin_usubl_overflow 1
#           define __macrodefs_builtin___builtin_usubll_overflow 1
#           define __macrodefs_builtin___builtin_mul_overflow 1
#           define __macrodefs_builtin___builtin_smul_overflow 1
#           define __macrodefs_builtin___builtin_smull_overflow 1
#           define __macrodefs_builtin___builtin_smulll_overflow 1
#           define __macrodefs_builtin___builtin_umul_overflow 1
#           define __macrodefs_builtin___builtin_umull_overflow 1
#           define __macrodefs_builtin___builtin_umulll_overflow 1
#           if defined(__i386__) || defined(__x86_64__)
#               define __macrodefs_builtin___builtin_cpu_init 1
#               define __macrodefs_builtin___builtin_cpu_is 1
#               define __macrodefs_builtin___builtin_cpu_supports 1
#           endif
#           if defined(__powerpc__) || defined(__powerpc64__)
#               define __macrodefs_builtin___builtin_recipdiv 1
#               define __macrodefs_builtin___builtin_recipdivf 1
#               define __macrodefs_builtin___builtin_rsqrt 1
#               define __macrodefs_builtin___builtin_rsqrtf 1
#               define __macrodefs_builtin___builtin_ppc_get_timebase 1
#               define __macrodefs_builtin___builtin_ppc_mftb 1
#               define __macrodefs_builtin___builtin_unpack_longdouble 1
#               define __macrodefs_builtin___builtin_pack_longdouble 1
#           endif
#       endif
#       if GCC_PREREQ(60000)
#           define __macrodefs_builtin___builtin_alloca_with_align 1
#           if STDC_PREREQ(199901L) || !defined(__STRICT_ANSI__)
#               define __macrodefs_builtin___builtin_clog10 1
#               define __macrodefs_builtin___builtin_clog10f 1
#               define __macrodefs_builtin___builtin_clog10l 1
#           endif
#           if defined(__powerpc__) || defined(__powerpc64__)
#               define __macrodefs_builtin___builtin_cpu_init 1
#               define __macrodefs_builtin___builtin_cpu_is 1
#               define __macrodefs_builtin___builtin_cpu_supports 1
#           endif
#           if CPP_PREREQ(1L)
#               define __macrodefs_builtin___is_same 1
#           endif
#       endif
#       if GCC_PREREQ(70000)
#           define __macrodefs_builtin___builtin_add_overflow_p 1
#           define __macrodefs_builtin___builtin_sub_overflow_p 1
#           define __macrodefs_builtin___builtin_mul_overflow_p 1
#           define __macrodefs_builtin___builtin_fabsf32 1
#           define __macrodefs_builtin___builtin_fabsf32x 1
#           define __macrodefs_builtin___builtin_fabsf64 1
#           define __macrodefs_builtin___builtin_fabsf64x 1
#           define __macrodefs_builtin___builtin_fabsf128 1
#           define __macrodefs_builtin___builtin_copysignf32 1
#           define __macrodefs_builtin___builtin_copysignf32x 1
#           define __macrodefs_builtin___builtin_copysignf64 1
#           define __macrodefs_builtin___builtin_copysignf64x 1
#           define __macrodefs_builtin___builtin_copysignf128 1
#           define __macrodefs_builtin___builtin_huge_valf32 1
#           define __macrodefs_builtin___builtin_huge_valf32x 1
#           define __macrodefs_builtin___builtin_huge_valf64 1
#           define __macrodefs_builtin___builtin_huge_valf64x 1
#           define __macrodefs_builtin___builtin_huge_valf128 1
#           define __macrodefs_builtin___builtin_inff32 1
#           define __macrodefs_builtin___builtin_inff32x 1
#           define __macrodefs_builtin___builtin_inff64 1
#           define __macrodefs_builtin___builtin_inff64x 1
#           define __macrodefs_builtin___builtin_inff128 1
#           define __macrodefs_builtin___builtin_nanf32 1
#           define __macrodefs_builtin___builtin_nanf32x 1
#           define __macrodefs_builtin___builtin_nanf64 1
#           define __macrodefs_builtin___builtin_nanf64x 1
#           define __macrodefs_builtin___builtin_nanf128 1
#           define __macrodefs_builtin___builtin_nansf32 1
#           define __macrodefs_builtin___builtin_nansf32x 1
#           define __macrodefs_builtin___builtin_nansf64 1
#           define __macrodefs_builtin___builtin_nansf64x 1
#           define __macrodefs_builtin___builtin_nansf128 1
#           ifdef __ALTIVEC__
#               define __macrodefs_builtin___builtin_fabsq 1
#               define __macrodefs_builtin___builtin_copysignq 1
#               define __macrodefs_builtin___builtin_huge_valq 1
#               define __macrodefs_builtin___builtin_infq 1
#           endif
#           if defined(__ALTIVEC__) || defined(__i386__) || defined(__x86_64__)
#               define __macrodefs_builtin___builtin_nanq 1
#               define __macrodefs_builtin___builtin_nansq 1
#           endif
#           if CPP_PREREQ(1L)
#               define __macrodefs_builtin___builtin_launder 1
#           endif
#       endif
#       if GCC_PREREQ(80000)
#           define __macrodefs_builtin___builtin_alloca_with_align_and_max 1
#           define __macrodefs_builtin___builtin_extend_pointer 1
#           if STDC_PREREQ(1L)
#               define __macrodefs_builtin___builtin_tgmath 1
#           else
#               define __macrodefs_builtin___integer_pack 1
#           endif
#       endif
#       if GCC_PREREQ(90000)
#           define __macrodefs_builtin___builtin_expect_with_probability 1
#           define __macrodefs_builtin___builtin_has_attribute 1
#           define __macrodefs_builtin___builtin_speculation_safe_value 1
#           define __macrodefs_builtin___builtin_convertvector 1
#           define __macrodefs_builtin___builtin_goacc_parlevel_id 1
#           define __macrodefs_builtin___builtin_goacc_parlevel_size 1
#           define __macrodefs_builtin___builtin_setjmp 1
#           define __macrodefs_builtin___builtin_longjmp 1
#           if CPP_PREREQ(1L)
#               define __macrodefs_builtin___builtin_is_constant_evaluated 1
#           endif
#       endif
#   elif MSVC_PREREQ(1)
#       if MSVC_PREREQ(1915) && CPP_PREREQ(201703L)
#           define __macrodefs_builtin___builtin_launder 1
#       endif
#       if MSVC_PREREQ(1926)
#           define __macrodefs_builtin___builtin_FILE 1
#           define __macrodefs_builtin___builtin_FUNCTION 1
#           define __macrodefs_builtin___builtin_LINE 1
#           define __macrodefs_builtin___builtin_COLUMN 1
#       endif
#   endif
#   define __has_builtin(x) __macrodefs_builtin_ ##x
#endif
#if !defined(__has_c_attribute) \
    || CPP_PREREQ(1L) /* C18- and C++ don't have C attributes */
#   define __has_c_attribute(x) 0L
#endif
#if !defined(__has_cpp_attribute) \
    || STDC_PREREQ(1L) /* C++17- doesn't have __has_cpp_attribute */
#   if CPP_PREREQ(201103L)
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
#   else
#       define __has_cpp_attribute(x) 0L
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
#       if MSVC_PREREQ(1100)
#           define __macrodefs_declspec_attribute_selectany     1
#           define __macrodefs_declspec_attribute_uuid          1
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
#   ifdef __TINYC__
#       define __macrodefs_extension_cxx_binary_literals 1
#       define __macrodefs_extension___cxx_binary_literals__ 1
#   elif defined(__GNUC__)
#       define __macrodefs_extension_gnu_asm 1
#       define __macrodefs_extension___gnu_asm__ 1
#       if GCC_PREREQ(40300)
#           define __macrodefs_extension_cxx_binary_literals 1
#           define __macrodefs_extension___cxx_binary_literals__ 1
#           define __macrodefs_extension_cxx_decltype 1
#           define __macrodefs_extension___cxx_decltype__ 1
#           define __macrodefs_extension_cxx_rvalue_references 1
#           define __macrodefs_extension___cxx_rvalue_references__ 1
#           define __macrodefs_extension_cxx_static_assert 1
#           define __macrodefs_extension___cxx_static_assert__ 1
#       endif
#       if GCC_PREREQ(40400)
#           define __macrodefs_extension_cxx_auto_type 1
#           define __macrodefs_extension___cxx_auto_type__ 1
#           define __macrodefs_extension_cxx_defaulted_functions 1
#           define __macrodefs_extension___cxx_defaulted_functions__ 1
#           define __macrodefs_extension_cxx_deleted_functions 1
#           define __macrodefs_extension___cxx_deleted_functions__ 1
#           define __macrodefs_extension_cxx_generalized_initializers 1
#           define __macrodefs_extension___cxx_generalized_initializers__ 1
#           define __macrodefs_extension_cxx_inline_namespaces 1
#           define __macrodefs_extension___cxx_inline_namespaces__ 1
#           define __macrodefs_extension_cxx_strong_enums 1
#           define __macrodefs_extension___cxx_strong_enums__ 1
#           define __macrodefs_extension_cxx_trailing_return 1
#           define __macrodefs_extension___cxx_trailing_return__ 1
#           define __macrodefs_extension_cxx_unicode_literals 1
#           define __macrodefs_extension___cxx_unicode_literals__ 1
#           define __macrodefs_extension_cxx_variadic_templates 1
#           define __macrodefs_extension___cxx_variadic_templates__ 1
#       endif
#       if GCC_PREREQ(40500)
#           define __macrodefs_extension_attribute_deprecated_with_message 1
#           define __macrodefs_extension___attribute_deprecated_with_message__ 1
#           define __macrodefs_extension_cxx_default_function_template_args 1
#          define __macrodefs_extension___cxx_default_function_template_args__ 1
#           define __macrodefs_extension_cxx_explicit_conversions 1
#           define __macrodefs_extension___cxx_explicit_conversions__ 1
#           define __macrodefs_extension_cxx_lambdas 1
#           define __macrodefs_extension___cxx_lambdas__ 1
#           define __macrodefs_extension_cxx_raw_string_literals 1
#           define __macrodefs_extension___cxx_raw_string_literals__ 1
#       endif
#       if GCC_PREREQ(40600)
#           define __macrodefs_extension_cxx_constexpr 1
#           define __macrodefs_extension___cxx_constexpr__ 1
#           define __macrodefs_extension_cxx_implicit_moves 1
#           define __macrodefs_extension___cxx_implicit_moves__ 1
#           define __macrodefs_extension_cxx_noexcept 1
#           define __macrodefs_extension___cxx_noexcept__ 1
#           define __macrodefs_extension_cxx_range_for 1
#           define __macrodefs_extension___cxx_range_for__ 1
#           define __macrodefs_extension_cxx_unrestricted_unions 1
#           define __macrodefs_extension_cxx___unrestricted_unions__ 1
#       endif
#       if GCC_PREREQ(40700)
#           define __macrodefs_extension_cxx_aggregate_nsdmi 1
#           define __macrodefs_extension_cxx___aggregate_nsdmi__ 1
#           define __macrodefs_extension_cxx_delegating_constructors 1
#           define __macrodefs_extension___cxx_delegating_constructors__ 1
#           define __macrodefs_extension_cxx_nonstatic_member_init 1
#           define __macrodefs_extension___cxx_nonstatic_member_init__ 1
#           define __macrodefs_extension_cxx_override_control 1
#           define __macrodefs_extension___cxx_override_control__ 1
#           define __macrodefs_extension_cxx_user_literals 1
#           define __macrodefs_extension___cxx_user_literals__ 1
#       endif
#       if GCC_PREREQ(40800)
#           define __macrodefs_extension_cxx_decltype_auto 1
#           define __macrodefs_extension___cxx_decltype_auto__ 1
#           define __macrodefs_extension_cxx_inheriting_constructors 1
#           define __macrodefs_extension___cxx_inheriting_constructors__ 1
#           define __macrodefs_extension_cxx_thread_local 1
#           define __macrodefs_extension___cxx_thread_local__ 1
#       endif
#       if GCC_PREREQ(40900)
#           define __macrodefs_extension_cxx_contextual_conversions 1
#           define __macrodefs_extension___cxx_contextual_conversions__ 1
#           define __macrodefs_extension_cxx_generic_lambdas 1
#           define __macrodefs_extension___cxx_generic_lambdas__ 1
#           define __macrodefs_extension_cxx_init_captures 1
#           define __macrodefs_extension___cxx_init_captures__ 1
#           define __macrodefs_extension_cxx_return_type_deduction 1
#           define __macrodefs_extension___cxx_return_type_deduction__ 1
#           ifndef __cpp_digit_separators
#               define __cpp_digit_separators 1
#           endif
#       endif
#       if GCC_PREREQ(50000)
#           define __macrodefs_extension_cxx_relaxed_constexpr 1
#           define __macrodefs_extension___cxx_relaxed_constexpr__ 1
#           define __macrodefs_extension_cxx_variable_templates 1
#           define __macrodefs_extension___cxx_variable_templates__ 1
#       endif
#       if GCC_PREREQ(60000)
#           define __macrodefs_extension_enumerator_attributes 1
#           define __macrodefs_extension___enumerator_attributes__ 1
#       endif
#   elif MSVC_PREREQ(1)
#       if MSVC_PREREQ(1600)
#           define __macrodefs_extension_cxx_auto_type 1
#           define __macrodefs_extension___cxx_auto_type__ 1
#           define __macrodefs_extension_cxx_decltype 1
#           define __macrodefs_extension___cxx_decltype__ 1
#           define __macrodefs_extension_cxx_lambdas 1
#           define __macrodefs_extension___cxx_lambdas__ 1
#           define __macrodefs_extension_cxx_nullptr 1
#           define __macrodefs_extension___cxx_nullptr__ 1
#           define __macrodefs_extension_cxx_rvalue_references 1
#           define __macrodefs_extension___cxx_rvalue_references__ 1
#           define __macrodefs_extension_cxx_static_assert 1
#           define __macrodefs_extension___cxx_static_assert__ 1
#           define __macrodefs_extension_cxx_trailing_return 1
#           define __macrodefs_extension___cxx_trailing_return__ 1
#       endif
#       if MSVC_PREREQ(1700)
#           define __macrodefs_extension_cxx_override_control 1
#           define __macrodefs_extension___cxx_override_control__ 1
#           define __macrodefs_extension_cxx_range_for 1
#           define __macrodefs_extension___cxx_range_for__ 1
#           define __macrodefs_extension_cxx_strong_enums 1
#           define __macrodefs_extension___cxx_strong_enums__ 1
#       endif
#       if MSVC_PREREQ(1800)
#           define __macrodefs_extension_cxx_aggregate_nsdmi 1
#           define __macrodefs_extension_cxx___aggregate_nsdmi__ 1
#           define __macrodefs_extension_cxx_contextual_conversions 1
#           define __macrodefs_extension___cxx_contextual_conversions__ 1
#           define __macrodefs_extension_cxx_default_function_template_args 1
#          define __macrodefs_extension___cxx_default_function_template_args__ 1
#           define __macrodefs_extension_cxx_delegating_constructors 1
#           define __macrodefs_extension___cxx_delegating_constructors__ 1
#           define __macrodefs_extension_cxx_deleted_functions 1
#           define __macrodefs_extension___cxx_deleted_functions__ 1
#           define __macrodefs_extension_cxx_explicit_conversions 1
#           define __macrodefs_extension___cxx_explicit_conversions__ 1
#           define __macrodefs_extension_cxx_generalized_initializers 1
#           define __macrodefs_extension___cxx_generalized_initializers__ 1
#           define __macrodefs_extension_cxx_nonstatic_member_init 1
#           define __macrodefs_extension___cxx_nonstatic_member_init__ 1
#           define __macrodefs_extension_cxx_raw_string_literals 1
#           define __macrodefs_extension___cxx_raw_string_literals__ 1
#           define __macrodefs_extension_cxx_variadic_templates 1
#           define __macrodefs_extension___cxx_variadic_templates__ 1
#       endif
#       if MSVC_PREREQ(1900)
#           define __macrodefs_extension_cxx_constexpr 1
#           define __macrodefs_extension___cxx_constexpr__ 1
#           define __macrodefs_extension_cxx_binary_literals 1
#           define __macrodefs_extension___cxx_binary_literals__ 1
#           define __macrodefs_extension_cxx_decltype_auto 1
#           define __macrodefs_extension___cxx_decltype_auto__ 1
#           define __macrodefs_extension_cxx_defaulted_functions 1
#           define __macrodefs_extension___cxx_defaulted_functions__ 1
#           define __macrodefs_extension_cxx_generic_lambdas 1
#           define __macrodefs_extension___cxx_generic_lambdas__ 1
#           define __macrodefs_extension_cxx_implicit_moves 1
#           define __macrodefs_extension___cxx_implicit_moves__ 1
#           define __macrodefs_extension_cxx_inheriting_constructors 1
#           define __macrodefs_extension___cxx_inheriting_constructors__ 1
#           define __macrodefs_extension_cxx_init_captures 1
#           define __macrodefs_extension___cxx_init_captures__ 1
#           define __macrodefs_extension_cxx_inline_namespaces 1
#           define __macrodefs_extension___cxx_inline_namespaces__ 1
#           define __macrodefs_extension_cxx_noexcept 1
#           define __macrodefs_extension___cxx_noexcept__ 1
#           define __macrodefs_extension_cxx_return_type_deduction 1
#           define __macrodefs_extension___cxx_return_type_deduction__ 1
#           define __macrodefs_extension_cxx_thread_local 1
#           define __macrodefs_extension___cxx_thread_local__ 1
#           define __macrodefs_extension_cxx_unicode_literals 1
#           define __macrodefs_extension___cxx_unicode_literals__ 1
#           define __macrodefs_extension_cxx_unrestricted_unions 1
#           define __macrodefs_extension_cxx___unrestricted_unions__ 1
#           define __macrodefs_extension_cxx_user_literals 1
#           define __macrodefs_extension___cxx_user_literals__ 1
#           if _MSC_FULL_VER >= 190023918
#               define __macrodefs_extension_cxx_variable_templates 1
#               define __macrodefs_extension___cxx_variable_templates__ 1
#           endif
#           ifndef __cpp_digit_separators
#               define __cpp_digit_separators 1
#           endif
#       endif
#       if MSVC_PREREQ(1910)
#           define __macrodefs_extension_cxx_relaxed_constexpr 1
#           define __macrodefs_extension___cxx_relaxed_constexpr__ 1
#       endif
#       if MSVC_PREREQ(1927)
#           define __macrodefs_extension_c_generic_selections 1
#           define __macrodefs_extension___c_generic_selections__ 1
#       endif
#       if MSVC_PREREQ(1928)
#           define __macrodefs_extension_c_static_assert 1
#           define __macrodefs_extension___c_static_assert__ 1
#           define __macrodefs_extension_modules 1
#           define __macrodefs_extension___modules__ 1
#       endif
#   endif
#   if (defined(_CPPUNWIND) && (_CPPUNWIND > 0)) || defined(__EXCEPTIONS)
#       define __macrodefs_extension_cxx_exceptions 1
#       define __macrodefs_extension___cxx_exceptions__ 1
#   endif
#   if (defined(_CPPRTTI) && (_CPPRTTI > 0)) || defined(__GXX_RTTI) \
        || defined(__RTTI__)
#       define __macrodefs_extension_cxx_rtti 1
#       define __macrodefs_extension___cxx_rtti__ 1
#   endif
#   ifndef __STDC_NO_ATOMICS__
#       define __macrodefs_extension_c_atomic 1
#       define __macrodefs_extension___c_atomic__ 1
#   endif
#   define __has_extension(x) ((__macrodefs_extension_ ##x) || __has_feature(x))
#endif
#ifndef __has_feature
#   define __has_feature(x) 0
#endif
#ifndef __has_include
#   define __has_include(x) 0
#endif
#ifndef __has_include_next
#   define __has_include_next(x) 0
#endif
#ifndef __has_warning
#   define __has_warning(x) 0
#endif
#ifndef __is_identifier
#   define __is_identifier(x) 0
#endif

/* == C++ FEATURE DETECTION MACROS ========================================== */

#if CPP_PREREQ(1L) && !(GCC_PREREQ(50000) || CLANG_PREREQ(30400) \
    || MSVC_PREREQ(1915)) && !defined(_FEATURE_TEST_MACROS_DEFINED)
#   define _FEATURE_TEST_MACROS_DEFINED 1
#   if __has_extension(cxx_aggregate_nsdmi)
#       define __cpp_aggregate_nsdmi 201304L
#   endif
#   if GCC_PREREQ(40700) || CLANG_PREREQ(30000) || MSVC_PREREQ(1800)
#       define __cpp_alias_templates 200704L
#   endif
#   if GCC_PREREQ(70000) || CLANG_PREREQ(40000) || MSVC_PREREQ(1912)
#       define __cpp_aligned_new 201606L
#   endif
#   if GCC_PREREQ(40800) || CLANG_PREREQ(30300) || MSVC_PREREQ(1900)
#       define __cpp_attributes 200809L
#   endif
#   if __has_extension(cxx_binary_literals)
#       define __cpp_binary_literals 201304L
#   endif
#   if GCC_PREREQ(70000) || CLANG_PREREQ(30900) || MSVC_PREREQ(1911)
#       define __cpp_capture_star_this 201603L
#   endif
#   if GCC_PREREQ(70000) || CLANG_PREREQ(50000) || MSVC_PREREQ(1911)
#       define __cpp_constexpr 201603L
#   elif __has_extension(cxx_relaxed_constexpr)
#       define __cpp_constexpr 201304L
#   elif __has_extension(cxx_constexpr)
#       define __cpp_constexpr 200704L
#   endif
#   if __has_extension(cxx_decltype)
#       define __cpp_decltype 200707L
#   endif
#   if __has_extension(cxx_decltype_auto)
#       define __cpp_decltype_auto 201304L
#   endif
#   if __has_extension(cxx_delegating_constructors)
#       define __cpp_delegating_constructors 200604L
#   endif
#   if GCC_PREREQ(60000) || CLANG_PREREQ(30600) || MSVC_PREREQ(1900)
#       define __cpp_enumerator_attributes 201411L
#       define __cpp_namespace_attributes 201411L
#   endif
#   if __has_extension(cxx_exceptions)
#       define __cpp_exceptions 199711L
#   endif
#   if GCC_PREREQ(60000) || CLANG_PREREQ(30600) || MSVC_PREREQ(1912)
#       define __cpp_fold_expressions 201603L
#   endif
#   if GCC_PREREQ(70000) || CLANG_PREREQ(40000) || MSVC_PREREQ(1914)
#       define __cpp_guaranteed_copy_elision 201606L
#   endif
#   if GCC_PREREQ(30000) || CLANG_PREREQ(1) || MSVC_PREREQ(1911)
#       define __cpp_hex_float 201603L
#   endif
#   if GCC_PREREQ(70000) || CLANG_PREREQ(30900) || MSVC_PREREQ(1911)
#       define __cpp_if_constexpr 201606L
#   endif
#   if __has_extension(cxx_inheriting_constructors)
#       define __cpp_inheriting_constructors 200802L
#   endif
#   if __has_extension(cxx_generalized_initializers)
#       define __cpp_initializer_lists 200806L
#   endif
#   if GCC_PREREQ(70000) || CLANG_PREREQ(30900) || MSVC_PREREQ(1912)
#       define __cpp_inline_variables 201606L
#   endif
#   if __has_extension(cxx_lambdas)
#       define __cpp_lambdas 200907L
#   endif
#   if GCC_PREREQ(70000) || CLANG_PREREQ(40000) || MSVC_PREREQ(1912)
#       define __cpp_noexcept_function_type 201510L
#   endif
#   if GCC_PREREQ(60000) || CLANG_PREREQ(30600) || MSVC_PREREQ(1912)
#       define __cpp_nontype_template_args 201411L
#   endif
#   if GCC_PREREQ(70000) || CLANG_PREREQ(40000) || MSVC_PREREQ(1914)
#       define __cpp_nontype_template_parameter_auto 201606L
#   endif
#   if __has_extension(cxx_nonstatic_member_init)
#       define __cpp_nsdmi 200809L
#   endif
#   if GCC_PREREQ(60000) || CLANG_PREREQ(30900) || MSVC_PREREQ(1910)
#       define __cpp_range_based_for 201603L
#   elif __has_extension(cxx_range_for)
#       define __cpp_range_based_for 200907L
#   endif
#   if __has_extension(cxx_raw_string_literals)
#       define __cpp_raw_strings 200710L
#   endif
#   if __has_extension(cxx_return_type_deduction)
#       define __cpp_return_type_deduction 201304L
#   endif
#   if __has_extension(cxx_rtti)
#       define __cpp_rtti 199711L
#   endif
#   if __has_extension(cxx_rvalue_references)
#       define __cpp_rvalue_references 200610L
#   endif
#   if GCC_PREREQ(50000) || CLANG_PREREQ(30400) || MSVC_PREREQ(1900)
#       define __cpp_sized_deallocation 201309L
#   endif
#   if GCC_PREREQ(60000) || CLANG_PREREQ(20500) || MSVC_PREREQ(1910)
#       define __cpp_static_assert 201411L
#   elif __has_extension(cxx_static_assert)
#       define __cpp_static_assert 200410L
#   endif
#   if GCC_PREREQ(70000) || CLANG_PREREQ(40000) || MSVC_PREREQ(1911)
#       define __cpp_structured_bindings 201606L
#   endif
#   if GCC_PREREQ(40400) || CLANG_PREREQ(20900) || MSVC_PREREQ(1900)
#       define __cpp_unicode_characters 200704L
#   endif
#   if __has_extension(cxx_unicode_literals)
#       define __cpp_unicode_literals 200710L
#   endif
#   if __has_extension(cxx_variable_templates)
#       define __cpp_variable_templates 201304L
#   endif
#   if __has_extension(cxx_variadic_templates)
#       define __cpp_variadic_templates 200704L
#   endif
#   if GCC_PREREQ(70000) || CLANG_PREREQ(40000) || MSVC_PREREQ(1914)
#       define __cpp_variadic_using 201611L
#   endif
#elif !defined(_FEATURE_TEST_MACROS_DEFINED)
#   define _FEATURE_TEST_MACROS_DEFINED 1
#endif

/* == DYNAMIC LIBRARY IMPORT/EXPORT ANNOTATIONS ============================= */

#ifndef EXPORT

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
#if (defined(_WIN32) || defined(__WINRT__) || defined(__OS2__) \
    || defined(__CYGWIN__)) && (__has_declspec_attribute(dllexport) \
    || __has_declspec_attribute(dllimport))
#   if (defined(_WIN32) || defined(__WINRT__) || defined(__OS2__) \
        || defined(__CYGWIN__)) && __has_declspec_attribute(dllexport)
#       define EXPORT __declspec(dllexport)
#   endif
#   if (defined(_WIN32) || defined(__WINRT__) || defined(__OS2__) \
        || defined(__CYGWIN__)) && __has_declspec_attribute(dllimport)
#       define IMPORT __declspec(dllimport)
#   endif
#   define LOCAL
#elif __has_attribute(visibility)
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

#endif

/* == CALLING CONVENTION SPECIFIERS ========================================= */

#ifndef CDECL

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
#           define CDECL __attribute__((__cdecl__))
#       endif
#       if __has_attribute(stdcall)
#           define STDCALL __attribute__((__stdcall__))
#       endif
#       if __has_attribute(fastcall)
#           define FASTCALL __attribute__((__fastcall__))
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

#endif

/* == PRAGMA DIRECTIVE ====================================================== */

#ifndef __pragma

/**
 * @def __pragma(dir)
 * @brief Microsoft-style pragma directive.
 * @details Due to the existence of __prgma, it's more easily made
 *          cross-platform than C99 _Pragma lul
 * 
 * @param[in] dir Compiler pragma directive to give.
 */
#if !MSVC_PREREQ(1) && !defined(__INTEL_COMPILER)
#   if (STDC_PREREQ(199901L) || CPP_PREREQ(201103L)) /* C99+/C++11+ _Pragma */
#       define __pragma(dir) _Pragma(#dir)
#   elif !MSVC_PREREQ(1500) /* MSVC 2008+ __pragma */
#       define __pragma(dir)
#   endif
#endif

#endif

/* == FUNCTION ATTRIBUTES =================================================== */

#ifndef ALLOCATOR

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
 * @def NO_EXCEPT
 * @brief Denotes that a function doesn't throw a C++ exception.
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
 * @def NOTNULL_PARAMS
 * @brief Denotes which function parameters are not allowed to be @c NULL in a
 *        function invocation.
 */
/**
 * @def CHECK_RESULT
 * @brief Denotes that a function's return value must be read after evaluation.
 */
/**
 * @def NOTNULL_RETURN
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
#   if GCC_PREREQ(110000) && !defined(__INTELLISENSE__)
#       define ALLOCATOR(deallocator) \
            __attribute__((__malloc__, __malloc__(deallocator)))
#   else
#       define ALLOCATOR(deallocator) __attribute__((__malloc__))
#   endif
#elif MSVC_PREREQ(1) || __has_declspec_attribute(allocator) \
    || __has_declspec_attribute(restrict)
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
#if (__has_c_attribute(deprecated) && STDC_PREREQ(201800L)) \
    || (__has_cpp_attribute(deprecated) && CPP_PREREQ(201103L))
#   define DEPRECATED(msg) [[deprecated(msg)]]
#elif __has_attribute(deprecated)
#   if __has_extension(attribute_deprecated_with_message)
#       define DEPRECATED(msg) __attribute__((__deprecated__(msg)))
#   else
#       define DEPRECATED(msg) __attribute__((__deprecated__))
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
#if CPP_PREREQ(201103L) || STDC_PREREQ(202000L)
#   define NO_RETURN [[noreturn]] /* C++11+/C23+ attribute noreturn */
#elif STDC_PREREQ(201112L)
#   define NO_RETURN _Noreturn /* C11+ _Noreturn */
#elif __has_attribute(noreturn)
#   define NO_RETURN __attribute__((__noreturn__))
#elif __has_declspec_attribute(noreturn) /* MSVC noreturn */
#   define NO_RETURN __declspec(noreturn)
#else
#   define NO_RETURN
#endif
#if (CPP_PREREQ(201103L) && __has_cpp_attribute(fallthrough)) \
    || (STDC_PREREQ(202000L) && __has_c_attribute(fallthrough))
#   define FALLTHROUGH [[fallthrough]]
#elif __has_attribute(fallthrough)
#   define FALLTHROUGH __attribute__((__fallthrough__))
#else
#   define FALLTHROUGH
#endif
#if __has_attribute(unavailable)
#   define UNAVAILABLE __attribute__((__unavailable__))
#elif (CPP_PREREQ(201103L) && __has_cpp_attribute(deprecated)) \
    || (STDC_PREREQ(202000L) && __has_c_attribute(deprecated))
#   define UNAVAILABLE [[deprecated]]
#elif __has_attribute(deprecated)
#   define UNAVAILABLE __attribute__((__deprecated__))
#else
#   define UNAVAILABLE
#endif
#if __has_c_attribute(unsequenced) /* C23 unsequenced */
#   define CONST_FUNC [[unsequenced]]
#elif __has_attribute(const) /* GCC 2.5+ const */
#   define CONST_FUNC __attribute__((__const__))
#else
#   define CONST_FUNC
#endif
#if __has_c_attribute(reproducible) /* C23 reproducible */
#   define PURE_FUNC [[reproducible]]
#elif __has_attribute(pure) /* GCC 2.95+ pure */
#   define PURE_FUNC __attribute__((__pure__))
#else
#   define PURE_FUNC
#endif
#if CPP_PREREQ(201103L)
#   define NO_EXCEPT noexcept
#elif CPP_PREREQ(1)
#   define NO_EXCEPT throw()
#else
#   define NO_EXCEPT
#endif
#if (__has_c_attribute(nodiscard) && STDC_PREREQ(201800L)) \
    || (__has_cpp_attribute(nodiscard) && CPP_PREREQ(201103L))
#   define CHECK_RESULT [[nodiscard]] /* C2x+ / C++17+ nodiscard */
#elif __has_attribute(warn_unused_result) /* GCC warn_unused_result */
#   define CHECK_RESULT __attribute__((__warn_unused_result__))
#elif MSVC_PREREQ(1400) || __has_include(<sal.h>) \
    && !defined(MACRODEFS_ONLY)  /* MSVC sal.h */
#   include <sal.h>
#   define _USE_SAL 1
#endif
#if __has_attribute(returns_nonnull)
#   define NOTNULL_RETURN __attribute__((__returns_nonnull__))
#endif
#if __has_attribute(nonnull)
#   define NOTNULL_PARAMS(params) __attribute__((__nonnull__ params))
#endif
#ifdef _USE_SAL
#   ifndef CHECK_RESULT
#       define CHECK_RESULT _Check_return_
#   endif
#   ifndef NOTNULL_RETURN
#       define NOTNULL_RETURN _Ret_notnull_
#   endif
#   undef _USE_SAL
#else
#   ifndef CHECK_RESULT
#       define CHECK_RESULT
#   endif
#   ifndef NOTNULL_RETURN
#       define NOTNULL_RETURN
#   endif
#   ifndef NOTNULL_PARAMS
#       define NOTNULL_PARAMS
#   endif
#endif
#if __has_attribute(format) /* GCC3 printf/scanf attrs */
#   define PRINTF_FUNC(fstr_index, arg_index) \
        __attribute__((__format__(__printf__, fstr_index, arg_index)))
#   define SCANF_FUNC(fstr_index, arg_index) \
        __attribute__((__format__(__scanf__, fstr_index, arg_index)))
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
#   if MSVC_PREREQ(1) || defined(__BORLANDC__) || defined(__DMC__) \
        || defined(__WATCOMC__) || defined(__LCC__) || defined(__CC_ARM)
#       define inline __inline /* MSVC __inline */
#   elif GCC_PREREQ(1) && __has_attribute(gnu_inline) /* GCC __inline__ */
#       define inline __inline__ __attribute__((__gnu_inline__))
#   elif GCC_PREREQ(1)
#       define inline __inline__
#   else /* set inline as static if unavailable */
#       define inline static
#       define _NO_INLINE
#   endif
#endif
#if MSVC_PREREQ(1200) /* MSVC __forceinline */
#   define force_inline __forceinline
#elif __has_attribute(always_inline) /* GCC always_inline */
#   if defined(__cplusplus) || !__has_attribute(gnu_inline)
#       define force_inline __inline__ __attribute__((__always_inline__))
#   else
#       define force_inline \
            __inline__ __attribute__((__always_inline__, __gnu_inline__))
#   endif
#else /* hope it gets inlined */
#   define force_inline inline
#endif
#if (MSVC_PREREQ(1) && defined(__EDG__) && !CPP_PREREQ(1L)) \
    || defined(_NO_INLINE) /* MSVC can't do static+inline... */
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
#   define no_inline __attribute__((__noinline__))
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
#if (CPP_PREREQ(201703L) && __has_cpp_attribute(maybe_unused)) \
    || (STDC_PREREQ(201800L) && __has_c_attribute(maybe_unused))
#   define MAYBE_UNUSED [[maybe_unused]] /* C++17/C2x+ maybe_unused */
#elif __has_attribute(unused) /* GCC unused */
#   define MAYBE_UNUSED __attribute__((__unused__))
#else
#   define MAYBE_UNUSED
#endif

/**
 * @def NULLABLE
 * @brief Denotes a nullable pointer parameter.
 */
/**
 * @def NONNULL
 * @brief Denotes a nullable pointer parameter.
 */
#ifdef __clang__
#   define NULLABLE _Nullable
#   define NOTNULL _Nonnull
#else
#   define NULLABLE
#   define NOTNULL
#endif

/**
 * @def ARRPARAM(name, specifiers, size)
 * @brief Denotes a pointer parameter should be taken as an array.
 * 
 * @param name       The name of the parameter
 * @param specifiers Pointer attributes & specifiers (e.g. NOTNULL, restrict)
 * @param size       Number of elements the array should contain. Can be blank.
 */
#if STDC_PREREQ(199901L)
#   define ARRPARAM(name, specifiers, size) name[specifiers size]
#else
#   define ARRPARAM(name, specifiers, size) *specifiers name
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
#   define LIKELY(cond)         (cond) [[likely]]
#   define UNLIKELY(cond)       (cond) [[unlikely]]
#   define LIKELY_LABEL(name)   [[likely]] name
#   define UNLIKELY_LABEL(name) [[unlikely]] name
#elif __has_builtin(__builtin_expect) /* GCC3+ expect */
#   define LIKELY(cond)         (__builtin_expect((cond), 1))
#   define UNLIKELY(cond)       (__builtin_expect((cond), 0))
#else
#   define LIKELY(cond)         (cond)
#   define UNLIKELY(cond)       (cond)
#endif
#ifndef LIKELY_LABEL
#   if __has_attribute(cold) && GCC_PREREQ(40800)
#       define LIKELY_LABEL(name)   name __attribute__((__cold__));
#       define UNLIKELY_LABEL(name) name __attribute__((__hot__));
#   else
#       define LIKELY_LABEL(name)   name
#       define UNLIKELY_LABEL(name) name
#   endif
#endif
#if __has_builtin(__builtin_unreachable) /* GCC4+ builtin unreachable */
#   define UNREACHABLE() __builtin_unreachable()
#elif MSVC_PREREQ(1) /* MSVC assume intrinsic */
#   define UNREACHABLE() __assume(0)
#elif CPP_PREREQ(1L) && !defined(MACRODEFS_ONLY)
#   include <cstdlib>
#   define UNREACHABLE() std::abort()
#elif __STDC_HOSTED__ && !defined(MACRODEFS_ONLY)
#   include <stdlib.h>
#   define UNREACHABLE() abort()
#elif !defined(MACRODEFS_ONLY)
#   define UNREACHABLE()
#endif

/* == RESTRICT KEYWORD ====================================================== */

/**
 * @def __restrict
 * @brief Hints that a pointer isn't aliased by another variable.
 */
#ifdef __restrict
#   undef __restrict
#endif
#if STDC_PREREQ(199901L)
#   define __restrict restrict
#elif GCC_PREREQ(1) || CLANG_PREREQ(1)
#   define __restrict __restrict__
#elif !defined(__CC_ARM)
#   define __restrict
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
#   elif !__has_extension(cxx_thread_local)
#       define _NO_THREAD_LOCAL 1
#   endif
#endif

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
#ifndef MACRODEFS_ONLY
#   if CPP_PREREQ(1L)
#       include <cstddef>
#   else
#       include <stddef.h>
#   endif
#endif
#ifndef offsetof
#   if __has_builtin(__builtin_offsetof)
#       define offsetof(type, field) __builtin_offsetof(type, field)
#   elif GCC_PREREQ(30400) && CPP_PREREQ(1L)
#       define offsetof(type, field) __offsetof__(reinterpret_cast<size_t>( \
            (&reinterpret_cast<char&>(static_cast<type*>(0)->field))))
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

#ifndef ALIGN_OF

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
#   define ALIGN_TO(size)   __attribute__((__aligned__(size)))
#   define ALIGN_TYPE(type) __attribute__((__aligned__(ALIGN_OF(type))))
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
#if STDC_PREREQ(201112L) && !STDC_PREREQ(202000L)
#   define __MACRODEFS_STATIC_ASSERT2 _Static_assert
#elif CPP_PREREQ(201103L) && !CPP_PREREQ(201703L)
#   define __MACRODEFS_STATIC_ASSERT2 static_assert
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
#if defined(DEBUG) && !defined(MACRODEFS_ONLY)
#   if CPP_PREREQ(1L)
    extern "C" {
#   endif
#       ifdef EXTERN_ASSERT_HANDLER
        extern
#       elif !defined(CUSTOM_ASSERT_HANDLER)
#       include <stdio.h>
#       include <stdlib.h>
        NO_RETURN static_force_inline
#       endif
        void __assert_handler(
            char const* cond,
            char const* file,
            int line
        )
#       if !defined(CUSTOM_ASSERT_HANDLER)
        {
#       if defined(_WIN32) && !defined(__WINRT__)
#       else
#       endif
            fprintf(
                stderr,
                "Assertion failed in %s@%d: \"%s\"\n",
                file, line, cond
            );
            exit(EXIT_FAILURE);
        }
#       else
        ;
#       endif
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

/* == DEBUG BREAKPOINTS ===================================================== */

#ifndef BREAKPOINT

#if __has_builtin(__builtin_debug_trap)
#   define BREAKPOINT() __builtin_debug_trap()
#elif MSVC_PREREQ(1000) && !defined(MACRODEFS_ONLY)
    extern void CDECL __debugbreak(void);
#   define BREAKPOINT() __debugbreak()
#elif GCC_PREREQ(1) && (defined(__i386__) || defined(__x86_64__))
#   define BREAKPOINT() __asm__ __volatile__ ( "int $3\n\t" )
#elif GCC_PREREQ(1) && defined(__APPLE__) && defined(__aarch64__)
#   define BREAKPOINT() __asm__ __volatile__ ( "brk #22\n\t" )
#elif GCC_PREREQ(1) && defined(__APPLE__) && defined(__arm__)
#   define BREAKPOINT() __asm__ __volatile__ ( "bkpt #22\n\t" )
#elif defined(__WATCOMC__) && defined(__i386__)
#   define BREAKPOINT() do { _asm { int 0x03} } while (0)
#elif !defined(__WATCOMC__) && __STDC_HOSTED__ && !defined(MACRODEFS_ONLY)
#   include <signal.h>
#   ifdef SIGTRAP
#       define BREAKPOINT() raise(SIGTRAP)
#   else
#       define BREAKPOINT()
#   endif
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
#if MSVC_PREREQ(1300) || (GCC_PREREQ(20000) && !GCC_PREREQ(30000))
#   define __func__ __FUNCTION__ /* MSVC 2002+ / GCC2 __FUNCTION__ */
#elif !GCC_PREREQ(30000) && !STDC_PREREQ(199901L) && !CPP_PREREQ(201103L)
#   ifndef __func__
#       define __func__ "???"
#   endif
#endif
#if MSVC_PREREQ(1300) /* MSVC 2002+ __FUNCSIG__ */
#   define __PRETTY_FUNCTION__ __FUNCSIG__
#elif !GCC_PREREQ(20000) /* GCC __PRETTY_FUNCTION__ */
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
#       ifdef MACRODEFS_ONLY
#           define bool uint8_t
#       else
            typedef uint8_t __macrodef_bool;
#           define bool  __macrodef_bool
#       endif
#       define false ((bool)0)
#       define true  ((bool)1)
#   endif
#endif

/* == ARCHITECTURE WORD SIZE ================================================ */

#if defined(__linux__) && !defined(MACRODEFS_ONLY)
#   include <asm/types.h>
#   define WORD_SIZE BITS_PER_LONG
#elif defined __WORDSIZE
#   define WORD_SIZE __WORDSIZE
#elif defined(__aarch64__) || defined(__x86_64__) || defined(__ia64__) \
    || defined(__powerpc64__) || (defined(__riscv_xlen) && (__riscv_xlen == 64))
#   define WORD_SIZE 64
#else
#   define WORD_SIZE 32
#endif

#endif
#ifndef MACRODEFS_ONLY

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
#if !MSVC_PREREQ(1300) || MSVC_PREREQ(1500) /* deprecated in MSVC2008 */
    /* __w64 informs that the pointer size changes on 64-bit machines */
#   define __w64
#endif
#if CPP_PREREQ(201103L) || (!STDC_PREREQ(1L) && __has_include(<cstdint>))
#   include <cstdint> /* don't import C++ header in C mode */
#   include <cinttypes>
#   define _SIZED_TYPES_INCLUDED 1
#elif STDC_PREREQ(199901L) || defined(__GNUC__) || defined(__SCO__) \
    || defined(__USLC__) || __has_include(<stdint.h>)
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
#   if MSVC_PREREQ(1) || defined(__WATCOM_INT64__) /* MSVC-style __int64 */ \
        || (defined(__BORLANDC__) && __BORLANDC__ > 0x460)
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
#   if defined(__LP64__) || defined(__lp64__)
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
#   elif defined(__MWERKS__) || defined(__SUNPRO_C) || defined(__SUNPRO_CC) \
        || defined(_LONG_LONG) /* C99-style long long */
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
#   if defined(UINT64_C) || defined(UINT64_MAX) || MSVC_PREREQ(1) \
        || STDC_PREREQ(199901L) /* detect 64-bit int support */
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
#   if defined(__arm__) || defined(__aarch64__) || defined(__powerpc__) \
        || defined(__powerpc64__) || defined(__mips__)
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
    typedef   int8_t   int_least8_t;
    typedef  uint8_t  uint_least8_t;
    typedef  int16_t  int_least16_t;
    typedef uint16_t uint_least16_t;
    typedef  int32_t  int_least32_t;
    typedef uint32_t uint_least32_t;
#   define PRIdLEAST8 PRId8
#   define PRIiLEAST8 PRIi8
#   define PRIoLEAST8 PRIo8
#   define PRIuLEAST8 PRIu8
#   define PRIxLEAST8 PRIx8
#   define PRIXLEAST8 PRIX8
#   define SCNdLEAST8 SCNd8
#   define SCNiLEAST8 SCNi8
#   define SCNoLEAST8 SCNo8
#   define SCNuLEAST8 SCNu8
#   define SCNxLEAST8 SCNx8
#   define SCNXLEAST8 SCNX8
#   define PRIdLEAST16 PRId16
#   define PRIiLEAST16 PRIi16
#   define PRIoLEAST16 PRIo16
#   define PRIuLEAST16 PRIu16
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
#   if (defined(_WIN64) || defined(__aarch64__) || defined(__powerpc64__) \
        || defined(__x86_64__) || defined(__ia64__)) && defined(_INT64_DEFINED)
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
        template <typename T, typename U>
        constexpr static_force_inline T __macrodefs_min(T a, U b) {
            return (a < static_cast<T>(b)) ? a : static_cast<T>(b);
        }

        template <typename T, typename U>
        constexpr static_force_inline T __macrodefs_max(T a, U b) {
            return (a > static_cast<T>(b)) ? a : static_cast<T>(b);
        }
#   if !CPP_PREREQ(201103L)
#       undef constexpr
#   endif
#   define MIN(a, b) __macrodefs_min(a, b)
#   define MAX(a, b) __macrodefs_max(a, b)
#elif GCC_PREREQ(1) /* GNU C minmax */
#   define MIN(a, b) __extension__ ({ \
        __typeof__(a) _a = (__typeof__(a))(a); \
        __typeof__(a) _b = (__typeof__(a))(b); \
        (_a < _b) ? _a : _b; \
    })
#   define MAX(a, b) __extension__ ({ \
        __typeof__(a) _a = (__typeof__(a))(a); \
        __typeof__(a) _b = (__typeof__(a))(b); \
        (_a > _b) ? _a : _b; \
    })
#elif STDC_PREREQ(201112L) /* C11+ minmax + C99+ fmin/fmax */
#   include <math.h>
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
        macro(unsigned long long int,   ull)
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
        float: fminf, \
        double: fmin, \
        long double: fminl, \
        default: __macrodefs_min_p \
    )((a), (b)))
#   define MAX(a, b) (_Generic((a), \
        __ENUMERATE_MINMAX_FUNCTIONS(__GENERATE_GENERICSEL_LABEL_MAX) \
        float: fmaxf, \
        double: fmax, \
        long double: fmaxl, \
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
#if __has_builtin(__builtin_bswap16) && __has_builtin(__builtin_bswap32)
#   define BSWAP16(x) __builtin_bswap16(x)
#   define BSWAP32(x) __builtin_bswap32(x)
#   if __has_builtin(__builtin_bswap64)
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
#elif defined(__OpenBSD__) || defined(__NetBSD__) || defined(__FreeBSD__) \
    || defined(__DragonFly__) /* BSD endian utils, but it has wack defines */
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
#       elif defined(__BIG_ENDIAN__) || defined(__ARMEB__) \
            || defined(__THUMBEB__) || defined(__AARCH64EB__) \
            || defined(_MIPSEB) || defined(__MIPSEB) || defined(__MIPSEB__)
#           define BYTE_ORDER   BIG_ENDIAN
#       elif defined(__LITTLE_ENDIAN__) || defined(__ARMEL__) \
            || defined(__THUMEL__) || defined(__AARCH64EL__) \
            || defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__) \
            || defined(_WIN32) || defined(__i386__) || defined(__x86_64__)
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

#endif /* !MACRODEFS_ONLY */

#endif /* MACRODEFS_H_ */
