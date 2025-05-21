#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define FILENAME "saida.txt"

FILE *arquivo = NULL;

// Função tratamento de sinal
void finalizar_gracefully(int sinal) {
    if (arquivo != NULL) {
        // Escrevendo mensagem no arquivo até ser encerrado
        fprintf(arquivo, "\n[Sinal %d recebido: salvando e fechando arquivo]\n", sinal); 
        fclose(arquivo);
        printf("\nArquivo fechado corretamente.\n");
    }
    exit(0);
}

int main() {
    // Registrar tratadores de sinal
    signal(SIGINT, finalizar_gracefully);   // Ctrl+C
    signal(SIGTERM, finalizar_gracefully);  // kill

    arquivo = fopen(FILENAME, "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    printf("Programa iniciado. PID: %d\n", getpid());
    printf("Escrevendo no arquivo '%s'. Pressione Ctrl+C para parar.\n", FILENAME);

    char buffer[100];
    int contador = 1;

    while (1) {
        snprintf(buffer, sizeof(buffer), "Linha %d: escrita contínua\n", contador++);
        fputs(buffer, arquivo);
        fflush(arquivo); // Garante que os dados sejam gravados no disco
        sleep(1);        // Simula trabalho contínuo
    }

    return 0;
}
