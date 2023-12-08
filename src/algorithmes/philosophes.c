/**
 * @file philosophes.c
 * @brief Dining Philosophers Problem implementation.
 */

#include "../../headers/algorithmes/philosophes.h"
#include "../../headers/attente_active/my_mutex.h"

// #define CYCLES 10000000 // 10000000 = 10 000 000
#define CYCLES 1000000

#ifdef MYMUTEX_H
my_mutex_t *chopsticks; ///< Array of mutexes representing the chopsticks.
#else
pthread_mutex_t *chopsticks; ///< Array of mutexes representing the chopsticks.
#endif

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
            #ifdef MYMUTEX_H
            TATAS_lock(&chopsticks[left]);
            TATAS_lock(&chopsticks[right]);
            #else
            pthread_mutex_lock(&chopsticks[left]);
            pthread_mutex_lock(&chopsticks[right]);
            #endif
        }
        else
        {
            #ifdef MYMUTEX_H
            TATAS_lock(&chopsticks[right]);
            TATAS_lock(&chopsticks[left]);
            #else
            pthread_mutex_lock(&chopsticks[right]);
            pthread_mutex_lock(&chopsticks[left]);
            #endif
        }

        // eat(id);
        
        #ifdef MYMUTEX_H
        my_unlock(&chopsticks[left]);
        my_unlock(&chopsticks[right]);
        #else
        pthread_mutex_unlock(&chopsticks[left]);
        pthread_mutex_unlock(&chopsticks[right]);
        #endif
        i++;
    }

    return (NULL);
}

void run_philosophes(int nbr_philosophe)
{
    int err; //< Variable used to verify the eventual error.
    pthread_t phil[nbr_philosophe];

    #ifdef MYMUTEX_H
    chopsticks = (my_mutex_t *)malloc(sizeof(my_mutex_t) * nbr_philosophe);
    if (chopsticks == NULL)
    {
        error(0, "malloc(chopsticks)");
    }
    #else
    chopsticks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nbr_philosophe);
    if (chopsticks == NULL)
    {
        error(0, "malloc(chopsticks)");
    }
    #endif

    struct args_philosophes args_philosophes[nbr_philosophe];

    size_t i = 0;
    for (i = 0; i < nbr_philosophe; i++)
    {
        args_philosophes[i].nbr_philosophes = nbr_philosophe;
        args_philosophes[i].id = i;
    }

    for (i = 0; i < nbr_philosophe; i++)
    {
        #ifdef MYMUTEX_H
        my_mutex_init(&chopsticks[i]);
        #else
        err = pthread_mutex_init(&chopsticks[i], NULL);
        if (err != 0)
        {
            error(err, "Mutex(es) Initialisation (pthread_mutex_init())");
        }
        #endif
        
    }

    for (i = 0; i < nbr_philosophe; i++)
    {
        err = pthread_create(&phil[i], NULL, philosophe, (void *)&(args_philosophes[i]));
        if (err != 0)
        {
            error(err, "Thread(s) Creation (pthread_create())");
        }
    }

    for (i = 0; i < nbr_philosophe; i++)
    {
        err = pthread_join(phil[i], NULL);
        if (err != 0)
        {
            error(err, "Thread(s) Join (pthread_join())");
        }
    }

    #ifdef MYMUTEX_H
    #else
    for (i = 0; i < nbr_philosophe; i++)
    {
        err = pthread_mutex_destroy(&chopsticks[i]);
        if (err != 0)
        {
            error(err, "Mutex(es) Destruction (pthread_mutex_destroy())");
        }
    }
    #endif

    free(chopsticks);
}