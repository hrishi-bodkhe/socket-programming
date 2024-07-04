# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Source files
CLIENT_SRC = client_main.c
SERVER_SRC = server_main.c
COMMON_SRC = socket.c

# Object files
CLIENT_OBJS = $(CLIENT_SRC:.c=.o) socket.o
SERVER_OBJS = $(SERVER_SRC:.c=.o) socket.o

# Executables
CLIENT_EXEC = client
SERVER_EXEC = server

# Default target
all: $(CLIENT_EXEC) $(SERVER_EXEC)

# Rule to create client executable
$(CLIENT_EXEC): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to create server executable
$(SERVER_EXEC): $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile socket.c into socket.o
socket.o: socket.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile client source files into object files
client_main.o: client_main.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile server source files into object files
server_main.o: server_main.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(CLIENT_OBJS) $(SERVER_OBJS) $(CLIENT_EXEC) $(SERVER_EXEC)

# Phony targets
.PHONY: all client server clean

# Compile only the client executable
client: $(CLIENT_EXEC)

# Compile only the server executable
server: $(SERVER_EXEC)
