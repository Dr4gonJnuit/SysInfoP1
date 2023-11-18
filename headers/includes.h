#ifndef INCLUDES
#define INCLUDES

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

/**
 * @brief Put on \c stderr the thing that did wrong
 * 
 * @param err 
 * @param msg 
 */
void error(int err, char *msg);

#endif // INCLUDES