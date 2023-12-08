#include "../../headers/algorithmes/produc_conso.h"
#include "../../headers/attente_active/my_mutex.h"
#include "../../headers/attente_active/my_semaphore.h"

#define TAILLE_BUFFER 8
#define PRODUITS 8192
#define MAX_INT 100
#define MIN_INT 1

int buffer[TAILLE_BUFFER];
int debut = 0, fin = 0;

// Choose between my_mutex and pthread_mutex
#ifdef MYMUTEX_H
my_mutex_t mutex;
#else
pthread_mutex_t mutex;
#endif

// Choose between my_semaphore and pthread_semaphore
#ifdef MYSEMAPHORE_H
my_semaphore_t plein, vide;
#else
sem_t plein, vide;
#endif

void conso(int element)
{
	return;
}

void *producteur(void *arg)
{
	int element;

	for (int i = 0; i < PRODUITS; i++)
	{
		// random number
		element = rand() % (MAX_INT - MIN_INT + 1) + MIN_INT;

		#ifdef MYSEMAPHORE_H
		my_semaphore_wait(&vide);
		#else
		sem_wait(&vide);
		#endif
		
		#ifdef MYMUTEX_H
		TATAS_lock(&mutex);
		#else
		pthread_mutex_lock(&mutex);
		#endif

		// mettre elem dans buffer
		buffer[fin] = element;

		// on met a jour
		fin = (fin + 1) % TAILLE_BUFFER;

		#ifdef MYMUTEX_H
		my_unlock(&mutex);
		#else
		pthread_mutex_unlock(&mutex);
		#endif

		#ifdef MYSEMAPHORE_H
		my_semaphore_post(&plein);
		#else
		sem_post(&plein);
		#endif

		// simule temps de traitement
		for (int j = 0; j < 10000; j++)
		{
		}

		// printf("elem produit\n", element);
	}

	return (NULL);
}

void *consommateur(void *arg)
{
	int element;

	for (int i = 0; i < PRODUITS; i++)
	{
		#ifdef MYSEMAPHORE_H
		my_semaphore_wait(&plein);
		#else
		sem_wait(&plein);
		#endif

		#ifdef MYMUTEX_H
		TATAS_lock(&mutex);
		#else
		pthread_mutex_lock(&mutex);
		#endif

		// Retirer un elem du buffer
		element = buffer[debut];

		// Utilise l'element
		conso(element);

		// on met a jour
		debut = (debut + 1) % TAILLE_BUFFER;

		#ifdef MYMUTEX_H
		my_unlock(&mutex);
		#else
		pthread_mutex_unlock(&mutex);
		#endif

		#ifdef MYSEMAPHORE_H
		my_semaphore_post(&vide);
		#else
		sem_post(&vide);
		#endif

		// simule temps de traintement
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
	#ifdef MYMUTEX_H
	my_mutex_init(&mutex);
	#else
	pthread_mutex_init(&mutex, NULL);
	#endif

	#ifdef MYSEMAPHORE_H
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
	#ifdef MYMUTEX_H
	#else
	pthread_mutex_destroy(&mutex);
	#endif

	#ifdef MYSEMAPHORE_H
	#else
	sem_destroy(&plein);
	sem_destroy(&vide);
	#endif
}
