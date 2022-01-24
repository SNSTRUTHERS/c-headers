/**
 * @file thread.h
 * @author Simon Bolivar
 * @date 23 Jan 2022
 * 
 * @brief Standard C11 library compatible threading header.
 * 
 * @copyright LGPL-3.0
 */

#ifndef THREAD_H_
#define THREAD_H_

#include "macrodefs.h"

#if defined(_WIN32) || defined(__WINRT__)
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
#   include <limits.h>
#   include <stdlib.h>
#   include <string.h>
#   include <time.h>
#   include <windows.h>
#elif defined(__unix__) || defined(__MACOSX__)
#   include <pthread.h>
#   include <sched.h>
#   include <sys/types.h>
#   include <sys/time.h>
#   include <time.h>
#   include <unistd.h>
#   ifndef __APPLE__
#       include <semaphore.h>
#   else
#       include <sys/sysctl.h>
#       define _NO_SEM_DEFINITION 1
#   endif
#   ifdef _GNU_SOURCE
#       include <sys/sysinfo.h>
#   endif
#else
#   error "Unsupported operating system"
#endif

#ifndef __STDC_NO_THREADS__ /* -- c11 implementation ------------------------ */
#   define THRD_CONV
#   define TSS_DTOR_SETUP()
#   define _NO_SEM_DEFINITION 1
#elif defined(__WINRT__) || defined(_WIN32) /* -- windows implementation ---- */

/* ---- typedefs ------------------------------------------------------------ */

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
    
#   if !defined(__WINRT__) || (_WIN32_WINNT < 0x602)
        typedef union sem_u {
            HANDLE kern;
            LONG volatile atom;
        } sem_t;
#       define _NO_WIN8_SEMATOMS 1
#   else
        typedef struct sem_s {
            LONG volatile atom;
        } sem_t;
#   endif
#   if !defined(__WINRT__) || (_WIN32_WINNT < 0x0600)
        typedef struct cnd_s {
            CRITICAL_SECTION lock;
            int wait, sigs;
            sem_t sem_wait, sem_done;
        } cnd_t;
#       define _NO_VISTA_CONDVAR 1
#   else
        typedef CONDITION_VARIABLE cnd_t;
#   endif
    
    typedef HANDLE thrd_t;
    typedef CRITICAL_SECTION mtx_t;
    typedef DWORD tss_t;
    typedef struct once_flag {
        LONG volatile l;
    } once_flag;
    typedef int (*thrd_start_t)(void*);
    typedef void (*tss_dtor_t)(void*);
    
    typedef struct __tss_dtor_entry {
        tss_t key;
        tss_dtor_t dtor;
    } __tss_dtor_entry;
    extern __tss_dtor_entry __tss_dtor_table[64];

/* ---- macrodefs ----------------------------------------------------------- */
    
#   define THRD_CONV WINAPI
#   define ONCE_FLAG_INIT { 0 }
#   define TSS_DTOR_ITERATIONS 1
#   define SEM_VALUE_MAX LONG_MAX

#   define __TIMESPEC_TO_MS(ts) ( \
        ((ts)->tv_sec * 1000u) + ((ts)->tv_nsec / 1000000) \
    )
#   define TSS_DTOR_SETUP() __tss_dtor_entry __tss_dtor_table[64]

