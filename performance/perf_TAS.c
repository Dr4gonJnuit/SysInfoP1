#include "../headers/includes.h"
#include "../headers/attente_active/my_mutex.h"

#define CYCLES 6400

struct my_mutex *spin;
int test = 0;

void *TAS_test(void *arg)
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

void run_TAS(int nbr_threads)
{
    spin = (my_mutex *)malloc(sizeof(my_mutex));
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

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        error(0, "Usage: ./perf_TAS nbr_threads");
    }

    printf("Benchmarking test_and_set()...\n");

    int nbr_threads = atoi(argv[1]);

    run_TAS(nbr_threads);

    printf("test = %d\n", test);

    printf("Done.\n");

    return 0;
}
