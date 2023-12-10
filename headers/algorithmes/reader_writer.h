#ifndef READER_WRITER_H
#define READER_WRITER_H

#include "../includes.h"

/**
 * @brief Function to execute the reader-writer algorithm.
 * @note Destroy the mutexes at the end.
 *
 * @param nbr_reader Number of reader threads.
 * @param nbr_writer Number of writer threads
 */
void run_reader_writer(int nbr_reader, int nbr_writer);

#endif // READER_WRITER_H
