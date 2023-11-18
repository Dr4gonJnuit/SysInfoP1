#ifndef PHILOSOPHES
#define PHILOSOPHES

#include "includes.h"

typedef struct args_philosophes
{
    int nbr_philosophes; ///< Number of philosophers.
    int id;              ///< Philosopher ID.
} args_philosophes;

/**
 * @brief Function to execute the Dining Philosophers Problem by launching the differents threads and mutexes.
 * @note Destroy the mutexes at the end.
 *
 * @param nbr_philosophe Number of philosophers.
 */
void run_philosophes(int nbr_philosophe);

#endif // PHILOSOPHES