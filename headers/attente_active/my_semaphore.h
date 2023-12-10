#ifndef MYSEMAPHORE_H
#define MYSEMAPHORE_H

#include "../includes.h"
#include "my_mutex.h"

/**
 * @brief Structure of a semaphore
 *
 * @param value (volatile long) The value of the semaphore
 * @param mutex (struct my_mutex_t) The mutex of the semaphore
 */
typedef struct my_semaphore_t
{
    volatile long value;
    struct my_mutex_t mutex;
} my_semaphore_t;

/**
 * @brief Initialize the semaphore
 *
 * @param sem The semaphore to initialize
 * @param value The value of the semaphore
 */
void my_semaphore_init(my_semaphore_t *sem, long value);

/**
 * @brief Wait for the semaphore to be available
 *
 * @param sem The semaphore to wait
 */
void my_semaphore_wait(my_semaphore_t *sem);

/**
 * @brief Post the semaphore
 *
 * @param sem The semaphore to post
 */
void my_semaphore_post(my_semaphore_t *sem);

#endif // MYSEMAPHORE_H
