#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5
#define ESQUERDA (i + N - 1) % N
#define DIREITA (i + 1) % N

enum { PENSANDO, FAMINTO, COMENDO } estado[N];
pthread_mutex_t mutex;
pthread_cond_t cond[N];

void testar(int i) {
    if (estado[i] == FAMINTO &&
        estado[ESQUERDA] != COMENDO &&
        estado[DIREITA] != COMENDO) {
        estado[i] = COMENDO;
        pthread_cond_signal(&cond[i]);
    }
}

void pegar_garfos(int i) {
    pthread_mutex_lock(&mutex);
    estado[i] = FAMINTO;
    printf("Filósofo %d está com fome.\n", i);
    testar(i);
    while (estado[i] != COMENDO)
        pthread_cond_wait(&cond[i], &mutex);
    printf("Filósofo %d começou a comer.\n", i);
    pthread_mutex_unlock(&mutex);
}

void devolver_garfos(int i) {
    pthread_mutex_lock(&mutex);
    estado[i] = PENSANDO;
    printf("Filósofo %d terminou de comer e voltou a pensar.\n", i);
    testar(ESQUERDA);
    testar(DIREITA);
    pthread_mutex_unlock(&mutex);
}

void *filosofo(void *arg) {
    int i = *((int *)arg);
    while (1) {
        printf("Filósofo %d está pensando...\n", i);
        sleep(rand() % 3 + 1);
        pegar_garfos(i);
        sleep(rand() % 3 + 1);
        devolver_garfos(i);
    }
    return NULL;
}

int main() {
    pthread_t threads[N];
    int ids[N];

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < N; i++) {
        pthread_cond_init(&cond[i], NULL);
        estado[i] = PENSANDO;
        ids[i] = i;
        pthread_create(&threads[i], NULL, filosofo, &ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < N; i++) {
        pthread_cond_destroy(&cond[i]);
    }

    return 0;
}

