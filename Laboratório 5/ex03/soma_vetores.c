#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/wait.h>

#define SHM_NAME "/shm_vetores"

typedef struct {
    int start;
    int end;
} Intervalo;

// Função para imprimir erro e sair
void erro(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int numElementos, numProcessos;
    
    // Fazer a leitura dos parâmetros
    printf("Digite o número de elementos: ");
    // Para scanf:
    if (scanf("%d", &numElementos) != 1) {
        fprintf(stderr, "Erro ao ler numElementos\n");
        return 1;
    }
    printf("Digite o número de processos: ");
    // Para scanf:
    if (scanf("%d", &numProcessos) != 1) {
        fprintf(stderr, "Erro ao ler numProcessos\n");
        return 1;
    }

    if (numElementos <= 0 || numProcessos <= 0 || numProcessos > numElementos) {
        fprintf(stderr, "Parâmetros inválidos.\n");
        return 1;
    }

    size_t totalSize = sizeof(int) * numElementos * 3 + sizeof(int) * numProcessos;

    // Criar memória compartilhada
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0600);
    if (shm_fd == -1) erro("shm_open");

    if (ftruncate(shm_fd, totalSize) == -1) erro("ftruncate");

    void *ptr = mmap(NULL, totalSize, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) erro("mmap");

    // Iniciar os vetores
    int *V1 = (int *) ptr;
    int *V2 = V1 + numElementos;
    int *V3 = V2 + numElementos;
    int *sinal = V3 + numElementos;

    // Preencher vetores V1 e V2 com valores simples
    for (int i = 0; i < numElementos; i++) {
        V1[i] = i;
        V2[i] = 2 * i;
    }

    // Criar pipes
    int pipes[numProcessos][2];

    for (int i = 0; i < numProcessos; i++) {
        if (pipe(pipes[i]) == -1) erro("pipe");
    }

    // Criar processos filhos
    for (int i = 0; i < numProcessos; i++) {
        pid_t pid = fork();
        if (pid < 0) erro("fork");

        if (pid == 0) {  // Processo filho
            close(pipes[i][1]); // Fecha escrita

            Intervalo intervalo;
            // Para read:
            ssize_t r = read(pipes[i][0], &intervalo, sizeof(Intervalo));
            if (r != sizeof(Intervalo)) {
                fprintf(stderr, "Erro ao ler intervalo do pipe\n");
                exit(1);
            }

            for (int j = intervalo.start; j < intervalo.end; j++) {
                V3[j] = V1[j] + V2[j];
            }

            sinal[i] = 1;

            close(pipes[i][0]);
            munmap(ptr, totalSize);
            close(shm_fd);
            exit(0);
        }

        close(pipes[i][0]); // Pai fecha leitura
    }

    // Pai distribui trabalho
    int elementosPorFilho = numElementos / numProcessos;
    for (int i = 0; i < numProcessos; i++) {
        Intervalo intervalo;
        intervalo.start = i * elementosPorFilho;
        intervalo.end = (i == numProcessos - 1) ? numElementos : intervalo.start + elementosPorFilho;
        // Para write:
        ssize_t w = write(pipes[i][1], &intervalo, sizeof(Intervalo));
        if (w != sizeof(Intervalo)) {
            fprintf(stderr, "Erro ao escrever intervalo no pipe\n");
            exit(1);
        }
        close(pipes[i][1]);
    }

    // Pai aguarda os filhos terminarem
    int concluidos = 0;
    while (concluidos < numProcessos) {
        sleep(1);
        concluidos = 0;
        for (int i = 0; i < numProcessos; i++) {
            if (sinal[i] == 1) concluidos++;
        }
    }

    // Imprime V1
    printf("V1 = [");
    for (int i = 0; i < numElementos; i++) {
        printf("%d%s", V1[i], (i == numElementos - 1) ? "] + " : ", ");
    }

    // Imprime V2
    printf("V2 = [");
    for (int i = 0; i < numElementos; i++) {
        printf("%d%s", V2[i], (i == numElementos - 1) ? "] =\n" : ", ");
    }

    // Imprime o resultado V3
    printf("V3 = [");
    for (int i = 0; i < numElementos; i++) {
        printf("%d%s", V3[i], (i == numElementos - 1) ? "]\n" : ", ");
    }

    // Limpeza
    munmap(ptr, totalSize);
    close(shm_fd);
    shm_unlink(SHM_NAME);

    for (int i = 0; i < numProcessos; i++) wait(NULL);

    return 0;
}
