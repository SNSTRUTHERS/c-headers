/**
 * @file thread.h
 * @author Simon Bolivar
 * @date 17 Jul 2022
 * 
 * @brief Standard C11 threading and POSIX semaphore compatible library.
 * 
 * @copyright LGPL-3.0
 */

#ifndef THREAD_H_
#define THREAD_H_

#include "macrodefs.h"

#if defined(__STDCPP_THREADS__) && (__STDCPP_THREADS__ == 0)
#   error "Cannot include thread.h in a single-threaded environment."
#endif

#ifndef THRD_API
#   ifdef THRD_FROM_DLL
#       define THRD_API extern IMPORT
#   elif defined THRD_BUILD_DLL
#       define THRD_API extern EXPORT
#   elif defined THRD_STATIC_INCLUDE
#       define THRD_API static
#   else
#       define THRD_API extern
#   endif
#endif
#ifndef THRD_CALL
#   define THRD_CALL CDECL
#endif

/* == TYPE DEFINES + INCLUDES =============================================== */

#include <limits.h>
#ifndef __STDC_NO_THREADS__
#   include <threads.h>
#endif
#if defined(__WINRT__) || defined(_WIN32) /* -- windows implementation ------ */
#   define NOATOM               1
#   define NOCOMM               1
#   define NOCRYPT              1
#   define NOGDI                1
#   define NOGDICAPMASKS        1
#   define NOIME                1
#   define NOKANJI              1
#   define NOMCX                1
#   define NOMETAFILE           1
#   define NOMSG                1
#   define NOOPENFILE           1
#   define NORASTEROPS          1
#   define NOSCROLL             1
#   define NOSERVICE            1
#   define NOSOUND              1
#   define NOSYSMETRICS         1
#   define NOTEXTMETRIC         1
#   define NOWH                 1
#   define WIN32_LEAN_AND_MEAN  1
#       include <windows.h>
#   undef WIN32_LEAN_AND_MEAN
#   undef NOWH
#   undef NOTEXTMETRIC
#   undef NOSYSMETRICS
#   undef NOSOUND
#   undef NOSERVICE
#   undef NOSCROLL
#   undef NORASTEROPS
#   undef NOOPENFILE
#   undef NOMSG
#   undef NOMETAFILE
#   undef NOMCX
#   undef NOKANJI
#   undef NOIME
#   undef NOGDICAPMASKS
#   undef NOGDI
#   undef NOCRYPT
#   undef NOCOMM
#   undef NOATOM

#   ifdef __STDC_NO_THREADS__
        enum thrd_result {
            thrd_success = 0,
            thrd_nomem = ERROR_OUTOFMEMORY,
            thrd_timedout = WAIT_TIMEOUT,
            thrd_busy = ERROR_BUSY,
            thrd_error = -1
        };

        enum mtx_flags {
            mtx_plain = 0,
            mtx_recursive = 1,
            mtx_timed = 2
        };

        struct timespec {
            time_t tv_sec;
            long tv_nsec;
        };

        typedef HANDLE thrd_t;
        typedef CRITICAL_SECTION mtx_t;
        typedef DWORD tss_t;
#       if !defined(__WINRT__) || (_WIN32_WINNT < 0x0600)
            typedef struct cnd_s {
                CRITICAL_SECTION lock;
                int wait, sigs;
                sem_t sem_wait, sem_done;
            } cnd_t;
#           define _NO_VISTA_CONDVAR 1
#       else
            typedef CONDITION_VARIABLE cnd_t;
#       endif
#   endif

    typedef union sem_u {
        HANDLE kern;
        LONG volatile atom;
    } sem_t;
#   define SEM_VALUE_MAX LONG_MAX

#   if defined(__WINRT__) || _WIN32_WINNT >= 0x0600
        typedef INIT_ONCE once_flag;
#       define ONCE_FLAG_INIT INIT_ONCE_STATIC_INIT
#   endif

#elif defined(__PSP__) || defined(__vita__) /* psp/vita implementation ------ */
#   include <sys/types.h>
#   include <sys/time.h>
#   ifdef __PSP__
#       include <pspkerneltypes.h>
#   else
#       include <psp2/types.h>
#   endif

#   ifdef __STDC_NO_THREADS__
#       ifdef __PSP__
#           include <pspkerror.h>
#           include <pspthreadman.h>
#       else
#           include <psp2/kernel/error.h>
#           include <psp2/kernel/threadmgr.h>
#       endif

        enum {
            thrd_success = 0,
            thrd_nomem = SCE_KERNEL_ERROR_NO_MEMORY,
            thrd_timedout = SCE_KERNEL_ERROR_WAIT_TIMEOUT,
            thrd_busy = SCE_KERNEL_ERROR_TIMER_BUSY,
            thrd_error = SCE_KERNEL_ERROR_ERROR
        };

        enum {
            mtx_plain = 0,
            mtx_recursive = SCE_KERNEL_MUTEX_ATTR_RECURSIVE,
            mtx_timed = 0
        };

        struct timespec {
            time_t tv_sec;
            long tv_nsec;
        };

        typedef SceUID thrd_t;
        typedef SceLwMutexWorkarea mtx_t;

#       define _NO_COND_DEFINITION 1
#       define _NO_TSS_DEFINITION 1
#   endif

    typedef SceUID sem_t;
#   define SEM_VALUE_MAX (INT_MAX / 2)

#elif defined(__unix__) || defined(__MACOSX__) /* -- pthread implementation - */

#   include <errno.h>
#   include <pthread.h>

#   ifdef __STDC_NO_THREADS__
        enum {
            thrd_success = 0,
            thrd_nomem = ENOMEM,
            thrd_timedout = ETIMEDOUT,
            thrd_busy = EBUSY,
            thrd_error = -1
        };

        enum {
            mtx_plain = 0,
            mtx_recursive = 1,
            mtx_timed = 2
        };

        typedef pthread_t thrd_t;
        typedef pthread_mutex_t mtx_t;
        typedef pthread_cond_t cnd_t;
        typedef pthread_key_t tss_t;
        typedef pthread_once_t once_flag;
#       define ONCE_FLAG_INIT PTHREAD_ONCE_INIT
#   endif

#   if defined(__APPLE__) && defined(__MACH__)
#       include <mach/semaphore.h>
#       include <sys/sysctl.h>

        typedef struct {
            semaphore_t sem;
            int val;
        } sem_t;
#       define SEM_VALUE_MAX INT_MAX
#   elif !defined(__APPLE__) && !defined(__MVS__)
#       include <semaphore.h>
#       define _POSIX_SEMAPHORE_IMPL 1
#   endif

#else /* -- unsupported operating system ------------------------------------ */
#   error "Unsupported operating system"
    ]]]]}[[}]]_
#endif /* ------------------------------------------------------------------- */

#if !defined(SEM_VALUE_MAX) && defined(_NO_COND_DEFINITION)
#   error "Missing sem_t and missing cond_t definitions are mutually exclusive."
    ]]]]}[[}]]_
#endif

#ifndef SEM_VALUE_MAX
    typedef struct sem_s {
        int count, wait;
        mtx_t lock;
        cnd_t cond;
    } sem_t;
#   define SEM_VALUE_MAX INT_MAX
#   define _NO_SEM_DEFINITION 1
#endif
#if !defined(ONCE_FLAG_INIT)
#   include "atomics.h"
    typedef atomic_flag once_flag;
#   define ONCE_FLAG_INIT ATOMIC_FLAG_INIT
#   define _NO_CALLONCE_DEFINITION 1
#endif
#if defined(_NO_COND_DEFINITION) && defined(__STDC_NO_THREADS__)
    typedef struct cnd_s {
        mtx_t lock;
        int wait, sigs;
        sem_t sem_wait, sem_done;
    } cnd_t;
#endif
#if defined(_NO_TSS_DEFINITION) && defined(__STDC_NO_THREADS__)
    typedef uint_fast32_t tss_t;
#endif

/* == API =================================================================== */

