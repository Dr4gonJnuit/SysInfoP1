#include "../headers/produc_conso.h"

#define TAILLE_BUFFER 8
#define PRODUITS 8192
#define MAX_INT 100
#define MIN_INT 1

int buffer[TAILLE_BUFFER];
int debut = 0, fin = 0;

pthread_mutex_t mutex;
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
		pthread_mutex_lock(&mutex);

		// mettre elem dans buffer
		buffer[fin] = element;

		// on met a jour
		fin = (fin + 1) % TAILLE_BUFFER;

		pthread_mutex_unlock(&mutex);
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
		pthread_mutex_lock(&mutex);

		// Retirer un elem du buffer
		element = buffer[debut];

		// Utilise l'element
		conso(element);

		// on met a jour
		debut = (debut + 1) % TAILLE_BUFFER;

		pthread_mutex_unlock(&mutex);
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
	pthread_mutex_init(&mutex, NULL);
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
	pthread_mutex_destroy(&mutex);
	sem_destroy(&plein);
	sem_destroy(&vide);
}
