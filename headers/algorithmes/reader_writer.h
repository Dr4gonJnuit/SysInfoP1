#ifndef READER_WRITER_H
#define READER_WRITER_H

#include "../includes.h"

/**
 * @brief Function to execute the Dining Philosophers Problem by launching the differents threads and mutexes.
 * @note Destroy the mutexes at the end.
 *
 * @param nbr_philosophe Number of philosophers.
 */
void run_reader_writer(int nbr_reader, int nbr_writer);

#endif // READER_WRITER_H
