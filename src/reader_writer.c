#include "../headers/reader_writer.h"

void reader(void)
{
    while (true)
    {
        pthread_mutex_lock(&mutex);
        // section critique
        readcount++;
        if (readcount == 1)
        { // arrivée du premier reader
            sem_wait(&db);
        }
        pthread_mutex_unlock(&mutex);
        read_database();
        pthread_mutex_lock(&mutex);
        // section critique
        readcount--;
        if (readcount == 0)
        { // départ du dernier reader
            sem_post(&db);
        }
        pthread_mutex_unlock(&mutex);
        process_data();
    }
}

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
