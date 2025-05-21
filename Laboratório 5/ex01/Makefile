# Makefile para compilar e executar cliente e servidor do exercício 1

CC = gcc
CFLAGS = -Wall
TARGETS = cliente servidor
FIFO = meu_fifo

all: $(TARGETS)

cliente: cliente.c
	$(CC) $(CFLAGS) -o cliente cliente.c

servidor: servidor.c
	$(CC) $(CFLAGS) -o servidor servidor.c

run: all mkfifo
	@echo "Abrindo terminal para o servidor..."
	gnome-terminal -- bash -c "./servidor; exec bash"
	sleep 1
	@echo "Abrindo terminal para o cliente..."
	gnome-terminal -- bash -c "./cliente; exec bash"

mkfifo:
	@if [ ! -p $(FIFO) ]; then \
		echo "Criando FIFO '$(FIFO)'..."; \
		mkfifo $(FIFO); \
	fi

clean:
	rm -f $(TARGETS) $(FIFO)

