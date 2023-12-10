#include "../headers/includes.h"

/**
 * @file includes.c
 * @brief The file includes.c contains all the includes needed for the project and the error function.
 */

void error(int err, char *msg)
{
	fprintf(stderr, "%s returned %d error message : %s\n", msg, err, strerror(errno));
	exit(EXIT_FAILURE);
}
