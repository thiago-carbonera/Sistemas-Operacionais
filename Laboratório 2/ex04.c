#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define MAX_ARGS 64
#define MAX_LINE 256

void parse_comando(char *linha, char **args, int *background) {
   int i = 0;
   *background = 0;

   // Quebrar a linha em tokens
   args[i] = strtok(linha, " \n");
   while (args[i] != NULL) {
       if (strcmp(args[i], "&") == 0) {
           *background = 1;
           args[i] = NULL;
           break;
       }
       i++;
       args[i] = strtok(NULL, " \n");
   }
}

int main() {
   char linha[MAX_LINE];
   char *args[MAX_ARGS];
   int background;

   while (1) {
       printf("myshell> ");
       fflush(stdout);

       if (!fgets(linha, sizeof(linha), stdin)) {
           break; 
       }

       parse_comando(linha, args, &background);

       if (args[0] == NULL) continue; // comando vazio

       if (strcmp(args[0], "exit") == 0) {
           break;
       }

       pid_t pid = fork();
       if (pid < 0) {
           perror("Erro no fork");
       } else if (pid == 0) {
           // processo filho
           execvp(args[0], args);
           perror("execvp falhou");
           exit(1);
       } else {
           if (!background) {
               waitpid(pid, NULL, 0); 
           } else {
               printf("Processo em segundo plano: PID %d\n", pid);
           }
       }
   }

   return 0;
}