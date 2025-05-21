# Exercício 3 - Soma Paralela de Vetores com Memória Compartilhada e Pipes

## Descrição

Este exercício demonstra como realizar a soma de dois vetores em C utilizando **processos paralelos**, **memória compartilhada** e **pipes** para comunicação entre processos no Linux.

O programa `soma_vetores.c` executa as seguintes tarefas:
- Solicita ao usuário o número de elementos dos vetores e o número de processos a serem utilizados.
- Cria três vetores inteiros (`V1`, `V2`, `V3`) em memória compartilhada.
- Preenche `V1` e `V2` com valores simples.
- Cria múltiplos processos filhos, cada um responsável por somar uma parte dos vetores.
- Utiliza **pipes** para o processo pai informar a cada filho qual intervalo de índices ele deve processar.
- Cada filho realiza a soma parcial e sinaliza sua conclusão.
- O processo pai aguarda todos os filhos terminarem e imprime os vetores e o resultado final.
- Ao final, libera a memória compartilhada e encerra corretamente.

## Compilação e Execução

Para compilar o programa:
```bash
make
```

Executar o programa:
```bash
./soma_vetores
```

Siga as instruções do terminal para informar o número de elementos e de processos.

Para limpar os arquivos binários e a memória compartilhada:
```bash
make clean
```

O resultado exibirá os vetores de entrada e o vetor soma, mostrando o processamento paralelo realizado.

## Autor

Thiago Riemma Carbonera  
21 de Maio de 2025