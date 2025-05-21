# Exercício 2 - Manipulação de Arquivos e Finalização Graceful com Signals

## Descrição

Esse exercício demonstra como manipular arquivos em C e realizar uma finalização limpa (graceful stop) ao receber sinais do sistema operacional no Linux.

O programa `signal_graceful.c` executa as seguintes tarefas:
- Abre (ou cria) um arquivo chamado `saida.txt` para escrita.
- Escreve linhas no arquivo, simulando uma operação de longa duração.
- E ao receber um sinal SIGINT (Ctrl+C) ou SIGTERM (`kill <PID>`), executa um tratador de sinal que:
  - Escreve uma mensagem de encerramento no arquivo.
  - Fecha corretamente o arquivo.
  - Exibe uma mensagem de finalização no terminal.
- O programa pode ser finalizado de forma segura tanto pelo teclado (Ctrl+C) quanto por comandos do sistema (`kill`).

## Compilação e Execução

Para compilar o programa:
```bash
make
```

Executar o programa:
```bash
./signal_graceful
```

Para finalizar de forma limpa:
- Pressione `Ctrl+C` no terminal **ou**
- Em outro terminal, use `kill <PID>` (o PID é mostrado ao iniciar o programa)

Para limpar os arquivos binários e o FIFO:
```bash
make clean
```

O arquivo `saida.txt` tem todas as linhas escritas e uma mensagem indicando o encerramento seguro.

## Autor

Thiago Riemma Carbonera  
21 de Maio de 2025