#ifdef __STDC_NO_THREADS__
    typedef int (*thrd_start_t)(void*);
    typedef void (*tss_dtor_t)(void*);

    THRD_API int THRD_CALL thrd_create(
        thrd_t* thread_out,
        thrd_start_t func,
        void* arg
    ) NO_EXCEPT;
    THRD_API int THRD_CALL thrd_equal(thrd_t a, thrd_t b) NO_EXCEPT;
        thrd_t THRD_CALL thrd_current(void) NO_EXCEPT;
    THRD_API int THRD_CALL thrd_sleep(
        struct timespec const* duration,
        struct timespec* remaining
    ) NO_EXCEPT;
    THRD_API void THRD_CALL thrd_yield(void) NO_EXCEPT;
    THRD_API NO_RETURN void THRD_CALL thrd_exit(int result) NO_EXCEPT;
    THRD_API int THRD_CALL thrd_detach(thrd_t thread) NO_EXCEPT;
    THRD_API int THRD_CALL thrd_join(
        thrd_t thread,
        int* result_out
    ) NO_EXCEPT;

    THRD_API int THRD_CALL mtx_init(mtx_t* mutex, int type) NO_EXCEPT;
    THRD_API void THRD_CALL mtx_destroy(mtx_t* mutex) NO_EXCEPT;
    THRD_API int THRD_CALL mtx_lock(mtx_t* mutex) NO_EXCEPT;
    THRD_API int THRD_CALL mtx_unlock(mtx_t* mutex) NO_EXCEPT;
    THRD_API int THRD_CALL mtx_timedlock(
        mtx_t *__restrict mutex,
        struct timespec const *__restrict duration
    ) NO_EXCEPT;

    THRD_API int THRD_CALL cnd_init(cnd_t* cond) NO_EXCEPT;
    THRD_API void THRD_CALL cnd_destroy(cnd_t* cond) NO_EXCEPT;
    THRD_API int THRD_CALL cnd_signal(cnd_t* cond) NO_EXCEPT;
    THRD_API int THRD_CALL cnd_broadcast(cnd_t* cond) NO_EXCEPT;
    THRD_API int THRD_CALL cnd_wait(cnd_t* cond, mtx_t* mutex) NO_EXCEPT;
    THRD_API int THRD_CALL cnd_timedwait(
        cnd_t *__restrict cond,
        mtx_t *__restrict mutex,
        struct timespec const *__restrict duration
    ) NO_EXCEPT;

    THRD_API int THRD_CALL tss_create(
        tss_t* key_out,
        tss_dtor_t destructor
    ) NO_EXCEPT;
    THRD_API void* THRD_CALL tss_get(tss_t key) NO_EXCEPT;
    THRD_API int THRD_CALL tss_set(tss_t key, void* value) NO_EXCEPT;
    THRD_API void THRD_CALL tss_delete(tss_t key) NO_EXCEPT;

    THRD_API void THRD_CALL call_once(
        once_flag* flag,
        void (*func)(void)
    ) NO_EXCEPT;
#endif

#ifndef _POSIX_SEMAPHORE_IMPL
    THRD_API int THRD_CALL sem_init(
        sem_t* sem,
        int shared,
        unsigned value
    ) NO_EXCEPT;
    THRD_API int THRD_CALL sem_destroy(sem_t* sem) NO_EXCEPT;
    THRD_API int THRD_CALL sem_post(sem_t* sem) NO_EXCEPT;
    THRD_API int THRD_CALL sem_wait(sem_t* sem) NO_EXCEPT;
    THRD_API int THRD_CALL sem_trywait(sem_t* sem) NO_EXCEPT;
    THRD_API int THRD_CALL sem_timedwait(
        sem_t *__restrict sem,
        struct timespec const *__restrict duration
    ) NO_EXCEPT;
    THRD_API int THRD_CALL sem_getvalue(
        sem_t *__restrict sem,
        int *__restrict result_out
    ) NO_EXCEPT;
#endif

#if !defined(_POSIX_SEMAPHORE_IMPL) || !defined(__SOLARIS__)
    THRD_API int THRD_CALL sem_reltimedwait_np(
        sem_t *__restrict sem,
        struct timespec const *__restrict duration
    ) NO_EXCEPT;
#endif

THRD_API int THRD_CALL mtx_reltimedlock_np(
    mtx_t *__restrict mtx,
    struct timespec const *__restrict duration
) NO_EXCEPT;
THRD_API int THRD_CALL cnd_reltimedwait_np(
    mtx_t *__restrict mtx,
    struct timespec const *__restrict duration
) NO_EXCEPT;
THRD_API unsigned THRD_CALL thrd_hardware_concurrency(void);

/* == IMPLEMENTATION ======================================================== */

#ifdef THREAD_IMPLEMENTATION

#ifdef _NO_TSS_DEFINITION
    static void __tss_thrd_exit(void);
#endif

#if defined(__WINRT__) || defined(_WIN32)
    static struct timespec _get_time(void) {
        struct timespec ts;
        union {
            FILETIME ft;
            uint64_t u64;
        } time;

        GetSystemTimeAsFileTime(&time.ft);
        time.u64 *= 100;
        time.u64 -= UINT64_C(11644473600000000000);

        ts.tv_sec = time.u64 / 1000000000;
        ts.tv_nsec = time.u64 % 1000000000;
        return ts;
    }
#else
#   ifdef __MVS__
#       include <sys/time.h>
#   endif

    static struct timespec _get_time(void) {
#   ifdef __MVS__
        union {
            struct timeval tv;
            struct timespec ts;
        } time;
        gettimeofday(&time.tv, NULL);
        time.ts *= 1000;
        return time.ts;
#   else
        struct timespec time;
        clock_gettime(CLOCK_REALTIME, &time);
        return time;
#   endif
    }
#endif

#if defined(__WINRT__) || defined(_WIN32) /* -- windows implementation ------ */
#   include <stdlib.h>
#   include <string.h>
#   include <time.h>
#   define __TIMESPEC_TO_MS(ts) ( \
        ((ts)->tv_sec * 1000u) + ((ts)->tv_nsec / 1000000) \
    )
#   define _NO_MTX_TIMEDLOCK 1
#   define _NO_MTX_RELTIMEDLOCK 1

