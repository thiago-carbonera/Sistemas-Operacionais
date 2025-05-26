# Makefile para compilar e executar o leitores_escritores do exercício 1
TARGET = leitores_escritores

CC = gcc
CFLAGS = -Wall -pthread

SRC = leitores_escritores.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
