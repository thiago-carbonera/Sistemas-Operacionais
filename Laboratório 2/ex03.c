#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#define TAM 100 // tamanho do vetor

int main(int argc, char *argv[]) {
   if (argc != 3) {
       fprintf(stderr, "Uso: %s <número de filhos> <item a buscar>\n", argv[0]);
       exit(1);
   }

   int n_filhos = atoi(argv[1]);
   int alvo = atoi(argv[2]);

   if (n_filhos <= 0) {
       fprintf(stderr, "Número de filhos deve ser maior que zero.\n");
       exit(1);
   }

   int vetor[TAM];
   srand(time(NULL));

   // Gerando vetor aleatório
   printf("Vetor gerado:\n");
   for (int i = 0; i < TAM; i++) {
       vetor[i] = rand() % 20; // valores entre 0 e 19
       printf("%d ", vetor[i]);
   }
   printf("\n\n");

   int encontrado = 0;
   int segmento = TAM / n_filhos;

   for (int i = 0; i < n_filhos; i++) {
       pid_t pid = fork();

       if (pid < 0) {
           perror("Erro ao criar processo");
           exit(1);
       }

       if (pid == 0) {
           int inicio = i * segmento;
           int fim = (i == n_filhos - 1) ? TAM : inicio + segmento;
           int achou = 0;

           for (int j = inicio; j < fim; j++) {
               if (vetor[j] == alvo) {
                   if (!achou) {
                       printf("Filho PID %d encontrou o valor nas posições: ", getpid());
                       achou = 1;
                   }
                   printf("%d ", j);
               }
           }

           if (achou) printf("\n");
           exit(achou ? 1 : 0); // filho retorna 1 se encontrou, e 0 para o contrário
       }
   }

   // Pai espera os filhos e verifica se algum encontrou
   for (int i = 0; i < n_filhos; i++) {
       int status;
       wait(&status);
       if (WIFEXITED(status) && WEXITSTATUS(status) == 1) {
           encontrado = 1;
       }
   }

   if (!encontrado) {
       printf("Pai: valor %d não encontrado por nenhum processo.\n", alvo);
   }

   return 0;
}