#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/socket_tradutor"
#define BUFFER_SIZE 256

int main() {
    int sock;
    struct sockaddr_un addr;
    char buffer[BUFFER_SIZE];

    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH);

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect");
        exit(1);
    }

    printf("Conectado ao tradutor.\nDigite 'NO-NO' para sair.\n");

    while (1) {
        printf("Entrada (ex: pt-en:cachorro): ");
        fflush(stdout);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            fprintf(stderr, "Erro ao ler entrada\n");
            break;
        }
        buffer[strcspn(buffer, "\n")] = '\0'; // remove '\n'

        ssize_t w = write(sock, buffer, strlen(buffer));
        if (w < 0) perror("write");

        if (strcmp(buffer, "NO-NO") == 0)
            break;

        char resposta[BUFFER_SIZE];
        ssize_t len = read(sock, resposta, sizeof(resposta) - 1);
        if (len <= 0) {
            printf("Desconectado.\n");
            break;
        }

        resposta[len] = '\0';
        printf("Resposta: %s\n", resposta);
    }

    close(sock);
    return 0;
}