#   ifdef __STDC_NO_THREADS__

    typedef struct __tss_dtor_entry {
        tss_t key;
        tss_dtor_t dtor;
    } __tss_dtor_entry;
    static __tss_dtor_entry __tss_dtor_table[64];

    static DWORD WINAPI __thrd_start(void* arg) {
        struct {
            thrd_start_t func;
            void* ptr;
        } params;
        __tss_dtor_entry* entry;
        int code;

        memcpy(&params, arg, sizeof params);
        free(arg);

        code = (*params.func)(params.ptr);

        for (entry = __tss_dtor_table;
            entry != __tss_dtor_table + ARRAY_LENGTH(__tss_dtor_table);
            entry++
        ) {
            if (entry->dtor) {
                void* value = TlsGetValue(entry->key);
                if (value)
                    (*entry->dtor)(value);
            }
        }

        return (DWORD)code;
    }

    int thrd_create(
        thrd_t* thread_out,
        thrd_start_t func,
        void* arg
    ) {
        if (!thread_out || !func) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_error;
        } else {
            struct {
                thrd_start_t func;
                void* ptr;
            }* thrd_params;
            HANDLE thread;

            if (!(thrd_params = malloc(sizeof *thrd_params))) {
                return thrd_nomem;
            } else {
                thrd_params->func = func;
                thrd_params->ptr = arg;
            }

            if (!(thread = CreateThread(
                    NULL, 0, __thrd_start, thrd_params, 0, NULL
            ))) {
                free(thrd_params);
                return (GetLastError() == ERROR_OUTOFMEMORY) ?
                    thrd_nomem :
                    thrd_error
                ;
            } else {
                *thread_out = thread;
                return thrd_success;
            }
        }
    }

    int thrd_equal(thrd_t a, thrd_t b) {
        return a == b;
    }

    thrd_t thrd_current(void) {
        return GetCurrentThread();
    }

    int thrd_sleep(
        struct timespec const* duration,
        struct timespec* remaining
    ) {
        if (!duration ||
            duration->tv_sec < 0 ||
            duration->tv_nsec < 0 ||
            duration->tv_nsec >= 1000000000
        ) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return -ERROR_INVALID_PARAMETER;
        } else {
            FILETIME start, end;
            uint64_t want;
            ULARGE_INTEGER real, total;
            uint32_t msecs;

            if (remaining)
                GetSystemTimeAsFileTime(&start);

            want = total.QuadPart = (
                duration->tv_sec * 1000 +
                duration->tv_nsec / 1000000
            );
            while (total.QuadPart) {
                msecs = (uint32_t)MIN(UINT64_C(4294967294), total.QuadPart);
                total.QuadPart -= msecs;

                Sleep(__TIMESPEC_TO_MS(duration));
            }

            if (remaining) {
                GetSystemTimeAsFileTime(&end);
                real.HighPart = start.dwHighDateTime;
                real.LowPart = start.dwLowDateTime;
                total.HighPart = end.dwHighDateTime;
                total.LowPart = end.dwLowDateTime;

                real.QuadPart = (total.QuadPart - real.QuadPart) / 10000;
                total.QuadPart =
                    (real.QuadPart < want) * (want - real.QuadPart)
                ;

                remaining->tv_sec = total.QuadPart / 1000;
                remaining->tv_nsec = (uint32_t)(total.QuadPart % 1000) * 1000000;

                if (total.QuadPart)
                    return thrd_error;
            }

            return thrd_success;
        }
    }

    void thrd_yield(void) {
        SwitchToThread();
    }

    NO_RETURN void thrd_exit(int result) {
        __tss_dtor_entry* entry;
        for (entry = __tss_dtor_table;
            entry != __tss_dtor_table + ARRAY_LENGTH(__tss_dtor_table);
            entry++
        ) {
            if (entry->dtor) {
                void* value = TlsGetValue(entry->key);
                if (value)
                    (*entry->dtor)(value);
            }
        }

        ExitThread((DWORD)result);
    }

    int thrd_detach(thrd_t thread) {
        if (!thread) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_error;
        } else if (!CloseHandle(thread)) {
            return thrd_error;
        } else {
            return thrd_success;
        }
    }

    int thrd_join(thrd_t thread, int* result_out) {
        if (thread) {
            DWORD result = WaitForSingleObject(thread, INFINITE);
            if (result != WAIT_OBJECT_0) {
                return thrd_error;
            } else if (result_out) {
                if (!GetExitCodeThread(thread, &result)) {
                    CloseHandle(thread);
                    return thrd_error;
                }

                *result_out = (int)result;
            }

            CloseHandle(thread);
            return thrd_success;
        } else {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_error;
        }
    }

    int mtx_init(mtx_t* mutex, int type) {
        (void)type;

        if (!mutex) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_error;
        } else {
            return InitializeCriticalSectionAndSpinCount(mutex, 16384) ?
                thrd_success :
                thrd_error
            ;
        }
    }

    int mtx_lock(mtx_t* mutex) {
        if (!mutex) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_error;
        } else {
            EnterCriticalSection(mutex);
            return thrd_success;
        }
    }

    int mtx_trylock(mtx_t* mutex) {
        if (!mutex) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_error;
        } else {
            return TryEnterCriticalSection(mutex) ? thrd_success : thrd_error;
        }
    }

    int mtx_unlock(mtx_t* mutex) {
        if (!mutex) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_error;
        } else {
            LeaveCriticalSection(mutex);
            return thrd_success;
        }
    }

    void mtx_destroy(mtx_t* mutex) {
        if (mutex)
            DeleteCriticalSection(mutex);
    }

    typedef void (WINAPI* PFN_InitializeConditionVariable)(
        cnd_t* cond
    );
    static PFN_InitializeConditionVariable InitializeConditionVariable;

    typedef void (WINAPI* PFN_WakeConditionVariable)(
        cnd_t* cond
    );
    static PFN_WakeConditionVariable WakeConditionVariable;

    typedef void (WINAPI* PFN_WakeAllConditionVariable)(
        cnd_t* cond
    );
    static PFN_WakeAllConditionVariable WakeAllConditionVariable;

    typedef BOOL (WINAPI* PFN_SleepConditionVariableCS)(
        cnd_t* cond,
        mtx_t* mutex,
        DWORD millisecs
    );
    static PFN_SleepConditionVariableCS SleepConditionVariableCS;

    int cnd_init(cnd_t* cond) {
        if (!cond) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_error;
        } else {
#   ifdef _NO_VISTA_CONDVAR
            if (!InitializeConditionVariable) {
                HMODULE kernel32 = GetModuleHandleA("kernel32.dll");
                if (kernel32) {
                    InitializeConditionVariable = __extension__
                        (PFN_InitializeConditionVariable)GetProcAddress(
                            kernel32, "InitializeConditionVariable"
                    );
                    WakeConditionVariable = __extension__
                        (PFN_WakeConditionVariable)GetProcAddress(
                            kernel32, "WakeConditionVariable"
                    );
                    WakeAllConditionVariable = __extension__
                        (PFN_WakeAllConditionVariable)GetProcAddress(
                            kernel32, "WakeAllConditionVariable"
                    );
                    SleepConditionVariableCS = __extension__
                        (PFN_SleepConditionVariableCS)GetProcAddress(
                            kernel32, "SleepConditionVariableCS"
                    );

                    if (!InitializeConditionVariable ||
                        !WakeConditionVariable ||
                        !WakeAllConditionVariable ||
                        !SleepConditionVariableCS
                    ) {
                        InitializeConditionVariable = __extension__ NULL;
                        WakeConditionVariable = __extension__ NULL;
                        WakeAllConditionVariable = __extension__ NULL;
                        SleepConditionVariableCS = __extension__ NULL;
                    }
                }
            }

            if (!InitializeConditionVariable) {
                if (mtx_init(&cond->lock, mtx_plain) != thrd_success) {
                    goto mtx_lock_fail;
                } else if (sem_init(&cond->sem_wait, 0, 0) != thrd_success) {
                    goto sem_wait_fail;
                } else if (sem_init(&cond->sem_done, 0, 0) != thrd_success) {
                    goto sem_done_fail;
                }

                cond->wait = 0;
                cond->sigs = 0;

                return thrd_success;

            sem_done_fail:
                sem_destroy(&cond->sem_wait);
            sem_wait_fail:
                mtx_destroy(&cond->lock);
            mtx_lock_fail:
                return thrd_error;
            }
#   endif
            InitializeConditionVariable(cond);
            return thrd_success;
        }
    }

    int cnd_signal(cnd_t* cond) {
        if (!cond) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_error;
        } else
#   ifdef _NO_VISTA_CONDVAR
        if (!WakeConditionVariable) {
            mtx_lock(&cond->lock);

            if (cond->wait > cond->sigs) {
                cond->sigs++;
                sem_post(&cond->sem_wait);
                mtx_unlock(&cond->lock);
                sem_wait(&cond->sem_done);
            } else {
                mtx_unlock(&cond->lock);
            }
        } else
#   endif
        {
            WakeConditionVariable(cond);
        }

        return thrd_success;
    }

    int cnd_broadcast(cnd_t* cond) {
        if (!cond) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_error;
        } else
#   ifdef _NO_VISTA_CONDVAR
        if (!WakeAllConditionVariable) {
            mtx_lock(&cond->lock);

            if (cond->wait > cond->sigs) {
                int i;
                const int waiting = cond->wait - cond->sigs;

                cond->sigs = cond->wait;
                for (i = 0; i < waiting; i++) {
                    if (sem_post(&cond->sem_wait) == thrd_error)
                        return thrd_error;
                }

                mtx_unlock(&cond->lock);
                for (i = 0; i < waiting; i++)
                    sem_wait(&cond->sem_done);
            } else {
                mtx_unlock(&cond->lock);
            }
        } else
#   endif
        {
            WakeAllConditionVariable(cond);
        }

        return thrd_success;
    }

    int cnd_timedwait(
        cnd_t *__restrict cond,
        mtx_t *__restrict mutex,
        struct timespec const *__restrict duration
    ) {
        if (!cond || !mutex || !duration ||
            duration->tv_sec < 0 ||
            duration->tv_nsec < 0 ||
            duration->tv_nsec >= 1000000000
        ) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_error;
        } else {
            struct timespec current = _get_time();
            if ((current.tv_sec -= duration->tv_sec) < 0) {
                current.tv_sec = current.tv_nsec = 0;
            } else if ((current.tv_nsec -= duration->tv_nsec) < 0) {
                if (current.tv_sec) {
                    current.tv_nsec += 1000000000;
                    current.tv_sec--;
                } else {
                    current.tv_nsec = 0;
                }
            }

            return cnd_reltimedwait_np(cond, mutex, &rel);
        }
    }

    int cnd_reltimedwait_np(
        cnd_t *__restrict cond,
        mtx_t *__restrict mutex,
        struct timespec const *__restrict duration
    ) {
        if (!cond || !mutex || (duration && (
                duration->tv_sec < 0 ||
                duration->tv_nsec < 0 ||
                duration->tv_nsec >= 1000000000
        ))) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_error;
        } else {
            DWORD msecs = duration ? __TIMESPEC_TO_MS(duration) : INFINITE;

#       ifdef _NO_VISTA_CONDVAR
            if (!SleepConditionVariableCS) {
                int result;

                mtx_lock(&cond->lock);
                cond->wait++;
                mtx_unlock(&cond->lock);

                mtx_unlock(mutex);
                result = sem_reltimedwait_np(&cond->sem_wait, duration);

                mtx_lock(&cond->lock);
                if (cond->sigs) {
                    if (!result)
                        sem_wait(&cond->sem_wait);

                    sem_post(&cond->sem_done);
                    cond->sigs--;
                }

                cond->wait--;
                mtx_unlock(&cond->lock);
                mtx_lock(mutex);
                return result;
            } else
#   endif
            {
                return SleepConditionVariableCS(cond, mutex, msecs) ?
                    thrd_success :
                    thrd_error
                ;
            }
        }
    }

    int cnd_wait(cnd_t* cond, mtx_t* mutex) {
        return cnd_reltimedwait_np(cond, mutex, NULL);
    }

    void cnd_destroy(cnd_t* cond) {
#   ifdef _NO_VISTA_CONDVAR
        if (!WakeConditionVariable && cond) {
            sem_destroy(&cond->sem_done);
            sem_destroy(&cond->sem_wait);
            mtx_destroy(&cond->lock);
        }
#   else
        (void)cond;
#   endif
    }

    int tss_create(tss_t* key_out, tss_dtor_t destructor) {
        __tss_dtor_entry* entry;
        tss_t key;

        if (!key_out) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_error;
        } else if ((key = TlsAlloc()) == UINT32_C(0xffffffff)) {
            return thrd_error;
        } else if (destructor) {
            __tss_dtor_entry* entry;
            for (entry = __tss_dtor_table;
                entry != __tss_dtor_table + ARRAY_LENGTH(__tss_dtor_table)
                    && !entry->dtor;
                entry++
            );

            if (entry == __tss_dtor_table + ARRAY_LENGTH(__tss_dtor_table)) {
                return thrd_error;
            } else {
                entry->key = key;
                entry->dtor = destructor;
            }
        }

        *key_out = key;
        return thrd_success;
    }

    void* tss_get(tss_t key) {
        return TlsGetValue(key);
    }

    int tss_set(tss_t key, void* value) {
        return TlsSetValue(key, value) ? thrd_success : thrd_error;
    }

    void tss_delete(tss_t key) {
        TlsFree(key);
    }

