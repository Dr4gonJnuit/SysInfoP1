#include "../headers/my_mutex.h"

void my_mutex_init(struct my_mutex *mutex)
{
    mutex->flag = 0;
}

void test_and_set(struct my_mutex *mutex)
{
    while (my_lock(mutex))
    {
        // spin
    }
}

void test_and_test_and_set(struct my_mutex *mutex)
{
    while (my_lock(mutex))
    {
        // spin
        while (mutex->flag)
        {
            // spin
        }
    }
}
