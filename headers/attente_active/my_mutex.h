#ifndef MYMUTEX_H
#define MYMUTEX_H

#include "../includes.h"

// Need to be in asm so it can be atomic like the consigne says

/**
 * @brief Structure of a mutex, the volatile is here to prevent the compiler to optimize the code and to force it to read the value in memory
 *
 * @param flag (volatile long) The flag of the mutex (0 = unlocked, 1 = locked)
 */
typedef struct my_mutex_t
{
    volatile long flag;
} my_mutex_t;

/**
 * @brief Initialize the mutex
 *
 * @param mutex The mutex to initialize
 * @return (long) 0 if the mutex was initialized successfully
 */
long my_mutex_init(struct my_mutex_t *mutex);

/**
 * @brief Lock the mutex with the Test-And-Set algorithm
 *
 * @param mutex The mutex to lock
 * @return (long) 0 if the mutex was locked successfully, loop otherwise
 */
long TAS_lock(struct my_mutex_t *mutex);

/**
 * @brief Lock the mutex with the Test-And-Test-And-Set algorithm
 *
 * @param mutex The mutex to lock
 * @return (long) 0 if the mutex was locked successfully, loop otherwise
 */
long TATAS_lock(struct my_mutex_t *mutex);

/**
 * @brief Unlock the mutex
 *
 * @param mutex The mutex to unlock
 * @return (long) 0 if the mutex was unlocked successfully
 */
long my_unlock(struct my_mutex_t *mutex);

#endif // MYMUTEX_H
