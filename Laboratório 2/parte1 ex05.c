#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    while(1) {
        pid_t pid = frok();
        if (pid < 0) {
            perror("fork falhou");
            exit(1);
        } else if (pid == 0) {
            printf("Processo filho criado: PID = %d\n", getpid());
        } else {
            break;
        }
    }
    return 0;
}