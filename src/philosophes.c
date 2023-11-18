/**
 * @file philosophes.c
 * @brief Dining Philosophers Problem implementation.
 */

#include "../headers/philosophes.h"

#define CYCLES 10 // 10000000 = 10 000 000
#define CYCLES_GOOD 10000000

pthread_mutex_t *chopsticks; ///< Array of mutexes representing the chopsticks.

void eat(int id)
{
    printf("Philosophe [%d] eat\n", id);
    for (int i = 0; i < rand(); i++)
    {
        // Philosophe is eating
    }
}

void *philosophe(void *arg)
{
    // Parse args
    struct args_philosophes *args_philosophes = (struct args_philosophes *)arg;

    int id = args_philosophes->id;
    int left = id;
    int right = (left + 1) % args_philosophes->nbr_philosophes;

    int i = 0;
    while (i < CYCLES)
    {
        if (left < right) // Verifie if he can take a chopsticks.
        {
            pthread_mutex_lock(&chopsticks[left]);
            pthread_mutex_lock(&chopsticks[right]);
        }
        else
        {
            pthread_mutex_lock(&chopsticks[right]);
            pthread_mutex_lock(&chopsticks[left]);
        }

        eat(id);
        
        pthread_mutex_unlock(&chopsticks[left]);
        pthread_mutex_unlock(&chopsticks[right]);
        i++;
    }

    return (NULL);
}

void run_philosophes(int nbr_philosophe)
{
    pthread_t phil[nbr_philosophe];
    chopsticks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nbr_philosophe);

    struct args_philosophes args_philosophes[nbr_philosophe];

    size_t i = 0;
    for (i = 0; i < nbr_philosophe; i++)
    {
        args_philosophes[i].nbr_philosophes = nbr_philosophe;
        args_philosophes[i].id = i;
    }

    for (i = 0; i < nbr_philosophe; i++)
    {
        pthread_mutex_init(&chopsticks[i], NULL);
    }

    for (i = 0; i < nbr_philosophe; i++)
    {
        pthread_create(&phil[i], NULL, philosophe, (void *)&(args_philosophes[i]));
    }

    for (i = 0; i < nbr_philosophe; i++)
    {
        pthread_join(phil[i], NULL);
    }

    for (i = 0; i < nbr_philosophe; i++)
    {
        pthread_mutex_destroy(&chopsticks[i]);
    }
}
