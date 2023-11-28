#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

/**
 * @brief Put on stderr the thing that did wrong
 * 
 * @param err The error value a function did return
 * @param msg The indication about what failed.
 */
void error(int err, char *msg);

#endif // INCLUDES_H
