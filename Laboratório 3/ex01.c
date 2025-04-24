#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define TAM 100  // Tamanho do vetor

// Estrutura para passar parâmetros para as threads
typedef struct {
    int *vetor;
    int inicio, fim;
    int alvo;
    int *resultados;
} ThreadData;

// Função que cada thread vai executar para procurar o valor
void *localiza_valor(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int *vetor = data->vetor;
    int inicio = data->inicio;
    int fim = data->fim;
    int alvo = data->alvo;

    int encontrou = 0;
    // Cada thread procura o valor no intervalo designado
    for (int i = inicio; i < fim; i++) {
        if (vetor[i] == alvo) {
            if (!encontrou) {
                printf("Thread PID %d encontrou o valor nas posições: ", getpid());
                encontrou = 1;
            }
            printf("%d ", i);
        }
    }

    if (encontrou) {
        printf("\n");
    }
    
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <número de threads> <valor a buscar>\n", argv[0]);
        exit(1);
    }

    int n_threads = atoi(argv[1]);
    int alvo = atoi(argv[2]);

    if (n_threads <= 0) {
        fprintf(stderr, "Número de threads deve ser maior que zero.\n");
        exit(1);
    }

    int vetor[TAM];
    srand(time(NULL));

    // Gerar vetor aleatório
    printf("Vetor gerado:\n");
    for (int i = 0; i < TAM; i++) {
        vetor[i] = rand() % 20;  // valores entre 0 e 19
        printf("%d ", vetor[i]);
    }
    printf("\n\n");

    // Número de elementos que cada thread irá processar
    int segmento = TAM / n_threads;

    pthread_t threads[n_threads];
    ThreadData dados[n_threads];

    // Criar as threads
    for (int i = 0; i < n_threads; i++) {
        dados[i].vetor = vetor;
        dados[i].inicio = i * segmento;
        dados[i].fim = (i == n_threads - 1) ? TAM : (i + 1) * segmento;  // Última thread pega o restante
        dados[i].alvo = alvo;

        pthread_create(&threads[i], NULL, localiza_valor, (void *)&dados[i]);
    }

    // Esperar as threads terminarem
    for (int i = 0; i < n_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
