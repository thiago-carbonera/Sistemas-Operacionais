# Makefile para compilar e executar o soma_vetores do exercício 3

TARGET = soma_vetores
CC = gcc
CFLAGS = -Wall -O2

all: $(TARGET)

$(TARGET): soma_vetores.c
	$(CC) $(CFLAGS) -o $(TARGET) soma_vetores.c

clean:
	rm -f $(TARGET)
