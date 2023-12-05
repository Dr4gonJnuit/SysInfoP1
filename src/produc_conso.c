#include "../headers/produc_conso.h"
#include "../headers/my_mutex.h"

#define TAILLE_BUFFER 8
#define PRODUITS 8192
#define MAX_INT 100
#define MIN_INT 1

int buffer[TAILLE_BUFFER];
int debut = 0, fin = 0;

#ifdef MYMUTEX_H
my_mutex mutex;
#else
pthread_mutex_t mutex;
#endif
sem_t plein, vide;

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

		sem_wait(&vide);
		#ifdef MYMUTEX_H
		test_and_set(&mutex);
		#else
		pthread_mutex_lock(&mutex);
		#endif

		// mettre elem dans buffer
		buffer[fin] = element;

		// on met a jour
		fin = (fin + 1) % TAILLE_BUFFER;

		#ifdef MYMUTEX_H
		unlock(&mutex);
		#else
		pthread_mutex_unlock(&mutex);
		#endif
		sem_post(&plein);

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

		sem_wait(&plein);
		#ifdef MYMUTEX_H
		test_and_set(&mutex);
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
		unlock(&mutex);
		#else
		pthread_mutex_unlock(&mutex);
		#endif
		sem_post(&vide);

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
	sem_init(&plein, 0, 0);
	sem_init(&vide, 0, TAILLE_BUFFER);

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
	sem_destroy(&plein);
	sem_destroy(&vide);
}
