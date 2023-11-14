#include "../headers/philosophes.h"

#define CYCLES 10000000 // 10 000 000
#define PHILOSOPHES 5

pthread_t phil[PHILOSOPHES];
sem_t baguette[PHILOSOPHES];

void mange(int id)
{
    printf("Philosophe [%d] mange\n", id);
    for (int i = 0; i < rand(); i++)
    {
        // philosophe mange
    }
}

void *philosophe(void *arg)
{
    int *id = (int *)arg;
    int left = *id;
    int right = (left + 1) % PHILOSOPHES;
    while (true)
    {
        printf("Philosophe [%d] pense\n", *id);

        sem_wait(&baguette[left]);
        printf("Philosophe [%d] possède baguette gauche [%d]\n", *id, left);
        sem_wait(&baguette[right]);
        printf("Philosophe [%d] possède baguette droite [%d]\n", *id, right);

        mange(*id);
        
        sem_post(&baguette[left]);
        printf("Philosophe [%d] a libéré baguette gauche [%d]\n", *id, left);
        sem_post(&baguette[right]);
        printf("Philosophe [%d] a libéré baguette droite [%d]\n", *id, right);
    }
    return (NULL);
}