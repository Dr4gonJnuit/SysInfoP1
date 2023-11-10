#include "../header/writer.h"

void writer(void)
{
    while (true)
    {
        prepare_data();
        sem_wait(&db);
        // section critique, un seul writer à la fois
        write_database();
        sem_post(&db);
    }
}