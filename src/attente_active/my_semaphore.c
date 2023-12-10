#include "../../headers/attente_active/my_semaphore.h"
#include "../../headers/attente_active/my_mutex.h"

/**
 * @file my_semaphore.c
 * @brief The file my_semaphore.c contains the implementation of the semaphores.
 *
 * We use the test_and_set() function for now.
 */

void my_semaphore_init(my_semaphore_t *sem, long value)
{
    sem->value = value;
    my_mutex_init(&sem->mutex);
}

void my_semaphore_wait(my_semaphore_t *sem)
{
    while ((sem->value <= 0) && (sem->mutex.flag == 0))
    {
    }

    TAS_lock(&sem->mutex);
    sem->value--;
    my_unlock(&sem->mutex);
}

void my_semaphore_post(my_semaphore_t *sem)
{
    TAS_lock(&sem->mutex);
    sem->value++;
    my_unlock(&sem->mutex);
}
