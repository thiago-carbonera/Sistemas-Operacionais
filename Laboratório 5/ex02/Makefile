# Nome do executável
TARGET = signal_graceful

# Compilador
CC = gcc

# Flags de compilação (pode incluir -Wall para warnings)
CFLAGS = -Wall -O2

# Arquivos-fonte
SRC = signal_graceful.c

# Regra padrão
all: $(TARGET)

# Como construir o binário
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Limpeza de arquivos gerados
clean:
	rm -f $(TARGET)
