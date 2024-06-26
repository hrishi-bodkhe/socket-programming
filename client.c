#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

#define PORT "3490"
#define SERVER_ADDR "192.168.122.20"

int main(){
	printf("herer");
	struct addrinfo hints, *servinfo;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	int status = getaddrinfo(SERVER_ADDR, PORT, &hints, &servinfo);

	if(status != 0){
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		return 1;
	}
	printf("here1");

	int client_fd;
	// struct addrinfo *p;
	// for(p = servinfo; p != NULL; p = p->ai_next){
	// 	client_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	// 	if(client_fd == -1){
	// 		perror("client: socket");
	// 		continue;
	// 	}

	// 	if(connect(client_fd, p->ai_addr, p->ai_addrlen) == -1){
	// 		close(client_fd);
	// 		perror("client: connect");
	// 		continue;
	// 	}

	// 	break;
	// }

	client_fd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
	printf("here2");
	connect(client_fd, servinfo->ai_addr, servinfo->ai_addrlen);
	printf("here3");

	freeaddrinfo(servinfo);

	// if(p == NULL){
	// 	fprintf(stderr, "client: failed to connect\n");
	// 	return 2;
	// }

	const char *hello = "HELLO FROM CLIENT 1!";

	if(send(client_fd, hello, strlen(hello), 0) == -1){
		perror("send");
		return 3;
	}

	printf("Client: Hello msg sent from client!\n");

	// char buffer[1024];
	// if(recv(client_fd, buffer, sizeof(buffer), 0) == -1){
	// 	perror("recv");
	// 	return 4;
	// }

	// printf("Client1: received '%s'\n", buffer);

	// const char *hello1 = "how are you?";
	// send(client_fd, hello1, strlen(hello1), 0);
	// printf("Client: Hello2 msg sent from client!\n");

	// int inp = 5;
	// for(int j = 0; j < inp; ++j){
	// 	printf("\nEnter msg: ");
	// 	char input_msg[100];
	// 	scanf("%99s", input_msg);

	// 	send(client_fd, input_msg, strlen(input_msg), 0);
	// 	printf("\nClient: Input msg sent from client!\n");
	// }

	close(client_fd);

	return 0;
}
