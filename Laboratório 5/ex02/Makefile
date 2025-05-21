# Makefile para compilar e executar o signal_graceful do exercício 2

TARGET = signal_graceful
CC = gcc
CFLAGS = -Wall -O2
SRC = signal_graceful.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
