# Exercício 1 - Comunicação entre Processos com FIFO

## Descrição

Esse exercício demonstra a comunicação entre dois processos usando FIFO (named pipe) no Linux.

`cliente.c`: Lê strings digitadas pelo usuário e envia para o FIFO.
`servidor.c`: Lê strings do FIFO, calcula e exibe:
  - String recebida
  - Tamanho
  - Número de vogais
  - Número de consoantes
  - Número de espaços

O FIFO é criado automaticamente com o nome `meu_fifo` ao executar `make run`.
O cliente termina ao digitar a palavra `sair`, encerrando também o servidor.


## Compilação e Execução

Para compilar os programas:

```bash
make
```

Para limpar os arquivos binários e o FIFO:

```bash
make clean
```

## Autor

Thiago Riemma Carbonera 
21 de Maio de 2025