#   ifndef _NO_CALLONCE_DEFINITION

    static BOOL CALLBACK __call_once_enter(
        PINIT_ONCE flag,
        PVOID param,
        PVOID* ctx
    ) {
        void (*func)(void) = __extension__((void(*)(void)))(param);
        (void)flag; (void)ctx;

        func();
        return TRUE;
    }

    void call_once(once_flag* flag, void (*func)(void)) {
        InitOnceExecuteOnce(flag, __call_once_enter, NULL, NULL);
    }

#   endif

#   endif

#   ifdef _NO_WIN8_SEMATOMS
    typedef BOOL (WINAPI* PFN_WaitOnAddress)(
        void volatile* addr,
        void* cmpaddr,
        SIZE_T addr_size,
        DWORD millisecs
    );
    static PFN_WaitOnAddress WaitOnAddress;

    typedef void (WINAPI* PFN_WakeByAddressSingle)(
        void* addr
    );
    static PFN_WakeByAddressSingle WakeByAddressSingle;
#   endif

    int sem_init(sem_t* sem, int shared, unsigned int value) {
        if (!sem || value > SEM_VALUE_MAX) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_error;
        } else
#   ifdef _NO_WIN8_SEMATOMS
        if (!WaitOnAddress) {
            HMODULE synch120 = GetModuleHandleA(
                "api-ms-core-synch-l1-2.0.dll"
            );

            if (synch120) {
                WaitOnAddress = __extension__
                    (PFN_WaitOnAddress)GetProcAddress(
                        synch120, "WaitOnAddress"
                );
                WakeByAddressSingle = __extension__
                    (PFN_WakeByAddressSingle)GetProcAddress(
                        synch120, "WakeByAddressSingle"
                );

                if (!WaitOnAddress || !WakeByAddressSingle) {
                    WaitOnAddress = __extension__ NULL;
                    WakeByAddressSingle = __extension__ NULL;
                }
            }
        }

        if (!WaitOnAddress) {
            sem->kern = CreateSemaphoreW(
                NULL, (LONG)value, SEM_VALUE_MAX, NULL
            );
            return sem->kern ? thrd_success : -1;
        } else
#   endif
        {
            sem->atom = (LONG)value;
            return thrd_success;
        }
    }

    int sem_destroy(sem_t* sem) {
        if (!sem) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_error;
        } else
#   ifdef _NO_WIN8_SEMATOMS
        if (!WaitOnAddress && !CloseHandle(sem)) {
            return thrd_error;
        } else
#   endif
        {
            return thrd_success;
        }
    }

    int sem_trywait(sem_t* sem) {
        if (!sem) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_success;
        } else
#   ifdef _NO_WIN8_SEMATOMS
        if (!WaitOnAddress) {
            return WaitForSingleObject(
                sem->kern, 0
            ) == WAIT_OBJECT_0 ? thrd_success : thrd_error;
        } else
#   endif
        {
            LONG c = sem->atom;
            return (
                !c ||
                InterlockedCompareExchange(
                    &sem->atom, c - 1, c
            )) ? thrd_success : thrd_error;
        }
    }

    int sem_reltimedwait_np(
        sem_t *__restrict sem,
        struct timespec const *__restrict duration
    ) {
        if (!sem || (duration &&
                duration->tv_sec < 0 ||
                duration->tv_nsec < 0 ||
                duration->tv_nsec >= 1000000000
        )) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_success;
        } else {
            DWORD msecs = duration ? __TIMESPEC_TO_MS(duration) : INFINITE;

#   ifdef _NO_WIN8_SEMATOMS
            if (!WaitOnAddress) {
                return WaitForSingleObject(
                    sem->kern, msecs
                ) == WAIT_OBJECT_0 ? thrd_success : thrd_error;
            } else
#   endif
            {
                LONG c;

                do {
                    c = sem->atom;
                    while (!c) {
                        if (!WaitOnAddress(
                            &sem->atom, &c, sizeof sem->atom, msecs
                        )) {
                            return GetLastError() == ERROR_TIMEDOUT ?
                                thrd_timedout :
                                thrd_error;
                        } else {
                            c = sem->atom;
                        }
                    }
                } while (InterlockedCompareExchange(&sem->atom, c - 1, c) != c);
                return thrd_success;
            }
        }
    }

    int sem_timedwait(
        sem_t *__restrict sem,
        struct timespec const *__restrict duration
    ) {
        union {
            uint64_t nsx100;
            FILETIME filetime;
        } current_time;
        uint64_t duration_filetime;
        struct timespec relative_time;

        if (!duration ||
            duration->tv_sec < 0 ||
            duration->tv_nsec < 0 ||
            duration->tv_nsec >= 1000000000
        ) {
            errno = EINVAL;
            return thrd_error;
        }

        GetSystemTimeAsFileTime(&current_time.filetime);
        duration_filetime = (UINT64_C(11644473600) + duration->tv_sec)
            * UINT64_C(10000000)
            + duration->tv_nsec / 100;
        duration_filetime -= current_time.filetime;

        relative_time.tv_sec = (time_t)(duration_filetime / UINT64_C(10000000));
        relative_time.tv_nsec = (time_t)(duration_filetime % UINT64_C(10000000)) * 100;
        return sem_reltimedwait_np(sem, &relative_time);
    }

    int sem_wait(sem_t* sem) {
        return sem_reltimedwait_np(sem, NULL);
    }

    int sem_post(sem_t* sem) {
        if (!sem) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_error;
        } else
#   ifdef _NO_WIN8_SEMATOMS
        if (!WakeByAddressSingle) {
            return ReleaseSemaphore(sem->kern, 1, NULL) ?
                thrd_success :
                thrd_error
            ;
        } else
#   endif
        if (sem->atom == SEM_VALUE_MAX) {
            SetLastError(ERROR_ARITHMETIC_OVERFLOW);
            return thrd_error;
        } else {
            InterlockedIncrement(&sem->atom);
            WakeByAddressSingle(&sem->atom);
            return (GetLastError() == NO_ERROR) ? thrd_success : thrd_error;
        }
    }

    int sem_getvalue(
        sem_t *__restrict sem,
        int *__restrict result_out
    ) {
        typedef DWORD (NTAPI* PFN_NtQuerySemaphore)(
            HANDLE sem,
            DWORD info_class,
            PVOID sem_info,
            ULONG sem_info_size,
            PULONG return_length
        );
        typedef DWORD (NTAPI* PFN_RtlNtStatusToDosError)(
            DWORD ntstatus
        );
        typedef struct _SEMAPHORE_BASIC_INFORMATION {
            ULONG current, max;
        } SEMAPHORE_BASIC_INFORMATION;

        if (!sem) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_error;
        } else
#   ifdef _NO_WIN8_SEMATOMS
        if (!WaitOnAddress) {
            static PFN_NtQuerySemaphore NtQuerySemaphore;
            static PFN_RtlNtStatusToDosError RtlNtStatusToDosError;

            SEMAPHORE_BASIC_INFORMATION basic_info;
            LONG status;

            if (!RtlNtStatusToDosError) {
                HMODULE ntdll = GetModuleHandleA("ntdll.dll");
                if (!ntdll)
                    return thrd_error;

                RtlNtStatusToDosError = __extension__
                    (PFN_RtlNtStatusToDosError)GetProcAddress(
                        ntdll, "RtlNtStatusToDosError"
                );
                NtQuerySemaphore = __extension__
                    (PFN_NtQuerySemaphore)GetProcAddress(
                        ntdll, "NtQuerySemaphore"
                );

                if (!NtQuerySemaphore || !RtlNtStatusToDosError)
                    return thrd_error;
            }

            if ((status = (*NtQuerySemaphore)(
                    sem, 0, &basic_info, sizeof basic_info, NULL
            )) == ERROR_SUCCESS) {
                if (result_out)
                    *result_out = (int)basic_info.current;
                return thrd_success;
            } else {
                SetLastError((*RtlNtStatusToDosError)(status));
                return thrd_error;
            }
        } else
#   endif
        {
            *result_out = (int)sem->atom;
            return thrd_success;
        }
    }

#elif defined(__PSP__) || defined(__vita__) /* psp/vita implementation ------ */
#   if defined(__PSP__)
#       include <stdlib.h>
#   endif
#   ifndef SCE_KERNEL_ERROR_MUTEX_FAILED_TO_OWN
#       define SCE_KERNEL_ERROR_MUTEX_FAILED_TO_OWN 0x80028145
#   endif
#   ifndef SCE_KERNEL_MUTEX_ATTR_RECURSIVE
#       define SCE_KERNEL_MUTEX_ATTR_RECURSIVE 0x0200u
#   endif