/* ---- thread API ---------------------------------------------------------- */

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

    static_inline int thrd_create(
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
    
    static_inline int thrd_equal(thrd_t a, thrd_t b) {
        return a == b;
    }
    
    static_inline thrd_t thrd_current(void) {
        return GetCurrentThread();
    }
    
    static int thrd_sleep(
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
    
    static_inline void thrd_yield(void) {
        SwitchToThread();
    }

    NO_RETURN static_inline void thrd_exit(int result) {
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
    
    static_inline int thrd_detach(thrd_t thread) {
        if (!thread) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_error;
        } else if (!CloseHandle(thread)) {
            return thrd_error;
        } else {
            return thrd_success;
        }
    }
    
    static_inline int thrd_join(thrd_t thread, int* result_out) {
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

/* ---- mutex API ----------------------------------------------------------- */
    
    static_inline int mtx_init(mtx_t* mutex, int type) {
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
    
    static_inline int mtx_lock(mtx_t* mutex) {
        if (!mutex) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_error;
        } else {
            EnterCriticalSection(mutex);
            return thrd_success;
        }
    }
    
    static_inline int mtx_trylock(mtx_t* mutex) {
        if (!mutex) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_error;
        } else {
            return TryEnterCriticalSection(mutex) ? thrd_success : thrd_error;
        }
    }
    
    static_inline int mtx_timedlock(
        mtx_t *__restrict mutex,
        struct timespec const *__restrict duration
    ) {
        if (!mutex ||
            !duration ||
            duration->tv_sec < 0 ||
            duration->tv_nsec < 0 ||
            duration->tv_nsec >= 1000000000
        ) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_error;
        } else {
            union {
                uint64_t nsx100;
                FILETIME filetime;
            } expire, now;
            
            GetSystemTimeAsFileTime(&expire.filetime);
            expire.nsx100 += __TIMESPEC_TO_MS(duration) * 10000;
            while (mtx_trylock(mutex) != thrd_success) {
                GetSystemTimeAsFileTime(&now.filetime);
                if (expire.nsx100 < now.nsx100) {
                    return thrd_timedout;
                } else {
                    thrd_yield();
                }
            }
            
            return thrd_success;
        }
    }
    
    static_inline int mtx_unlock(mtx_t* mutex) {
        if (!mutex) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return thrd_error;
        } else {
            LeaveCriticalSection(mutex);
            return thrd_success;
        }
    }
    
    static_inline void mtx_destroy(mtx_t* mutex) {
        if (mutex)
            DeleteCriticalSection(mutex);
    }

