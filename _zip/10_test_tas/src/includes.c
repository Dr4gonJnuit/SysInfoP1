#include "../headers/includes.h"

void error(int err, char *msg)
{
	fprintf(stderr, "%s returned %d error message : %s\n", msg, err, strerror(errno));
	exit(EXIT_FAILURE);
}
