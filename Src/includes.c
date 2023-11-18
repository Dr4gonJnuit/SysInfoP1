#include "../headers/includes.h"

void error(int err, char *msg)
{
  fprintf(stderr, "%s a retourné %d message d'erreur : %s\n", msg, err, strerror(errno));
  exit(EXIT_FAILURE);
}
