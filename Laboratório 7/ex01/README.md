# Exercício 1 - Problema dos Leitores e Escritores Usando Semáforos

## Descrição

Este exercício demonstra como implementar a solução clássica do **problema dos leitores e escritores** em C utilizando **threads** (`pthread`) e **semáforos** (`semaphore.h`) para sincronização no Linux.

O programa `leitores_escritores.c` executa as seguintes tarefas:
- Cria múltiplas threads leitoras e escritoras.
- Utiliza dois semáforos:
  - `mutex`: protege o acesso à variável que conta o número de leitores ativos.
  - `db`: garante acesso exclusivo à base de dados para escritores.
- Leitores podem acessar a base de dados simultaneamente, desde que não haja escritores ativos.
- Escritores têm acesso exclusivo à base de dados, bloqueando leitores enquanto escrevem.
- Cada thread leitora simula a leitura e espera um tempo aleatório antes de tentar ler novamente.
- Cada thread escritora simula o pensamento, realiza a escrita exclusiva e espera um tempo aleatório antes de tentar escrever novamente.
- O programa garante que não há condições de corrida e que a sincronização entre leitores e escritores é respeitada.

## Compilação e Execução

Para compilar o programa:
```bash
make
```

Executar o programa:
```bash
./leitores_escritores
```

O programa exibirá no terminal as ações dos leitores e escritores, mostrando a sincronização entre as threads.

Para limpar os arquivos binários:
```bash
make clean
```

## Autor

Thiago Riemma Carbonera  
26 de Maio de 2025