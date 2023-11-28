#include "../headers/reader_writer.h"

#define READER_CYCLE 2500
#define WRITER_CYCLE 640

pthread_mutex_t mutex_rw;
pthread_mutex_t mutex_readcount;
pthread_mutex_t mutex_writecount;

// sem_t db; //< access to the db
sem_t reader_sem;
sem_t writer_sem;

int readcount = 0;	// number of readers
int writecount = 0; // number of writers

void read_data()
{
	printf("Reading data...\n");
}

void write_data()
{
	printf("Writing data...\n");
}

/* Reader */
void *reader()
{
	int i = 0;
	while (i < READER_CYCLE)
	{
		pthread_mutex_lock(&mutex_rw);
		sem_wait(&reader_sem);

		pthread_mutex_lock(&mutex_readcount);
		readcount++;
		if (readcount == 1)
		{
			sem_wait(&writer_sem);
		}

		pthread_mutex_unlock(&mutex_readcount);
		sem_post(&reader_sem);
		pthread_mutex_unlock(&mutex_rw);

		// read_data(); //< Reading database

		pthread_mutex_lock(&mutex_readcount);
		readcount--;
		if (readcount == 0)
		{
			sem_post(&writer_sem);
		}

		pthread_mutex_unlock(&mutex_readcount);

		// Using the data read

		i++;
	}

	return (NULL);
}

/* Writer */
void *writer()
{
	int i = 0;
	while (i < WRITER_CYCLE)
	{
		// Think the data

		pthread_mutex_lock(&mutex_writecount);
		writecount++;
		if (writecount == 1)
		{
			sem_wait(&reader_sem);
		}

		pthread_mutex_unlock(&mutex_writecount);

		sem_wait(&writer_sem);

		// write_data(); //< Write on the database

		sem_post(&writer_sem);

		pthread_mutex_lock(&mutex_writecount);
		writecount--;
		if (writecount == 0)
		{
			sem_post(&reader_sem);
		}

		pthread_mutex_unlock(&mutex_writecount);

		i++;
	}

	return (NULL);
}

void run_reader_writer(int nbr_readers, int nbr_writers)
{
	int err; //< Variable used to verify the eventual error.
	pthread_t *threads = malloc(sizeof(pthread_t) * (nbr_readers + nbr_writers));

	// Initialize the mutex_rw
	err = pthread_mutex_init(&mutex_rw, NULL);
	if (err != 0)
	{
		error(err, "Mutex Initialization (pthread_mutex_init())");
	}
	err = pthread_mutex_init(&mutex_readcount, NULL);
	if (err != 0)
	{
		error(err, "Mutex Read Initialization (pthread_mutex_init())");
	}
	err = pthread_mutex_init(&mutex_writecount, NULL);
	if (err != 0)
	{
		error(err, "Mutex Write Initialization (pthread_mutex_init())");
	}

	// Initialize the semaphore
	if (sem_init(&reader_sem, 0, 1) == -1)
	{
		perror("Semaphore Initialization (sem_init())");
		exit(EXIT_FAILURE);
	}
	if (sem_init(&writer_sem, 0, 1) == -1)
	{
		perror("Semaphore Initialization (sem_init())");
		exit(EXIT_FAILURE);
	}
	
	int i, j;
	for (i = 0; i < nbr_readers; i++)
	{
		err = pthread_create(&threads[i], NULL, reader, NULL);
		if (err != 0)
        {
            error(err, "Thread(s) Creation Reader (pthread_create())");
        }
	}

	for (j = 0; j < nbr_writers; j++)
	{
		err = pthread_create(&threads[i + j], NULL, writer, NULL);
		if (err != 0)
        {
            error(err, "Thread(s) Creation Writer (pthread_create())");
        }
	}

	for (i = 0; i < nbr_readers + nbr_writers; i++)
	{
		err = pthread_join(threads[i], NULL);
		if (err != 0)
        {
            error(err, "Thread(s) Join (pthread_join())");
        }
	}
	
	// Destroy the mutex_rw
	err = pthread_mutex_destroy(&mutex_rw);
	if (err != 0)
	{
		error(err, "Mutex Destruction (pthread_mutex_destroy())");
	}
	err = pthread_mutex_destroy(&mutex_readcount);
	if (err != 0)
	{
		error(err, "Mutex Read Destruction (pthread_mutex_destroy())");
	}
	err = pthread_mutex_destroy(&mutex_writecount);
	if (err != 0)
	{
		error(err, "Mutex Write Destruction (pthread_mutex_destroy())");
	}

	free(threads);
}
