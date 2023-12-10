#include "../../headers/algorithmes/produc_conso.h"
#include "../../headers/attente_active/my_mutex.h"
#include "../../headers/attente_active/my_semaphore.h"

/**
 * @file produc_conso.c
 * @brief The file produc_conso.c is used to run the producer-consumer algorithm.
 *
 * For now we use the POSIX mutexes and semaphores.
 *
 * @see https://sites.uclouvain.be/SystInfo/notes/Theorie/Threads/coordination.html#probleme-des-producteurs-consommateurs
 */

#define TAILLE_BUFFER 8
#define PRODUITS 8192
#define MAX_INT 100
#define MIN_INT 1

int buffer[TAILLE_BUFFER]; //< The "store" of the producer-consumer algorithm.
int debut = 0, fin = 0;

// Choose between my_mutex and pthread_mutex
#ifndef MYMUTEX_H
my_mutex_t mutex;
#else
pthread_mutex_t mutex;
#endif

// Choose between my_semaphore and pthread_semaphore
#ifndef MYSEMAPHORE_H
my_semaphore_t plein, vide;
#else
sem_t plein, vide;
#endif

/**
 * @brief Function to simulate the consumption of an element.
 *
 * @param element The element to consume.
 */
void conso(int element)
{
	return;
}

/**
 * @brief The function that will be executed by the producer threads.
 *
 * @param arg Nothing to import.
 * @return void*
 */
void *producteur(void *arg)
{
	int element;

	for (int i = 0; i < PRODUITS; i++)
	{
		// Random number
		element = rand() % (MAX_INT - MIN_INT + 1) + MIN_INT;

#ifndef MYSEMAPHORE_H
		my_semaphore_wait(&vide);
#else
		sem_wait(&vide);
#endif

#ifndef MYMUTEX_H
		TAS_lock(&mutex);
#else
		pthread_mutex_lock(&mutex);
#endif

		// Mettre elem dans buffer
		buffer[fin] = element;

		// On met a jour
		fin = (fin + 1) % TAILLE_BUFFER;

#ifndef MYMUTEX_H
		my_unlock(&mutex);
#else
		pthread_mutex_unlock(&mutex);
#endif

#ifndef MYSEMAPHORE_H
		my_semaphore_post(&plein);
#else
		sem_post(&plein);
#endif

		// Simule le temps de traitement
		for (int j = 0; j < 10000; j++)
		{
		}

		// printf("elem produit\n", element);
	}

	return (NULL);
}

/**
 * @brief The function that will be executed by the consumer threads.
 *
 * @param arg Nothing to import.
 * @return void*
 */
void *consommateur(void *arg)
{
	int element;

	for (int i = 0; i < PRODUITS; i++)
	{
#ifndef MYSEMAPHORE_H
		my_semaphore_wait(&plein);
#else
		sem_wait(&plein);
#endif

#ifndef MYMUTEX_H
		TAS_lock(&mutex);
#else
		pthread_mutex_lock(&mutex);
#endif

		// Retirer un elem du buffer
		element = buffer[debut];

		// Utilise l'element
		conso(element);

		// On met a jour
		debut = (debut + 1) % TAILLE_BUFFER;

#ifndef MYMUTEX_H
		my_unlock(&mutex);
#else
		pthread_mutex_unlock(&mutex);
#endif

#ifndef MYSEMAPHORE_H
		my_semaphore_post(&vide);
#else
		sem_post(&vide);
#endif

		// Simule temps de traintement
		for (int j = 0; j < 10000; j++)
		{
		}

		// printf("élem consomé: %d\n", element);
	}

	return (NULL);
}

void run_produc_conso(int nb_producteurs, int nb_consommateurs)
{
	pthread_t threads_prod[nb_producteurs], threads_cons[nb_consommateurs];

// inti semaphores
#ifndef MYMUTEX_H
	my_mutex_init(&mutex);
#else
	pthread_mutex_init(&mutex, NULL);
#endif

#ifndef MYSEMAPHORE_H
	my_semaphore_init(&plein, 0);
	my_semaphore_init(&vide, TAILLE_BUFFER);
#else
	sem_init(&plein, 0, 0);
	sem_init(&vide, 0, TAILLE_BUFFER);
#endif

	// crée le thread producer
	for (int i = 0; i < nb_producteurs; i++)
	{
		pthread_create(&threads_prod[i], NULL, producteur, NULL);
	}

	// Crée les threads consommateurs
	for (int i = 0; i < nb_consommateurs; i++)
	{
		pthread_create(&threads_cons[i], NULL, consommateur, NULL);
	}

	// Attentla fin des threads producteurs
	for (int i = 0; i < nb_producteurs; i++)
	{
		pthread_join(threads_prod[i], NULL);
	}

	// Attent la fin des threads consommateurs
	for (int i = 0; i < nb_consommateurs; i++)
	{
		pthread_join(threads_cons[i], NULL);
	}

// DESTROY SEMAPHORES
#ifndef MYMUTEX_H
#else
	pthread_mutex_destroy(&mutex);
#endif

#ifndef MYSEMAPHORE_H
#else
	sem_destroy(&plein);
	sem_destroy(&vide);
#endif
}
