#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_NAME "meu_fifo"
#define MAX_LEN 256

int main() {
    char buffer[MAX_LEN];

    // Abertura do FIFO
    int fd = open(FIFO_NAME, O_WRONLY);
    if (fd < 0) {
        perror("Erro ao abrir FIFO para escrita");
        exit(EXIT_FAILURE);
    }

    // Loop para ler strings do usuário
    while (1) {
        printf("Digite uma string (ou 'sair' para encerrar): ");
        fgets(buffer, MAX_LEN, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remover \n

        write(fd, buffer, strlen(buffer) + 1);

        if (strcmp(buffer, "sair") == 0)
            break;
    }

    // Encerramento do FIFO
    close(fd);
    return 0;
}
