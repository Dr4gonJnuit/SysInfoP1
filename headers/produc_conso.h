#ifndef PRODUC_CONSO_H
#define PRODUC_CONSO_H

#include "includes.h"

/**
 * @brief Function to execute the Dining Philosophers Problem by launching the differents threads and mutexes.
 * @note Destroy the mutexes at the end.
 *
 * @param nbr_philosophe Number of philosophers.
 */
void run_produc_conso(int nbr_produc, int nbr_conso);

#endif // PRODUC_CONSO_H