#   ifdef __STDC_NO_THREADS__

    typedef struct {
        thrd_start_t f;
        void* a;
    } __thrd_entry_t;

    static int __thrd_entry(SceSize size, void* argp) {
        __thrd_entry_t args;
        (void)size;

        args = *(__thrd_entry_t*)argp;
        free(argp);
        return (*args->f)(args->a);
    }

    int thrd_create(
        thrd_t* thread_out,
        thrd_start_t func,
        void* arg
    ) {
        SceKernelThreadInfo thrd_status;
        thrd_t thrd;
        __thrd_entry_t* args;
#   ifdef __vita__
#       define priority 0
#   else
        int priority;
#       define VITA_THREAD_STACK_SIZE_DEFAULT 0x8000
#   endif
        char thrd_name[] = "stdc.thrd";

        if (!thread_out || !func) {
            return thrd_error;
        } else if (!(args = (__thrd_entry_t*)malloc(sizeof *args))) {
            return thrd_nomem;
        }

#   ifdef __PSP__
        priority = 32;
        if (!sceKernelReferThreadStatus(sceKernelGetThreadId(), &status)) {
            priority = status.currentPriority;
        }
#   endif

        thrd_name[MAX(32, sizeof thrd_name) - 1] = '\0';
        if ((thrd = sceKernelCreateThread(
            thrd_name,
            __thrd_entry,
            priority,
            VITA_THREAD_STACK_SIZE_DEFAULT,
#       ifdef __PSP__
            PSP_THREAD_ATTR_VFPU,
#       else
#           undef priority
            0, 0,
#       endif
            NULL
        )) < 0) {
            free(args);
            return thrd_error;
        }

        args->f = func;
        args->a = arg;
        sceKernelStartThread(
            thrd,
            (SceSize)(sizeof *args / sizeof(SceUInt)), (void*)args
        );

        *thread_out = thrd;
        return thrd_success;
    }

    int thrd_equal(thrd_t a, thrd_t b) {
        return a == b;
    }

    thrd_t thrd_current(void) {
        return sceKernelGetThreadId();
    }

    int thrd_sleep(
        struct timespec const* duration,
        struct timespec* remaining
    ) {
        const SceUInt max_delay = 0xfffffffful / 1000;
        struct timeval start, end;
        SceUInt delay;

        if (!duration ||
            duration->tv_sec < 0 ||
            duration->tv_nsec < 0 ||
            duration->tv_nsec >= 1000000000
        ) {
            return thrd_error;
        }

        delay = duration->tv_sec * 1000000;
        if (delay < duration->tv_sec || delay > max_delay) {
            delay = max_delay;
        } else if (delay + duration->tv_nsec / 1000 > max_delay) {
            delay = max_delay;
        } else {
            delay += duration->tv_nsec / 1000;
        }

        if (remaining) {
            gettimeofday(&start, NULL);
        }

        sceKernelDelayThreadCB(delay);
        if (remaining) {
            gettimeofday(&end, NULL);
            remaining->tv_sec = end.tv_sec - start.tv_sec;
            remaining->tv_nsec = (end.tv_usec - start.tv_usec) * 1000;
        }

        return (result == -1 && errno != EINTR) ? -errno : result;
    }

    void thrd_yield(void) {
        sceKernelDelayThreadCB(0);
    }

    void thrd_exit(int result) {
        __tss_thrd_exit();
        sceKernelExitThread(result);
    }

    int thrd_detach(thrd_t thread) {
        return sceKernelDeleteThread(thread) < 0 ? thrd_error : thrd_success;
    }

    int thrd_join(thrd_t thread, int* result_out) {
        if (sceKernelWaitThreadEnd(thread, NULL) < 0) {
            return thrd_error;
        } else if (result_out) {
            *result_out = sceKernelGetThreadExitStatus(thread);
        }

        sceKernelDeleteThread(thread);
        return thrd_success;
    }

    int mtx_init(mtx_t* mutex, int type) {
        if (!mutex) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_error;
        }

        return sceKernelCreateLwMutex(
            &mutex,
            "stdc.mtx",
            type,
            0, NULL
        ) < 0 ? thrd_error : thrd_success;
    }

    int mtx_lock(mtx_t* mutex) {
        return (!mutex || sceKernelLockLwMutex(mutex, 1, NULL) < 0) ?
            thrd_error :
            thrd_success;
    }

    int mtx_trylock(mtx_t* mutex) {
        if (!mutex) {
            return thrd_error;
        } else switch (sceKernelTryLockLwMutex(mutex, 1)) {
        case SCE_KERNEL_OK:
            return thrd_success;
        case SCE_KERNEL_ERROR_MUTEX_FAILED_TO_OWN:
        case SCE_KERNEL_ERROR_WAIT_TIMEOUT:
            return thrd_timedout;
        default:
            return thrd_error;
        }
    }

    int mtx_timedlock(
        mtx_t *__restrict,
        struct timespec const *__restrict duration
    ) {
        if (!mutex ||
            !duration ||
            duration->tv_sec < 0 ||
            duration->tv_nsec < 0 ||
            duration->tv_nsec >= 1000000000
        ) {
            return thrd_error;
        } else {
            struct timespec current = _get_time();
            if ((current.tv_sec -= duration->tv_sec) < 0) {
                return mtx_trylock(mutex);
            } else if ((current.tv_nsec -= duration->tv_nsec) < 0) {
                current.tv_nsec += 1000000000;
                if (!current.tv_sec--)
                    return mtx_trylock(mutex);
            }

            return mtx_reltimedlock_np(mutex, &current);
        }
    }

    int mtx_reltimedlock_np(
        mtx_t *__restrict mutex,
        struct timespec const *__restrict duration
    ) {
        SceUInt timeout;

        if (!mutex || (duration && (
            duration->tv_sec < 0 ||
            duration->tv_nsec < 0 ||
            duration->tv_nsec >= 1000000000
        ))) {
            return thrd_error;
        }

        timeout = ((duration->tv_sec * 1000000) + (duration->tv_nsec / 1000));
        switch (sceKernelLockLwMutex(mutex, 1, &timeout)) {
        case SCE_KERNEL_ERROR_OK:
            return thrd_success;
        case SCE_KERNEL_ERROR_WAIT_TIMEOUT:
            return thrd_timedout;
        default:
            return thrd_error;
        }
    }

    int mtx_unlock(mtx_t* mutex) {
        return (!mutex || sceKernelUnlockLwMutex(mutex, 1) < 0) ?
            thrd_error :
            thrd_success;
    }

    void mtx_destroy(mtx_t* mutex) {
        if (mutex)
            sceKernelDeleteLwMutex(mutex);
    }

#   endif

    int sem_init(sem_t* sem, int shared, unsigned int value) {
        sem_t result;
        (void)shared;

        if (!sem || value > SEM_VALUE_MAX) {
            errno = EINVAL;
            return thrd_error;
        }

        if ((result = sceKernelCreateSema(
                "stdc.sem", 0, value, SEM_VALUE_MAX, NULL
        )) < 0) {
            return thrd_error;
        }

        *sem = result;
        return thrd_success;
    }

    int sem_destroy(sem_t* sem) {
        return (!sem || sceKernelDeleteSema(*sem) < 0) ?
            thrd_error :
            thrd_success;
    }

    int sem_getvalue(
        sem_t *__restrict sem,
        int *__restrict result_out
    ) {
        SceKernelSemaInfo info;
#   ifdef __vita__
#       define sceKernelReferSemaStatus sceKernelGetSemaInfo
        info.size = sizeof info;
#   endif

        if (!sem || (result = sceKernelReferSemaStatus(*sem, &info)) < 0) {
            return thrd_error;
        }

        if (result_out) result_out = info.currentCount;
        return thrd_success;

#   ifdef sceKernelReferSemaStatus
#       undef sceKernelReferSemaStatus
#   endif
    }

    int sem_timedwait(
        sem_t *__restrict sem,
        struct timespec const *__restrict duration
    ) {
        int timeout;

        if (!sem ||
            !duration ||
            duration->tv_sec < 0 ||
            duration->tv_nsec < 0 ||
            duration->tv_nsec >= 1000000000
        ) {
            return thrd_error;
        }

        timeout = ((duration->tv_sec * 1000000) + (duration->tv_nsec / 1000));
        switch (sceKernelWaitSema(*sem, 1, &timeout)) {
        case SCE_KERNEL_ERROR_OK:
            return thrd_success;
        case SCE_KERNEL_ERROR_WAIT_TIMEOUT:
            return thrd_timedout;
        default:
            return thrd_error;
        }
    }

    int sem_wait(sem_t* sem) {
        return (!sem || sceKernelWaitSema(*sem, 1, NULL) < 0) ?
            thrd_error :
            thrd_success;
    }

    int sem_trywait(sem_t* sem) {
        return (!sem || sceKernelPollSema(*sem, 1) < 0) ?
            thrd_error :
            thrd_success;
    }

    int sem_post(sem_t* sem) {
        return (!sem || sceKernelSignalSema(*sem, 1) < 0) ?
            thrd_error :
            thrd_success;
    }

