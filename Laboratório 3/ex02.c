#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include "matriz.h"

#define M 1000
#define N 1000
#define ARQ_ENTRADA "matriz_entrada.in"
#define ARQ_SAIDA "resultado_saida.out"

int **matriz;
double media_linhas[M];
double media_colunas[N];
int num_threads;

// Estrutura de dados para passar para as threads
typedef struct {
    int id;
    int total_threads;
} ThreadData;

// Função para calcular médias das linhas (por thread)
void *media_linhas_thread(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int id = data->id;
    int step = data->total_threads;

    for (int i = id; i < M; i += step) {
        double soma = 0;
        for (int j = 0; j < N; j++) {
            soma += matriz[i][j];
        }
        media_linhas[i] = soma / N;
    }

    pthread_exit(NULL);
}

// Função para calcular médias geométricas das colunas (por thread)
void *media_colunas_thread(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int id = data->id;
    int step = data->total_threads;

    for (int j = id; j < N; j += step) {
        double produto = 1.0;
        for (int i = 0; i < M; i++) {
            produto *= matriz[i][j];
        }
        media_colunas[j] = pow(produto, 1.0 / M);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <numero_de_threads>\n", argv[0]);
        return 1;
    }

    num_threads = atoi(argv[1]);
    if (num_threads <= 0) {
        printf("Número de threads inválido!\n");
        return 1;
    }

    srand(time(NULL));
    matriz = create_matrix(M, N);
    generate_elements(matriz, M, N, 99);

    // Salvar matriz gerada
    FILE *fentrada = fopen(ARQ_ENTRADA, "w");
    fprintf(fentrada, "%dx%d\n", M, N);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(fentrada, "%d ", matriz[i][j]);
        }
        fprintf(fentrada, "\n");
    }
    fclose(fentrada);

    // Criar e iniciar threads para linha
    pthread_t *threads_linha = malloc(num_threads * sizeof(pthread_t));
    ThreadData *dados_linha = malloc(num_threads * sizeof(ThreadData));

    for (int i = 0; i < num_threads; i++) {
        dados_linha[i].id = i;
        dados_linha[i].total_threads = num_threads;
        pthread_create(&threads_linha[i], NULL, media_linhas_thread, &dados_linha[i]);
    }

    // Criar e iniciar threads para coluna
    pthread_t *threads_coluna = malloc(num_threads * sizeof(pthread_t));
    ThreadData *dados_coluna = malloc(num_threads * sizeof(ThreadData));

    for (int i = 0; i < num_threads; i++) {
        dados_coluna[i].id = i;
        dados_coluna[i].total_threads = num_threads;
        pthread_create(&threads_coluna[i], NULL, media_colunas_thread, &dados_coluna[i]);
    }

    // Esperar threads terminarem
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads_linha[i], NULL);
        pthread_join(threads_coluna[i], NULL);
    }

    free(threads_linha);
    free(dados_linha);
    free(threads_coluna);
    free(dados_coluna);

    // Gravar resultados
    FILE *fsaida = fopen(ARQ_SAIDA, "w");
    fprintf(fsaida, "Média aritmética das linhas:\n");
    for (int i = 0; i < M; i++) {
        fprintf(fsaida, "Linha %d: %.2f\n", i, media_linhas[i]);
    }

    fprintf(fsaida, "\nMédia geométrica das colunas:\n");
    for (int j = 0; j < N; j++) {
        fprintf(fsaida, "Coluna %d: %.2f\n", j, media_colunas[j]);
    }

    fclose(fsaida);

    printf("Cálculo finalizado com %d threads. Resultados em '%s'.\n", num_threads, ARQ_SAIDA);
    return 0;
}