/* ---- semaphore API ------------------------------------------------------- */

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

    static_inline int sem_init(sem_t* sem, int shared, unsigned int value) {
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
    
    static_inline int sem_destroy(sem_t* sem) {
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
    
    static_inline int sem_trywait(sem_t* sem) {
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
    
    static_inline int sem_timedwait(
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
                            return thrd_error;
                        } else {
                            c = sem->atom;
                        }
                    }
                } while (InterlockedCompareExchange(&sem->atom, c - 1, c) != c);
                return thrd_success;
            }
        }
    }
    
    static_inline int sem_wait(sem_t* sem) {
        return sem_timedwait(sem, NULL);
    }
    
    static_inline int sem_post(sem_t* sem) {
            SetLastError(ERROR_INVALID_PARAMETER);
        if (!sem) {
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
    
    static_inline int sem_getvalue(
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

/* ---- condition variable API ---------------------------------------------- */
    
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
    
    static_inline int cnd_init(cnd_t* cond) {
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
    
    static_inline int cnd_signal(cnd_t* cond) {
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
    
    static_inline int cnd_broadcast(cnd_t* cond) {
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
    
    static_inline int cnd_timedwait(
        cnd_t *__restrict cond,
        mtx_t *__restrict mutex,
        struct timespec const *__restrict duration
    ) {
        if (!cond || !mutex || (duration &&
                duration->tv_sec < 0 ||
                duration->tv_nsec < 0 ||
                duration->tv_nsec >= 1000000000
        )) {
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
    
    static_inline int cnd_wait(cnd_t* cond, mtx_t* mutex) {
        return cnd_timedwait(cond, mutex, NULL);
    }
    
    static_inline void cnd_destroy(cnd_t* cond) {
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

/* ---- thread-local storage API -------------------------------------------- */
    
    static_inline int tss_create(tss_t* key_out, tss_dtor_t destructor) {
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
                entry != __tss_dtor_table + ARRAY_LENGTH(__tss_dtor_table) &&
                    !entry->dtor;
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
    
    static_inline void* tss_get(tss_t key) {
        return TlsGetValue(key);
    }
    
    static_inline int tss_set(tss_t key, void* value) {
        return TlsSetValue(key, value) ? thrd_success : thrd_error;
    }
    
    static_inline void tss_delete(tss_t key) {
        TlsFree(key);
    }

/*  ---- call once API ------------------------------------------------------ */
    
    static_inline void call_once(once_flag* flag, void (*func)(void)) {
        if (flag && func) {
            if (!InterlockedCompareExchange(&flag->l, 1, 0)) {
                (*func)();
                InterlockedExchange(&flag->l, 2);
            } else while (flag->l == 1) {
                thrd_yield();
            }
        }
    }

/* ---- cleanup ------------------------------------------------------------- */
    
#   undef __TIMESPEC_TO_MS
#   ifdef _NO_VISTA_CONDVAR
#       undef _NO_VISTA_CONDVAR
#   endif
#   ifdef _NO_WIN8_SEMATOMS
#       undef _NO_WIN8_SEMATOMS
#   endif

#else /* -- pthread implementation ------------------------------------------ */
#   include <errno.h>

/* ---- typedefs ------------------------------------------------------------ */

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
    typedef int (*thrd_start_t)(void*);
    typedef void (*tss_dtor_t)(void*);

/* ---- macrodefs ----------------------------------------------------------- */

#   define THRD_CONV
#   define ONCE_FLAG_INIT PTHREAD_ONCE_INIT
#   define TSS_DTOR_ITERATIONS PTHREAD_DESTRUCTOR_ITERATIONS
#   define TSS_DTOR_SETUP()

/* ---- thread API ---------------------------------------------------------- */

    static_inline int thrd_create(
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

    static_inline int thrd_equal(thrd_t a, thrd_t b) {
        return pthread_equal(a, b);
    }

    static_inline thrd_t thrd_current(void) {
        return pthread_self();
    }

    static_inline int thrd_sleep(
        struct timespec const* duration,
        struct timespec* remaining
    ) {
        int result = nanosleep(duration, remaining);
        return (result == -1 && errno != EINTR) ? -errno : result;
    }

    static_inline void thrd_yield(void) {
        sched_yield();
    }

    NO_RETURN static_inline void thrd_exit(int result) {
        pthread_exit((void*)(intptr_t)result);
    }

    static_inline int thrd_detach(thrd_t thread) {
        return pthread_detach(thread) ? thrd_error : thrd_success;
    }

    static_inline int thrd_join(thrd_t thread, int* result_out) {
        void* result;
        
        if (pthread_join(thread, &result) != 0) {
            return thrd_error;
        } else if (result_out) {
            *result_out = (int)(intptr_t)result;
        }
        
        return thrd_success;
    }

/* ---- mutex API ----------------------------------------------------------- */
    
    static_inline int mtx_init(mtx_t* mutex, int type) {
        int result;
        pthread_mutexattr_t attr;
        
        pthread_mutexattr_init(&attr);
        
        if (type & mtx_timed) {
#           ifdef __linux__
                pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_TIMED_NP);
#           elif defined(PTHREAD_MUTEX_TIMED)
                pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_TIMED);
#           endif
        }
        if (type & mtx_recursive) {
#           ifdef __linux__
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

    static_inline int mtx_lock(mtx_t* mutex) {
        return pthread_mutex_lock(mutex) ? thrd_error : thrd_success;
    }

    static_inline int mtx_timedlock(
        mtx_t *__restrict mutex,
        struct timespec const *__restrict duration
    ) {
#   if !defined(__CYGWIN__) && !defined(__MACOSX__)
        switch (pthread_mutex_timedlock(mutex, duration)) {
        case ETIMEDOUT:
            return thrd_timedout;
        case 0:
            return thrd_success;
        default:
            return thrd_error;
        }
#   else
        if (!mutex ||
            !duration ||
            duration->tv_sec < 0 ||
            duration->tv_nsec < 0 ||
            duration->tv_nsec >= 1000000000
        ) {
            errno = EINVAL;
            return thrd_error;
        }

        struct timespec expire, now;
        clock_gettime(CLOCK_REALTIME, &expire);
        expire.tv_sec += duration->tv_sec;
        expire.tv_nsec += duration->tv_nsec;

        while (mtx_trylock(mutex) != thrd_success) {
            clock_gettime(CLOCK_REALTIME, &now);
            if (expire.tv_sec < now.tv_sec ||
                expire.tv_nsec < now.tv_nsec
            ) {
                return thrd_timedout;
            } else {
                thrd_yield();
            }
        }

        return thrd_success;
#   endif
    }

    static_inline int mtx_trylock(mtx_t* mutex) {
        switch (pthread_mutex_trylock(mutex)) {
        case EBUSY:
            return thrd_busy;
        case 0:
            return thrd_success;
        default:
            return thrd_error;
        }
    }

    static_inline int mtx_unlock(mtx_t* mutex) {
        return pthread_mutex_unlock(mutex) ? thrd_error : thrd_success;
    }

    static_inline void mtx_destroy(mtx_t* mutex) {
        pthread_mutex_destroy(mutex);
    }

/* ---- condition variable API ---------------------------------------------- */

    static_inline int cnd_init(cnd_t* cond) {
        return pthread_cond_init(cond, 0) ? thrd_error : thrd_success;
    }

    static_inline int cnd_signal(cnd_t* cond) {
        return pthread_cond_signal(cond) ? thrd_error : thrd_success;
    }

    static_inline int cnd_broadcast(cnd_t* cond) {
        return pthread_cond_broadcast(cond) ? thrd_error : thrd_success;
    }

    static_inline int cnd_wait(cnd_t* cond, mtx_t* mutex) {
        return pthread_cond_wait(cond, mutex) ? thrd_error : thrd_success;
    }

    static_inline int cnd_timedwait(
        cnd_t *__restrict cond,
        mtx_t *__restrict mutex,
        struct timespec const *__restrict duration
    ) {
        switch (pthread_cond_timedwait(cond, mutex, duration)) {
        case ETIMEDOUT:
            return thrd_timedout;
        case 0:
            return thrd_success;
        default:
            return thrd_error;
        }
    }

    static_inline void cnd_destroy(cnd_t* cond) {
        pthread_cond_destroy(cond);
    }

/* ---- thread-local storage API -------------------------------------------- */
    
    static_inline int tss_create(tss_t* key, tss_dtor_t destructor) {
        return pthread_key_create(key, destructor) ? thrd_error : thrd_success;
    }

    static_inline void* tss_get(tss_t key) {
        return pthread_getspecific(key);
    }

    static_inline int tss_set(tss_t key, void* value) {
        return pthread_setspecific(key, value) ? thrd_error : thrd_success;
    }

    static_inline void tss_delete(tss_t key) {
        pthread_key_delete(key);
    }

/* ---- call once API ------------------------------------------------------- */

    static_inline void call_once(once_flag* flag, void (*func)(void)) {
        pthread_once(flag, func);
    }
#endif

/* ---- semaphores ---------------------------------------------------------- */

#ifdef _NO_SEM_DEFINITION
#   undef _NO_SEM_DEFINITION
#   define SEM_VALUE_MAX INT_MAX

    typedef struct sem_s {
        int count, wait;
        mtx_t lock;
        cnd_t cond;
    } sem_t;
    
    static_inline int sem_init(sem_t* sem, int shared, unsigned int value) {
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
    
    static_inline int sem_destroy(sem_t* sem) {
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
    
    static_inline int sem_timedwait(
        sem_t *__restrict sem,
        struct timespec const *__restrict duration
    ) {
        
        if (!sem) {
            errno = EINVAL;
            return thrd_error;
        } else if (mtx_lock(&sem->lock) == thrd_error) {
            return thrd_error;
        } else if (
            !sem->count &&
            cnd_timedwait(&sem->cond, &sem->lock, duration) != thrd_success
        ) {
            mtx_unlock(&sem->lock);
            return thrd_error;
        } else if (sem->count) {
            sem->count--;
        }
        
        return mtx_unlock(&sem->lock);
    }
    
    static_inline int sem_wait(sem_t* sem) {
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
    
    static_inline int sem_trywait(sem_t* sem) {
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
    
    static_inline int sem_post(sem_t* sem) {
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
    
    static_inline int sem_getvalue(
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

/* -- C++ thread::hardware_concurrency -------------------------------------- */
    
static_inline unsigned int thrd_hardware_concurrency(void) {
#if defined(_WIN32) || defined(__WINRT__)
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    return info.dwNumberOfProcessors;
#elif defined(__hpux)
    return pthread_num_processors_np();
#elif defined(__APPLE__) || defined(__FreeBSD__)
    int count;
    size_t size = sizeof count;
    return sysctlbyname("hw.cpu", &count, &size, NULL, 0) ? 0 : count;
#elif defined(_SC_NPROCESSORS_ONLN)
    int const count = sysconf(_SC_NPROCESSORS_ONLN);
    return MAX(count, 0);
#elif defined(_GNU_SOURCE)
    return get_nprocs();
#else
    return 0;
#endif
}

#endif /* THREAD_H_ */
