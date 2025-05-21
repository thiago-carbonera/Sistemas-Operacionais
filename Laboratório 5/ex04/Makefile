# Makefile para compilar e executar o servidor e o cliente do exercício 4

CC = gcc
CFLAGS = -Wall -O2

all: servidor cliente

servidor: servidor.c
	$(CC) $(CFLAGS) -o servidor servidor.c

cliente: cliente.c
	$(CC) $(CFLAGS) -o cliente cliente.c

clean:
	rm -f servidor cliente
