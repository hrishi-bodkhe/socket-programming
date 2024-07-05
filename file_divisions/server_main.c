#include "socket.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SERVER_PORT 3490
#define SERVER_ADDRESS "127.0.0.1"

int main(){
	int sock_fd = create_socket(AF_INET, SOCK_STREAM, 0);
	
	bind_socket(sock_fd, SERVER_PORT, 4, SERVER_ADDRESS);

	listen_socket(sock_fd, 10);
	
	printf("Server: Listening on Port %d\n", SERVER_PORT);

	printf("Server: Waiting for connections...\n");

	int i = 0;

	while(i < 4){
		int client_fd = accept_connection(sock_fd, 4);

		handle_client(client_fd);
		++i;
	}

	/*

	int client_fd =	accept_connection(sock_fd, 4); 

	char buffer[1024] = {0};
	read_msg(client_fd, buffer, sizeof(buffer));
	printf("Received Message from client: %s\n", buffer);

	char *message = "Hello Client!";
	write_msg(client_fd, message);
	printf("Message sent to client.");

	close(client_fd);
	*/
	close(sock_fd);

	return 0;
}
