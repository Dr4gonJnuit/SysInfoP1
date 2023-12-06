#include "../../headers/attente_active/my_semaphore.h"
#include "../../headers/attente_active/my_mutex.h"

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

    TATAS_lock(&sem->mutex);
    sem->value--;
    my_unlock(&sem->mutex);
}

void my_semaphore_post(my_semaphore_t *sem)
{
    TATAS_lock(&sem->mutex);
    sem->value++;
    my_unlock(&sem->mutex);
}
