#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
   if (argc < 2) {
       fprintf(stderr, "Uso: %s <comando> [argumentos...]\n", argv[0]);
       return 1;
   }

   pid_t pid = fork();

   if (pid < 0) {
       perror("Erro ao criar processo");
       return 1;
   }

   if (pid == 0) {
       // Filho: executa o comando
       execvp(argv[1], &argv[1]);
       // Se execvp falhar:
       perror("execvp falhou");
       exit(1);
   } else {
       // Pai: espera o filho
       wait(NULL);
       printf("Processo %s finalizado.\n", argv[1]);
   }

   return 0;
}