#include "../../headers/attente_active/my_mutex.h"

/**
 * @file my_mutex.c
 * @brief The file my_mutex.c contains the implementation of the mutexes.
 *
 */

long my_mutex_init(struct my_mutex_t *mutex)
{
    asm("movl $0, %%eax\n"
        "xchgl %%eax, %0\n"
        : "+m"(mutex->flag)
        :
        : "eax", "memory");

    return 0;
}

long TAS_lock(struct my_mutex_t *mutex)
{
    long result;

    asm volatile(
        "TAS_enter:\n"
        "   movl $1, %%eax\n"
        "   xchgl %%eax, %0\n"
        "   testl %%eax, %%eax\n"
        "   jnz TAS_enter\n" // If another thread was faster to lock, we jump to TAS_enter
        : "+m"(mutex->flag), "=a"(result)
        :
        : "memory");

    return result;
}

long TATAS_lock(struct my_mutex_t *mutex)
{
    long result;

    asm volatile(
        "TATAS_enter:\n"
        "   movl $1, %%eax\n"
        "   testl %%eax, %0\n"
        "   jnz TATAS_enter\n" // If the value is 1, we jump to TATAS_enter
        "   xchgl %%eax, %0\n"
        "   testl %%eax, %%eax\n"
        "   jnz TATAS_enter\n" // If another thread was faster to lock, we jump to TATAS_enter
        : "+m"(mutex->flag), "=a"(result)
        :
        : "memory");

    return result;
}

long my_unlock(struct my_mutex_t *mutex)
{
    asm("movl $0, %%eax\n"
        "xchgl %%eax, %0\n"
        : "+m"(mutex->flag)
        :
        : "eax", "memory");

    return 0;
}
