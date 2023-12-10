#ifndef PRODUC_CONSO_H
#define PRODUC_CONSO_H

#include "../includes.h"

/**
 * @brief Function to execute the producer-consumer algorithm.
 * @note Destroy the mutexes at the end.
 *
 * @param nbr_produc Number of producer threads.
 * @param nbr_conso Number of consumer threads
 */
void run_produc_conso(int nbr_produc, int nbr_conso);

#endif // PRODUC_CONSO_H
