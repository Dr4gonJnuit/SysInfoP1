#ifndef MYSEMAPHORE_H
#define MYSEMAPHORE_H

#include "../includes.h"
#include "my_mutex.h"

typedef struct my_semaphore_t
{
    volatile long value;
    struct my_mutex_t mutex;
} my_semaphore_t;

void my_semaphore_init(my_semaphore_t *sem, long value);

void my_semaphore_wait(my_semaphore_t *sem);

void my_semaphore_post(my_semaphore_t *sem);

#endif // MYSEMAPHORE_H
