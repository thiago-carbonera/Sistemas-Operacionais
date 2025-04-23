#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void criar_filhos(int nivel, int max_nivel) {
   if (nivel >= max_nivel) return;

   pid_t pid1 = fork();
   if (pid1 == 0) {
       printf("Nível %d | PID: %d | PPID: %d\n", nivel + 1, getpid(), getppid());
       criar_filhos(nivel + 1, max_nivel);
       exit(0); // filho termina
   }

   pid_t pid2 = fork();
   if (pid2 == 0) {
       printf("Nível %d | PID: %d | PPID: %d\n", nivel + 1, getpid(), getppid());
       criar_filhos(nivel + 1, max_nivel);
       exit(0); // filho termina
   }

   // Pai espera os filhos
   wait(NULL);
   wait(NULL);
}

int main(int argc, char *argv[]) {
   if (argc != 2) {
       fprintf(stderr, "Uso: %s <niveis>\n", argv[0]);
       exit(1);
   }

   int niveis = atoi(argv[1]);
   printf("Processo raiz | PID: %d\n", getpid());

   criar_filhos(0, niveis);

   return 0;
}