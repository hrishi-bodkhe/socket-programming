#ifndef SOCKET_H
#define SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int create_socket(int ai_family, int ai_socktype, int ai_protocol);

void bind_socket(int sockfd, int port, int ip_version, char *address);

void listen_socket(int sockfd, int backlogs);

void connect_socket(int sockfd, const char *address, int port, int ip_version);

int accept_connection(int sockfd, int ip_version);

void write_msg(int sockfd, char *msg);

void read_msg(int sockfd, char buffer[], size_t buffer_size);

void handle_client(int client_socket);

#endif
