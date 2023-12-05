#ifndef MYMUTEX_H
#define MYMUTEX_H

#include "includes.h"

typedef struct my_mutex
{
    volatile long flag;
} my_mutex;

void my_mutex_init(struct my_mutex *mutex);

static inline bool my_lock(struct my_mutex *mutex)
{
    asm volatile(
        "movl $1, %%eax\n"
        "xchgl %%eax, %0\n"
        : "+m"(mutex->flag)
        :
        : "eax", "memory"
    );

    return mutex->flag;
}

void test_and_set(struct my_mutex *mutex);

void test_and_test_and_set(struct my_mutex *mutex);

static inline int my_unlock(struct my_mutex *mutex)
{
    asm("movl $0, %%eax\n"
        "xchgl %%eax, %0\n"
        : "+m"(mutex->flag)
        :
        : "eax", "memory"
    );

    return 0;
}

/*

* Old implementation should work

static inline int test_and_set(struct my_mutex *mutex)
{
    asm volatile(
        "lock:\n"
        "   movl $1, %%eax\n"
        "   xchgl %%eax, %0\n"
        "   testl %%eax, %%eax\n"
        "   jnz lock\n"
        : "+m"(mutex->flag)
        :
        : "eax"
    );

    return 0;
}

static inline int test_and_test_and_set(struct my_mutex *mutex)
{
    asm volatile(
        "lock:\n"
        "   movl $1, %%eax\n"
        "   testl %%eax, %0\n"
        "   jnz lock\n"
        "   xchgl %%eax, %0\n"
        "   testl %%eax, %%eax\n"
        "   jnz lock\n"
        : "+m"(mutex->flag)
        :
        : "eax"
    );

    return 0;
}
*/

#endif // MYMUTEX_H
