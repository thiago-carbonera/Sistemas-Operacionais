# Makefile para compilar e executar o jantar_dos_filosofos do exercício 2
TARGET = jantar_dos_filosofos

CC = gcc
CFLAGS = -Wall -pthread

SRC = jantar_dos_filosofos.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