#else /* -- pthread implementation ------------------------------------------ */
#   include <sched.h>
#   include <sys/types.h>
#   include <sys/time.h>
#   include <time.h>
#   include <unistd.h>

#   ifdef __STDC_NO_THREADS__

    int thrd_create(
        thrd_t* thread_out,
        thrd_start_t func,
        void* arg
    ) {
        return pthread_create(
            thread_out,
            0,
            __extension__ (void*(*)(void*))func,
            arg
        ) ? thrd_error : thrd_success;
    }

    int thrd_equal(thrd_t a, thrd_t b) {
        return pthread_equal(a, b);
    }

    thrd_t thrd_current(void) {
        return pthread_self();
    }

    int thrd_sleep(
        struct timespec const* duration,
        struct timespec* remaining
    ) {
        int result = nanosleep(duration, remaining);
        return (result == -1 && errno != EINTR) ? errno : result;
    }

    void thrd_yield(void) {
        sched_yield();
    }

    void thrd_exit(int result) {
        pthread_exit((void*)(intptr_t)result);
    }

    int thrd_detach(thrd_t thread) {
        return pthread_detach(thread) ? thrd_error : thrd_success;
    }

    int thrd_join(thrd_t thread, int* result_out) {
        void* result;

        if (pthread_join(thread, &result) != 0) {
            return thrd_error;
        } else if (result_out) {
            *result_out = (int)(intptr_t)result;
        }

        return thrd_success;
    }

    int mtx_init(mtx_t* mutex, int type) {
        int result;
        pthread_mutexattr_t attr;

        pthread_mutexattr_init(&attr);

        if (type & mtx_timed) {
#           ifdef PTHREAD_MUTEX_TIMED_NP
                pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_TIMED_NP);
#           elif defined(PTHREAD_MUTEX_TIMED)
                pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_TIMED);
#           endif
        }
        if (type & mtx_recursive) {
#           ifdef PTHREAD_MUTEX_RECURSIVE_NP
                pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
#           elif defined(PTHREAD_MUTEX_RECURSIVE)
                pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
#           endif
        }

        result = pthread_mutex_init(mutex, &attr) ?
            thrd_error :
            thrd_success;

        pthread_mutexattr_destroy(&attr);
        return result;
    }

    int mtx_lock(mtx_t* mutex) {
        return pthread_mutex_lock(mutex) ? thrd_error : thrd_success;
    }

#   if !defined(__CYGWIN__) && !defined(__MACOSX__)
        int mtx_timedlock(
            mtx_t *__restrict mutex,
            struct timespec const *__restrict duration
        ) {
            switch (pthread_mutex_timedlock(mutex, duration)) {
            case ETIMEDOUT:
                return thrd_timedout;
            case 0:
                return thrd_success;
            default:
                return thrd_error;
            }
        }
#   else
#       define _NO_MTX_TIMEDLOCK 1
#   endif
#   ifdef __SOLARIS__
        int mtx_reltimedlock_np(
            mtx_t *__restrict mutex,
            struct timespec const *__restrict duration
        ) {
            switch (pthread_mutex_reltimedlock_np(mutex, duration)) {
            case ETIMEDOUT:
                return thrd_timedout;
            case 0:
                return thrd_success;
            default:
                return thrd_error;
            }
        }
#   else
#       define _NO_MTX_RELTIMEDLOCK 1
#   endif

    int mtx_trylock(mtx_t* mutex) {
        switch (pthread_mutex_trylock(mutex)) {
        case EBUSY:
            return thrd_busy;
        case 0:
            return thrd_success;
        default:
            return thrd_error;
        }
    }

    int mtx_unlock(mtx_t* mutex) {
        return pthread_mutex_unlock(mutex) ? thrd_error : thrd_success;
    }

    void mtx_destroy(mtx_t* mutex) {
        pthread_mutex_destroy(mutex);
    }

    int cnd_init(cnd_t* cond) {
        return pthread_cond_init(cond, NULL) ? thrd_error : thrd_success;
    }

    int cnd_signal(cnd_t* cond) {
        return pthread_cond_signal(cond) ? thrd_error : thrd_success;
    }

    int cnd_broadcast(cnd_t* cond) {
        return pthread_cond_broadcast(cond) ? thrd_error : thrd_success;
    }

    int cnd_wait(cnd_t* cond, mtx_t* mutex) {
        return pthread_cond_wait(cond, mutex) ? thrd_error : thrd_success;
    }

    int cnd_reltimedwait_np(
        cnd_t *__restrict cond,
        mtx_t *__restrict mutex,
        struct timespec const *__restrict duration
    ) {
#   if defined(__APPLE__) && defined(__MACH__)
        return pthread_cond_timedwait_relative_np(cond, mutex, duration);
#   elif defined(__SOLARIS__)
        return pthread_cond_reltimedwait_np(cond, mutex, duration);
#   else
        if (duration && (
            duration->tv_sec < 0 ||
            duration->tv_nsec < 0 ||
            duration->tv_nsec >= 1000000000
        )) {
            return thrd_error;
        } else if (!duration) {
            return cnd_wait(cond, mutex);
        } else {
            struct timespec absolute_time = _get_time();
            absolute_time.tv_sec += duration->tv_sec;
            if ((absolute_time.tv_nsec += duration->tv_nsec) >= 1000000000) {
                absolute_time.tv_nsec -= 1000000000;
                absolute_time.tv_sec++;
            }

            return cnd_timedwait(cond, mutex, &absolute_time);
        }
#   endif
    }

    int cnd_timedwait(
        cnd_t *__restrict cond,
        mtx_t *__restrict mutex,
        struct timespec const *__restrict duration
    ) {
        int result;

        do {
            result = pthread_cond_timedwait(cond, mutex, &absolute_time);
        } while (result == EINTR);

        errno = result;
        switch (result) {
        case 0:
            return thrd_success;
        case ETIMEDOUT:
            return thrd_timedout;
        default:
            return thrd_error;
        }
    }

    void cnd_destroy(cnd_t* cond) {
        pthread_cond_destroy(cond);
    }

    int tss_create(tss_t* key, tss_dtor_t destructor) {
        return pthread_key_create(key, destructor) ? thrd_error : thrd_success;
    }

    void* tss_get(tss_t key) {
        return pthread_getspecific(key);
    }

    int tss_set(tss_t key, void* value) {
        return pthread_setspecific(key, value) ? thrd_error : thrd_success;
    }

    void tss_delete(tss_t key) {
        pthread_key_delete(key);
    }

    void call_once(once_flag* flag, void (*func)(void)) {
        pthread_once(flag, func);
    }

#   endif

#   if defined(__APPLE__) && defined(__MACH__)
#       include <mach/mach_init.h>
#       include <mach/semaphore.h>
#       include <mach/task.h>
#       ifndef SEM_NAME_LEN
#           define SEM_NAME_LEN 48
#       endif
#       define SEM_VALUE_MAX INT_MAX

        typedef struct {
            semaphore_t sem;
            int val;
        } sem_t;

        int sem_init(
            sem_t* sem, int shared, unsigned int value
        ) {
            (void)shared;

            switch (semaphore_create(
                mach_task_self(), &sem->sem, SYNC_POLICY_FIFO, (int)value
            )) {
            case KERN_SUCCESS:
                sem->val = 0;
                return thrd_success;
            case KERN_RESOURCE_SHORTAGE:
                errno = ENOMEM;
                return thrd_error;
            default:
                errno = EINVAL;
                return thrd_error;
            }
        }

        int sem_destroy(sem_t* sem) {
            return (!sem || semaphore_destroy(mach_task_self(), sem->sem)) ?
                thrd_error :
                thrd_success;
        }

        int sem_getvalue(
            sem_t *__restrict sem,
            int *__restrict val
        ) {
            if (sem) {
                if (val) *val = sem->val;
                return thrd_success;
            }

            errno = EINVAL;
            return thrd_error;
        }

        int sem_trywait(sem_t* sem) {
            mach_timespec_t ts = { 0, 0 };

            if (!sem) {
                errno = EINVAL;
                return thrd_error;
            }

            switch (semaphore_timedwait(sem->sem, ts)) {
            case KERN_SUCCESS:
                return thrd_success;
            case KERN_OPERATION_TIMED_OUT:
                errno = EAGAIN;
                return thrd_error;
            default:
                errno = EINVAL;
                return thrd_error;
            }
        }

        int sem_reltimedwait_np(
            sem_t *__restrict sem,
            struct timespec const *__restrict duration
        ) {
            mach_timespec_t ts;

            if (!sem || (duration &&
                    duration->tv_sec < 0 ||
                    duration->tv_nsec < 0 ||
                    duration->tv_nsec >= 1000000000
            )) {
                errno = EINVAL;
                return thrd_error;
            } else if (!duration) {
                return sem_wait(sem);
            }

            ts.tv_sec = (unsigned int)duration->tv_sec;
            ts.tv_nsec = (clock_res_t)duration->tv_nsec;

            switch (semaphore_timedwait(sem->sem, ts)) {
            case KERN_SUCCESS:
                return thrd_success;
            case KERN_OPERATION_TIMED_OUT:
                errno = ETIMEDOUT;
                return thrd_error;
            default:
                errno = EINVAL;
                return thrd_error;
            }
        }

        int sem_timedwait(
            sem_t *__restrict sem,
            struct timespec const *__restrict duration
        ) {
            struct timespec relative_time;

            if (!duration ||
                duration->tv_sec < 0 ||
                duration->tv_nsec < 0 ||
                duration->tv_nsec >= 1000000000
            ) {
                errno = EINVAL;
                return thrd_error;
            }

            relative_time = _get_time();
            relative_time.tv_nsec -= duration->tv_nsec;
            relative_time.tv_sec -= duration->tv_sec;
            if (relative_time.tv_nsec < 0) {
                relative_time.tv_nsec += 1000000000;
                relative_time.tv_sec -= 1;
            }
            return sem_reltimedwait_np(sem, &relative_time);
        }

        int sem_wait(sem_t* sem) {
            int err;

            if (!sem) {
                errno = EINVAL;
                return thrd_error;
            }

            if (sem->val) sem->val--;
            do {
                err = semaphore_wait(sem->sem);
            } while ((err = KERN_ABORTED));

            if (err) {
                errno = EINVAL;
                return thrd_error;
            }

            return thrd_success;
        }

        int sem_post(sem_t* sem) {
            if (!sem || semaphore_signal(sem->sem)) {
                errno = EINVAL;
                return thrd_error;
            }

            sem->val++;
            sem_reltimedwait_np;
            return thrd_success;
        }
