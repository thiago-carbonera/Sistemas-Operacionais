CC = gcc
CFLAGS = -Wall -pthread
LDFLAGS = -lm


all: busca_thread matriz_thread

busca_thread: ex01.c
	$(CC) $(CFLAGS) -o busca_thread ex01.c

matriz.o: matriz.c matriz.h
	$(CC) $(CFLAGS) -c matriz.c

matriz_thread: ex02.c matriz.o
	$(CC) $(CFLAGS) -o matriz_thread ex02.c matriz.o $(LDFLAGS)

clean:
	rm -f *.o busca_thread matriz_thread
