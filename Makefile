# Makefile for client-server program

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -g

# Targets
TARGETS = server client

# Default rule
all: $(TARGETS)

# Rule to build the server
server: server.c
	$(CC) $(CFLAGS) server.c -o server

# Rule to build the client
client: client.c
	$(CC) $(CFLAGS) client.c -o client

# Clean rule
clean:
	rm -f $(TARGETS)