#   elif defined(__APPLE__) || defined(__MVS__)
#   elif !defined(__SOLARIS__)
        int sem_reltimedwait_np(
            sem_t *__restrict sem,
            struct timespec const *__restrict duration
        ) {
            struct timespec absolute_time;

            if (duration && (
                duration->tv_sec < 0 ||
                duration->tv_nsec < 0 ||
                duration->tv_nsec >= 1000000000
            )) {
                return thrd_error;
            } else if (!duration) {
                return sem_wait(sem);
            }

            absolute_time = _get_time();
            absolute_time.tv_sec += duration->tv_sec +
                (absolute_time.tv_nsec + duration->tv_nsec) / 1000000000;
            absolute_time.tv_nsec += duration->tv_nsec;
            absolute_time.tv_nsec %= 1000000000;

            return sem_timedwait(sem, &absolute_time);
        }
#   endif

#endif

/* ---- mutex locking ------------------------------------------------------- */

#ifndef __STDC_NO_THREADS__
#   define _NO_MTX_RELTIMEDLOCK 1
#endif

#ifdef _NO_MTX_TIMEDLOCK
#   undef _NO_MTX_TIMEDLOCK

    int mtx_timedlock(
        mtx_t *__restrict mutex,
        struct timespec const *__restrict duration
    ) {
        if (!duration ||
            duration->tv_sec < 0 ||
            duration->tv_nsec < 0 ||
            duration->tv_nsec >= 1000000000
        )) {
            return thrd_error;
        } else while (mtx_trylock(mutex) != thrd_success) {
            struct timespec now = _get_time();
            if (duration->tv_sec < now.tv_sec ||
                duration->tv_nsec < now.tv_nsec
            )
                return thrd_timedout;

            thrd_yield();
        }

        return thrd_success;
    }
#endif

#ifdef _NO_MTX_RELTIMEDLOCK
#   undef _NO_MTX_RELTIMEDLOCK

    int mtx_reltimedlock_np(
        mtx_t *__restrict mutex,
        struct timespec const *__restrict duration
    ) {
        if (duration && (
            duration->tv_sec < 0 ||
            duration->tv_nsec < 0 ||
            duration->tv_nsec >= 1000000000
        )) {
            return thrd_error;
        } else if (!duration) {
            return mtx_lock(cond, mutex);
        } else {
            struct timespec absolute_time = _get_time();
            absolute_time.tv_sec += duration->tv_sec;
            if ((absolute_time.tv_nsec += duration->tv_nsec) >= 1000000000) {
                absolute_time.tv_nsec -= 1000000000;
                absolute_time.tv_sec++;
            }

            return mtx_timedlock(mutex, &absolute_time);
        }
    }
#endif

/* -- condition variables --------------------------------------------------- */

#ifdef _NO_COND_DEFINITION

    int cnd_init(cnd_t* cond) {
        if (mtx_init(&cond->lock, mtx_plain) != thrd_success) {
            goto mtx_lock_fail;
        } else if (sem_init(&cond->sem_wait, 0, 0) != thrd_success) {
            goto sem_wait_fail;
        } else if (sem_init(&cond->sem_done, 0, 0) != thrd_success) {
            goto sem_done_fail;
        }

        cond->wait = 0;
        cond->sigs = 0;

        return thrd_success;

    sem_done_fail:
        sem_destroy(&cond->sem_wait);
    sem_wait_fail:
        mtx_destroy(&cond->lock);
    mtx_lock_fail:
        return thrd_error;
    }

    int cnd_signal(cnd_t* cond) {
        mtx_lock(&cond->lock);

        if (cond->wait > cond->sigs) {
            cond->sigs++;
            sem_post(&cond->sem_wait);
            mtx_unlock(&cond->lock);
            sem_wait(&cond->sem_done);
        } else {
            mtx_unlock(&cond->lock);
        }

        return thrd_success;
    }

    int cnd_broadcast(cnd_t* cond) {
        mtx_lock(&cond->lock);

        if (cond->wait > cond->sigs) {
            int i;
            const int waiting = cond->wait - cond->sigs;

            cond->sigs = cond->wait;
            for (i = 0; i < waiting; i++) {
                if (sem_post(&cond->sem_wait) == thrd_error)
                    return thrd_error;
            }

            mtx_unlock(&cond->lock);
            for (i = 0; i < waiting; i++)
                sem_wait(&cond->sem_done);
        } else {
            mtx_unlock(&cond->lock);
        }

        return thrd_success;
    }

    int cnd_timedwait(
        cnd_t *__restrict cond,
        mtx_t *__restrict mutex,
        struct timespec const *__restrict duration
    ) {
        int result;

        mtx_lock(&cond->lock);
        cond->wait++;
        mtx_unlock(&cond->lock);

        mtx_unlock(mutex);
        result = sem_timedwait(&cond->sem_wait, duration);

        mtx_lock(&cond->lock);
        if (cond->sigs) {
            if (!result)
                sem_wait(&cond->sem_wait);

            sem_post(&cond->sem_done);
            cond->sigs--;
        }

        cond->wait--;
        mtx_unlock(&cond->lock);
        mtx_lock(mutex);
        return result;
    }

    int cnd_reltimedwait_np(
        cnd_t *__restrict cond,
        mtx_t *__restrict mutex,
        struct timespec const *__restrict duration
    ) {
        int result;

        mtx_lock(&cond->lock);
        cond->wait++;
        mtx_unlock(&cond->lock);

        mtx_unlock(mutex);
        result = sem_reltimedwait_np(&cond->sem_wait, duration);

        mtx_lock(&cond->lock);
        if (cond->sigs) {
            if (!result)
                sem_wait(&cond->sem_wait);

            sem_post(&cond->sem_done);
            cond->sigs--;
        }

        cond->wait--;
        mtx_unlock(&cond->lock);
        mtx_lock(mutex);
        return result;
    }

    int cnd_wait(cnd_t* cond, mtx_t* mutex) {
        return cnd_reltimedwait_np(cond, mutex, NULL);
    }

    void cnd_destroy(cnd_t* cond) {
        sem_destroy(&cond->sem_done);
        sem_destroy(&cond->sem_wait);
        mtx_destroy(&cond->lock);
    }

#endif

/* -- semaphores ------------------------------------------------------------ */

