# Exercício 2 - Jantar dos Filósofos Usando Threads, Mutex e Variáveis de Condição

## Descrição

Este exercício demonstra como implementar a solução clássica do **problema do jantar dos filósofos** em C utilizando **threads** (`pthread`), **mutex** e **variáveis de condição** para sincronização no Linux.

O programa `jantar_dos_filosofos.c` executa as seguintes tarefas:
- Cria 5 threads, cada uma representando um filósofo.
- Cada filósofo alterna entre pensar e tentar comer.
- Para comer, o filósofo precisa pegar os dois garfos (recursos compartilhados) ao seu lado.
- Utiliza um mutex global para proteger o acesso ao estado dos filósofos e um vetor de variáveis de condição para controlar quando cada filósofo pode comer.
- Cada filósofo só começa a comer se seus vizinhos não estiverem comendo, evitando condições de corrida e deadlocks.
- Após comer, o filósofo devolve os garfos e sinaliza aos vizinhos que podem tentar comer.
- O programa exibe no terminal o estado de cada filósofo (pensando, com fome, comendo) em tempo real.

## Compilação e Execução

Para compilar o programa:
```bash
make
```

Executar o programa:
```bash
./jantar_dos_filosofos
```

O programa exibirá no terminal as ações dos filósofos, mostrando a sincronização e a solução do problema de concorrência.

Para limpar os arquivos binários:
```bash
make clean
```

## Autor

Thiago Riemma Carbonera  
26 de Maio de 2025