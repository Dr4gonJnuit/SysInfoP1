#include "../headers/includes.h"
#include "../headers/attente_active/my_mutex.h"

/**
 * @file perf_TAS.c
 * @brief The file perf_TAS.c is used to benchmark the TAS function and the TATAS function.
 *
 * We use the test_and_set() function for now.
 *
 */

#define CYCLES 6400

struct my_mutex_t *spin; //< the spinlock
int test = 0;

/**
 * @brief The function that will be executed by the TAS threads.
 *
 * @param arg The number of threads (need to be casted in an int).
 * @return void*
 */
void *TAS_test(void *arg)
{
    int nbr_threads = *(int *)arg;

    int i = 0;
    while (i < CYCLES / nbr_threads)
    {
        TAS_lock(spin);

        // critical section
        test++;
        for (int j = 0; j < 10000; j++)
        {
            // do nothing
        }

        my_unlock(spin);

        i++;
    }

    return (NULL);
}

/**
 * @brief The function that will be executed by the TATAS threads.
 *
 * @param arg The number of threads (need to be casted in an int).
 * @return void*
 */
void *TATAS_test(void *arg)
{
    int nbr_threads = *(int *)arg;

    int i = 0;
    while (i < CYCLES / nbr_threads)
    {
        TATAS_lock(spin);

        // critical section
        test++;
        for (int j = 0; j < 10000; j++)
        {
            // do nothing
        }

        my_unlock(spin);

        i++;
    }

    return (NULL);
}

/**
 * @brief The function that will run the TAS threads.
 *
 * @param nbr_threads The number of threads.
 * @return void
 */
void run_TAS(int nbr_threads)
{
    spin = (my_mutex_t *)malloc(sizeof(my_mutex_t));
    if (spin == NULL)
    {
        error(0, "malloc(spin)");
    }
    pthread_t threads[nbr_threads];

    my_mutex_init(spin);

    for (size_t i = 0; i < nbr_threads; i++)
    {
        int err = pthread_create(&threads[i], NULL, TAS_test, &nbr_threads);
        if (err != 0)
        {
            error(err, "pthread_create()");
        }
    }

    for (size_t i = 0; i < nbr_threads; i++)
    {
        int err = pthread_join(threads[i], NULL);
        if (err != 0)
        {
            error(err, "pthread_join()");
        }
    }

    free(spin);
}

/**
 * @brief The function that will run the TATAS threads.
 *
 * @param nbr_threads The number of threads.
 * @return void
 */
void run_TATAS(int nbr_threads)
{
    spin = (my_mutex_t *)malloc(sizeof(my_mutex_t));
    if (spin == NULL)
    {
        error(0, "malloc(spin)");
    }
    pthread_t threads[nbr_threads];

    my_mutex_init(spin);

    for (size_t i = 0; i < nbr_threads; i++)
    {
        int err = pthread_create(&threads[i], NULL, TATAS_test, &nbr_threads);
        if (err != 0)
        {
            error(err, "pthread_create()");
        }
    }

    for (size_t i = 0; i < nbr_threads; i++)
    {
        int err = pthread_join(threads[i], NULL);
        if (err != 0)
        {
            error(err, "pthread_join()");
        }
    }

    free(spin);
}

/**
 * @brief The main function.
 *
 * @param argc The number of arguments.
 * @param argv The arguments.
 * @return int
 */
int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        error(0, "Usage: ./perf_TAS nbr_threads");
    }

    printf("Benchmarking test_and_set()...\n");

    int nbr_threads = atoi(argv[1]);

    run_TAS(nbr_threads);
    // run_TATAS(nbr_threads);

    printf("test = %d\n", test);

    printf("Done.\n");

    return 0;
}
