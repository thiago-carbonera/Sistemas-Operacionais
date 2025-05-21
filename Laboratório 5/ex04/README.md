# Exercício 4 - Servidor de Tradução com Sockets UNIX e Processos

## Descrição

Este exercício demonstra como implementar um **servidor de tradução** em C utilizando **sockets UNIX** e **processos** para atender múltiplos clientes simultaneamente no Linux.

O programa `servidor.c` executa as seguintes tarefas:
- Cria um socket UNIX do tipo stream e associa a um caminho no sistema de arquivos.
- Aceita conexões de múltiplos clientes, criando um novo processo (`fork`) para cada cliente conectado.
- Cada cliente pode enviar requisições de tradução no formato `origem-destino:palavra` (exemplo: `pt-en:cachorro`).
- O servidor procura a tradução no dicionário interno e retorna a palavra traduzida, ou uma mensagem de erro se não encontrar.
- O cliente pode encerrar a conexão enviando o comando `NO-NO`.
- O servidor trata erros de formato e de tradução, respondendo com mensagens apropriadas.
- Ao final, o servidor libera o socket do sistema de arquivos.

O programa `cliente.c` executa as seguintes tarefas:
- Conecta-se ao servidor de tradução via socket UNIX.
- Permite ao usuário digitar requisições de tradução no formato `origem-destino:palavra`.
- Envia a requisição ao servidor e exibe a resposta recebida (tradução ou mensagem de erro).
- O usuário pode encerrar a conexão digitando `NO-NO`.

## Compilação e Execução

Para compilar os programas:
```bash
make
```

Executar o servidor:
```bash
./servidor
```

Executar o cliente (em outro terminal):
```bash
./cliente
```

O servidor ficará aguardando conexões de clientes no caminho `/tmp/socket_tradutor`.

Para limpar os arquivos binários e o socket:
```bash
make clean
```

O cliente pode ser testado enviando mensagens no formato esperado e recebendo as traduções ou mensagens de erro do servidor.

## Autor

Thiago Riemma Carbonera  
21 de Maio de 2025