#include "../../headers/algorithmes/reader_writer.h"
#include "../../headers/attente_active/my_mutex.h"
#include "../../headers/attente_active/my_semaphore.h"

#define READER_CYCLE 2500
#define WRITER_CYCLE 640

// Choose between my_mutex and pthread_mutex
#ifdef MYMUTEX_H
my_mutex_t mutex_rw;
my_mutex_t mutex_readcount;
my_mutex_t mutex_writecount;
#else
pthread_mutex_t mutex_rw;
pthread_mutex_t mutex_readcount;
pthread_mutex_t mutex_writecount;
#endif

// Choose between my_semaphore and pthread_semaphore
#ifdef MYSEMAPHORE_H
// sem_t db; //< access to the db
my_semaphore_t reader_sem;
my_semaphore_t writer_sem;
#else
// sem_t db; //< access to the db
sem_t reader_sem;
sem_t writer_sem;
#endif

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
		#ifdef MYMUTEX_H
		TATAS_lock(&mutex_rw);
		#else
		pthread_mutex_lock(&mutex_rw);
		#endif

		#ifdef MYSEMAPHORE_H
		my_semaphore_wait(&reader_sem);
		#else
		sem_wait(&reader_sem);
		#endif

		#ifdef MYMUTEX_H
		TATAS_lock(&mutex_readcount);
		#else
		pthread_mutex_lock(&mutex_readcount);
		#endif

		readcount++;
		if (readcount == 1)
		{
			#ifdef MYSEMAPHORE_H
			my_semaphore_wait(&writer_sem);
			#else
			sem_wait(&writer_sem);
			#endif
		}

		#ifdef MYMUTEX_H
		my_unlock(&mutex_readcount);
		#else
		pthread_mutex_unlock(&mutex_readcount);
		#endif

		#ifdef MYSEMAPHORE_H
		my_semaphore_post(&reader_sem);
		#else
		sem_post(&reader_sem);
		#endif

		#ifdef MYMUTEX_H
		my_unlock(&mutex_rw);
		#else
		pthread_mutex_unlock(&mutex_rw);
		#endif

		// read_data(); //< Reading database

		#ifdef MYMUTEX_H
		TATAS_lock(&mutex_readcount);
		#else
		pthread_mutex_lock(&mutex_readcount);
		#endif

		readcount--;
		if (readcount == 0)
		{
			#ifdef MYSEMAPHORE_H
			my_semaphore_post(&writer_sem);
			#else
			sem_post(&writer_sem);
			#endif
		}

		#ifdef MYMUTEX_H
		my_unlock(&mutex_readcount);
		#else
		pthread_mutex_unlock(&mutex_readcount);
		#endif

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

		#ifdef MYMUTEX_H
		TATAS_lock(&mutex_writecount);
		#else
		pthread_mutex_lock(&mutex_writecount);
		#endif

		writecount++;
		if (writecount == 1)
		{
			#ifdef MYSEMAPHORE_H
			my_semaphore_wait(&reader_sem);
			#else
			sem_wait(&reader_sem);
			#endif
		}

		#ifdef MYMUTEX_H
		my_unlock(&mutex_writecount);
		#else
		pthread_mutex_unlock(&mutex_writecount);
		#endif

		#ifdef MYSEMAPHORE_H
		my_semaphore_wait(&writer_sem);
		#else
		sem_wait(&writer_sem);
		#endif

		// write_data(); //< Write on the database

		#ifdef MYSEMAPHORE_H
		my_semaphore_post(&writer_sem);
		#else
		sem_post(&writer_sem);
		#endif

		#ifdef MYMUTEX_H
		TATAS_lock(&mutex_writecount);
		#else
		pthread_mutex_lock(&mutex_writecount);
		#endif

		writecount--;
		if (writecount == 0)
		{
			#ifdef MYSEMAPHORE_H
			my_semaphore_post(&reader_sem);
			#else
			sem_post(&reader_sem);
			#endif
		}

		#ifdef MYMUTEX_H
		my_unlock(&mutex_writecount);
		#else
		pthread_mutex_unlock(&mutex_writecount);
		#endif

		i++;
	}

	return (NULL);
}

void run_reader_writer(int nbr_readers, int nbr_writers)
{
	int err; //< Variable used to verify the eventual error.
	pthread_t *threads = malloc(sizeof(pthread_t) * (nbr_readers + nbr_writers));

	// Initialize the mutex_rw
	#ifdef MYMUTEX_H
	my_mutex_init(&mutex_rw);
	my_mutex_init(&mutex_readcount);
	my_mutex_init(&mutex_writecount);
	#else
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
	#endif

	// Initialize the semaphore
	#ifdef MYSEMAPHORE_H
	my_semaphore_init(&reader_sem, 1);
	my_semaphore_init(&writer_sem, 1);
	#else
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
	#endif
	
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
	#ifdef MYMUTEX_H
	#else
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
	#endif

	// Destroy the semaphore
	#ifdef MYSEMAPHORE_H
	#else
	err = sem_destroy(&reader_sem);
	if (err == -1)
	{
		perror("Semaphore Destruction (sem_destroy())");
		exit(EXIT_FAILURE);
	}
	err = sem_destroy(&writer_sem);
	if (err == -1)
	{
		perror("Semaphore Destruction (sem_destroy())");
		exit(EXIT_FAILURE);
	}
	#endif

	free(threads);
}
