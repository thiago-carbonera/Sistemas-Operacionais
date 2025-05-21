#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/socket_tradutor"
#define BUFFER_SIZE 256

typedef struct {
    const char *origem;
    const char *destino;
    const char *palavra;
    const char *traducao;
} Traducao;

Traducao dicionario[] = {
    {"pt", "en", "cachorro", "dog"},
    {"pt", "en", "gato", "cat"},
    {"en", "pt", "dog", "cachorro"},
    {"en", "pt", "cat", "gato"},
    {NULL, NULL, NULL, NULL}
};

const char* traduzir(const char *codigo, const char *palavra) {
    char origem[3], destino[3];
    if (sscanf(codigo, "%2[^-]-%2s", origem, destino) != 2)
        return "ERROR:INVALID_FORMAT";

    for (int i = 0; dicionario[i].palavra != NULL; i++) {
        if (strcmp(dicionario[i].origem, origem) == 0 &&
            strcmp(dicionario[i].destino, destino) == 0 &&
            strcmp(dicionario[i].palavra, palavra) == 0) {
            return dicionario[i].traducao;
        }
    }
    return "ERROR:UNKNOWN";
}

void tratar_cliente(int client_sock) {
    char buffer[BUFFER_SIZE];
    while (1) {
        ssize_t bytes = read(client_sock, buffer, sizeof(buffer) - 1);
        if (bytes <= 0) break;
        buffer[bytes] = '\0';

        if (strcmp(buffer, "NO-NO") == 0)
            break;

        char codigo[10], palavra[BUFFER_SIZE];
        if (sscanf(buffer, "%[^:]:%s", codigo, palavra) == 2) {
            const char *resposta = traduzir(codigo, palavra);
            ssize_t w = write(client_sock, resposta, strlen(resposta));
            if (w < 0) perror("write");
        } else {
            const char *erro = "ERROR:INVALID_FORMAT";
            ssize_t w = write(client_sock, erro, strlen(erro));
            if (w < 0) perror("write");
        }
    }
    close(client_sock);
    exit(0);
}

int main() {
    int server_sock;
    struct sockaddr_un addr;

    unlink(SOCKET_PATH); // Remove anterior

    server_sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("socket");
        exit(1);
    }

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH);

    if (bind(server_sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(1);
    }

    listen(server_sock, 5);
    printf("Servidor de tradução iniciado.\n");

    while (1) {
        int client_sock = accept(server_sock, NULL, NULL);
        if (client_sock < 0) {
            perror("accept");
            continue;
        }

        pid_t pid = fork();
        if (pid == 0) {
            close(server_sock);
            tratar_cliente(client_sock);
        } else {
            close(client_sock);
        }
    }

    close(server_sock);
    unlink(SOCKET_PATH);
    return 0;
}