#ifdef _NO_SEM_DEFINITION

    int sem_init(sem_t* sem, int shared, unsigned int value) {
        if (!sem || value > SEM_VALUE_MAX) {
            errno = EINVAL;
            return thrd_error;
        } else {
            sem->count = (int)value;
            sem->wait = 0;

            if (mtx_init(&sem->lock, mtx_plain) != thrd_success) {
                goto mtx_lock_fail;
            } else if (cnd_init(&sem->cond) != thrd_success) {
                goto cnd_cond_fail;
            } else {
                return thrd_success;
            }

        cnd_cond_fail:
            mtx_destroy(&sem->lock);
        mtx_lock_fail:
            return thrd_error;
        }
    }

    int sem_destroy(sem_t* sem) {
        if (!sem) {
            errno = EINVAL;
            return thrd_error;
        } else while (sem->wait) {
            cnd_broadcast(&sem->cond);
            thrd_yield();
        }

        cnd_destroy(&sem->cond);
        mtx_destroy(&sem->lock);
    }

    int sem_reltimedwait_np(
        sem_t *__restrict sem,
        struct timespec const *__restrict duration
    ) {
        if (!sem) {
            errno = EINVAL;
            return thrd_error;
        } else if (mtx_lock(&sem->lock) == thrd_error) {
            return thrd_error;
        } else if (!sem->count && cnd_reltimedwait_np(
            &sem->cond, &sem->lock, duration
        ) != thrd_success) {
            mtx_unlock(&sem->lock);
            return thrd_error;
        } else if (sem->count) {
            sem->count--;
        }

        return mtx_unlock(&sem->lock);
    }

    int sem_timedwait(
        sem_t *__restrict sem,
        struct timespec const *__restrict duration
    ) {
        if (!sem) {
            errno = EINVAL;
            return thrd_error;
        } else if (mtx_lock(&sem->lock) == thrd_error) {
            return thrd_error;
        } else if (!sem->count && cnd_timedwait(
            &sem->cond, &sem->lock, duration
        ) != thrd_success) {
            mtx_unlock(&sem->lock);
            return thrd_error;
        } else if (sem->count) {
            sem->count--;
        }

        return mtx_unlock(&sem->lock);
    }

    int sem_wait(sem_t* sem) {
        if (!sem) {
            errno = EINVAL;
            return thrd_error;
        } else if (mtx_lock(&sem->lock) == thrd_error) {
            return thrd_error;
        } else {
            int result = thrd_success;
            while (!sem->count && result == thrd_success)
                result = cnd_wait(&sem->cond, &sem->lock);

            sem->wait--;
            if (result == thrd_success) {
                sem->count--;
                return mtx_unlock(&sem->lock);
            } else {
                mtx_unlock(&sem->lock);
                return thrd_error;
            }
        }
    }

    int sem_trywait(sem_t* sem) {
        if (!sem) {
            errno = EINVAL;
            return thrd_error;
        } else if (mtx_lock(&sem->lock) == thrd_error) {
            return thrd_error;
        } else if (sem->count) {
            sem->count--;
            return mtx_unlock(&sem->lock);
        } else {
            mtx_unlock(&sem->lock);
            errno = EAGAIN;
            return thrd_error;
        }
    }

    int sem_post(sem_t* sem) {
        if (!sem) {
            errno = EINVAL;
            return thrd_error;
        } else if (mtx_lock(&sem->lock) == thrd_error) {
            return thrd_error;
        } else if (sem->wait && cnd_signal(&sem->cond) == thrd_error) {
            mtx_unlock(&sem->lock);
            return thrd_error;
        } else {
            sem->count++;
            return mtx_unlock(&sem->lock);
        }
    }

    int sem_getvalue(
        sem_t *__restrict sem,
        int *__restrict result_out
    ) {
        if (!sem) {
            errno = EINVAL;
            return thrd_error;
        } else if (mtx_lock(&sem->lock) == thrd_error) {
            return thrd_error;
        } else if (result_out) {
            *result_out = sem->count;
        }

        return mtx_unlock(&sem->lock);
    }
#endif

/* -- thread-local storage -------------------------------------------------- */

#ifdef _NO_TSS_DEFINITION
#   include <stdlib.h>
#   include <string.h>
#   define TSS_STORAGE_SIZE 256

    typedef struct __tss_dtor_entry {
        void* data;
        tss_dtor_t dtor;
    } __tss_dtor_entry;
    typedef struct __tss_entry {
        thrd_t thread;
        __tss_dtor_entry* storage;
    } __tss_entry;
    typedef struct __tss_opt_mtx {
        mtx_t lock;
        bool enabled;
    } __tss_opt_mtx;

    static __tss_entry __tss_storage[TSS_STORAGE_SIZE];
    static __tss_opt_mtx __tss_mtx;

    static int __tss_get_entry(__tss_entry** entry_out, bool alloc) {
        thrd_t thread;
        __tss_entry* entry, *blank;

        thread = thrd_current();
        blank = NULL;

        if (!__tss_mtx.enabled) {
            int result;
            if ((result = mtx_init(
                    &__tss_mtx.lock, mtx_plain)
            ) != thrd_success) {
                return result;
            }
            __tss_mtx.enabled = true;
        }

        if (mtx_lock(&__tss_mtx.lock) == thrd_error)
            return thrd_error;

        for (entry = __tss_storage;
            entry != &__tss_storage[TSS_STORAGE_SIZE];
            entry++
        ) {
            if (entry->thread == thread) {
                mtx_unlock(&__tss_mtx.lock);
                *entry_out = entry;
                return thrd_success;
            } else if (!entry->storage) {
                blank = entry;
            }
        }

        if (alloc && !blank) {
            return thrd_nomem;
        } else if (alloc) {
            blank->thread = thread;
            if (!(blank->storage =
                    (__tss_dtor_entry*)malloc(sizeof *blank->storage * 64)
            )) {
                return thrd_nomem;
            }

            *entry_out = blank;
            return thrd_success;
        }

        mtx_unlock(&__tss_mtx.lock);
        return thrd_error;
    }

    void __tss_thrd_exit(void) {
        __tss_entry* entry;
        if (__tss_get_entry(&entry, false) == thrd_success) {
            int i;
            for (i = 0; i < 64; i++) {
                if (entry->storage[i].dtor)
                    entry->storage[i].dtor(entry->storage[i].data);
            }

            free(entry);
            __tss_storage[entry - __tss_storage].storage = NULL;
        }
    }

    int tss_create(tss_t* key_out, tss_dtor_t destructor) {
        __tss_entry* entry;
        __tss_dtor_entry* dtor_entry;
        int result;

        if (!key_out) {
            return thrd_error;
        } else if ((result = __tss_get_entry(&entry, true)) != thrd_success) {
            return result;
        } else if (!destructor) {
            destructor = __extension__(tss_dtor_t)(void*)(uintptr_t)-1;
        }

        for (dtor_entry = entry->storage;
            dtor_entry != entry->storage + 64 && !dtor_entry->dtor;
            dtor_entry++
        );

        if (dtor_entry == entry->storage + 64) {
            return thrd_nomem;
        }

        dtor_entry->dtor = destructor;
        *key_out = (tss_t)(dtor_entry - entry->storage);
        return thrd_success;
    }

    void* tss_get(tss_t key) {
        __tss_entry* entry;
        if (__tss_get_entry(&entry, false) != thrd_success) {
            return NULL;
        }

        return (
            key >= 64 ||
            !entry->storage[key].dtor
        ) ? NULL : entry->storage[key].data;
    }

    int tss_set(tss_t key, void* value) {
        __tss_entry* entry;
        int result;

        if ((result = __tss_get_entry(&entry, false)) != thrd_success) {
            return result;
        } else if (key >= 64 || !entry->storage[key].dtor) {
            return thrd_error;
        }

        entry->storage[key].data = value;
        return thrd_success;
    }

    void tss_delete(tss_t key) {
        __tss_entry* entry;
        if (__tss_get_entry(&entry, false) == thrd_success &&
            key < 64 &&
            entry->storage[key].dtor
        ) {
            entry->storage[key].data = NULL;
            entry->storage[key].dtor = __extension__(tss_dtor_t)NULL;
        }
    }

#endif

/* -- call_once ------------------------------------------------------------- */

#ifdef _NO_CALLONCE_DEFINITION
#   if GCC_PREREQ(1) || CLANG_PREREQ(1)
#       if defined(__i386__) || defined(__x86_64__)
#           define __THRD_PAUSE() __asm__ __volatile__("pause\n")
#       elif (defined(__arm__) && __ARM_ARCH__ >= 7) || defined(__aarch64__)
#           define __THRD_PAUSE() __asm__ __volatile__("yield" ::: "memory")
#       elif (defined(__powerpc__) || defined(__powerpc64__))
#           define __THRD_PAUSE() __asm__ __volatile__("or 27,27,27")
#       endif
#   elif MSVC_PREREQ(1)
#       include <intrin.h>
#       if defined(__i386__)
#           define __THRD_PAUSE() _mm_pause()
#       elif defined(__arm__) || defined(__aarch64__)
#           define __THRD_PAUSE() __yield()
#       endif
#   elif defined(__WATCOMC__) && defined(__i386__)
        extern _inline void __THRD_PAUSE(void);
#       pragma aux __THRD_PAUSE = "db 0f3h,90h"
#       define __THRD_PAUSE __THRD_PAUSE
#   endif
#   ifndef __THRD_PAUSE
#       define __THRD_PAUSE()
#   endif

    void call_once(once_flag* flag, void (*func)(void)) {
        if (flag && func && atomic_flag_test_and_set(flag))
            func();
    }

#endif

/* -- C++ thread::hardware_concurrency -------------------------------------- */

#ifdef _GNU_SOURCE
#   include <sys/sysinfo.h>
#endif

unsigned thrd_hardware_concurrency(void) {
#if defined(_WIN32) || defined(__WINRT__)
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    return info.dwNumberOfProcessors;
#elif defined(__hpux)
    return pthread_num_processors_np();
#elif defined(__APPLE__) || defined(__FreeBSD__)
    int count;
    size_t size = sizeof count;
    return sysctlbyname("hw.ncpu", &count, &size, NULL, 0) ? 0 : count;
#elif defined(_SC_NPROCESSORS_ONLN)
    int const count = sysconf(_SC_NPROCESSORS_ONLN);
    return MAX(count, 0);
#elif defined(_GNU_SOURCE)
    return get_nprocs();
#else
    return 0;
#endif
}

#endif

/* ========================================================================== */

#endif /* THREAD_H_ */
