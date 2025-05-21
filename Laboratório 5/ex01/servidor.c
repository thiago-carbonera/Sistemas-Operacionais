#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_NAME "meu_fifo"
#define MAX_LEN 256

// Contando o número de vogais na string
int contar_vogais(const char *str) {
    int count = 0;
    while (*str) {
        char c = tolower(*str);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            count++;
        str++;
    }
    return count;
}

// Contando o número de consoantes na string
int contar_consoantes(const char *str) {
    int count = 0;
    while (*str) {
        char c = tolower(*str);
        if (isalpha(c) && !(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'))
            count++;
        str++;
    }
    return count;
}

// Contando o número de espaços na string
int contar_espacos(const char *str) {
    int count = 0;
    while (*str) {
        if (*str == ' ')
            count++;
        str++;
    }
    return count;
}

int main() {
    char buffer[MAX_LEN];

    // Abertura da FIFO
    int fd = open(FIFO_NAME, O_RDONLY);
    if (fd < 0) {
        perror("Erro ao abrir FIFO para leitura");
        exit(EXIT_FAILURE);
    }

    // Loop para ler strings da FIFO
    while (1) {
        int bytes = read(fd, buffer, MAX_LEN);
        if (bytes > 0) {
            buffer[bytes] = '\0';

            // Se receber "sair", encerra o loop
            if (strcmp(buffer, "sair") == 0)
                break;

            int len = strlen(buffer);
            int vogais = contar_vogais(buffer);
            int consoantes = contar_consoantes(buffer);
            int espacos = contar_espacos(buffer);

            // Imprimindo os resultados
            printf("\nRecebido: \"%s\"\n", buffer);
            printf("Tamanho: %d\n", len);
            printf("Vogais: %d\n", vogais);
            printf("Consoantes: %d\n", consoantes);
            printf("Espaços: %d\n\n", espacos);
        }
    }

    // Encerramento da FIFO
    close(fd);
    return 0;
}
