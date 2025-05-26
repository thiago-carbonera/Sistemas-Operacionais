#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N_LEITORES 5
#define N_ESCRITORES 2

sem_t mutex;  // Protege acesso à variável rc
sem_t db;     // Controla o acesso à base de dados
int rc = 0;   // Contador de leitores ativos

// Função leitor
void *leitor(void *arg) {
    int id = *((int *)arg);
    while (1) {
        sem_wait(&mutex);
        rc++;
        if (rc == 1) sem_wait(&db); // Primeiro leitor bloqueia escritores
        sem_post(&mutex);

        printf("Leitor %d está lendo...\n", id);
        sleep(rand() % 3 + 1);

        sem_wait(&mutex);
        rc--;
        if (rc == 0) sem_post(&db); // Último leitor libera escritores
        sem_post(&mutex);

        printf("Leitor %d terminou de ler.\n", id);
        sleep(rand() % 3 + 1); // Espera antes de tentar ler novamente
    }
    return NULL;
}

// Função escritor: Escritor espera um tempo, adquire acesso exclusivo à base de dados, escreve, libera o acesso e espera novamente.
void *escritor(void *arg) {
    int id = *((int *)arg);
    while (1) {
        printf("Escritor %d está pensando...\n", id);
        sleep(rand() % 5 + 2);

        sem_wait(&db); // Escritor adquire acesso exclusivo
        printf("Escritor %d está escrevendo!\n", id);
        sleep(rand() % 3 + 2);
        printf("Escritor %d terminou de escrever.\n", id);
        sem_post(&db);

        sleep(rand() % 4 + 1);
    }
    return NULL;
}

int main() {
    // Inicialização dos semáforos e criação das threads
    pthread_t leitores[N_LEITORES], escritores[N_ESCRITORES];
    int ids_leitores[N_LEITORES], ids_escritores[N_ESCRITORES];

    sem_init(&mutex, 0, 1);
    sem_init(&db, 0, 1);

    // Criação das threads de leitores e escritores
    for (int i = 0; i < N_LEITORES; i++) {
        ids_leitores[i] = i + 1;
        pthread_create(&leitores[i], NULL, leitor, &ids_leitores[i]);
    }
    
    for (int i = 0; i < N_ESCRITORES; i++) {
        ids_escritores[i] = i + 1;
        pthread_create(&escritores[i], NULL, escritor, &ids_escritores[i]);
    }

    // Espera pelas threads terminarem 
    for (int i = 0; i < N_LEITORES; i++) {
        pthread_join(leitores[i], NULL);
    }
    for (int i = 0; i < N_ESCRITORES; i++) {
        pthread_join(escritores[i], NULL);
    }

    // Destruição dos semáforos
    sem_destroy(&mutex);
    sem_destroy(&db);
    return 0;
}
