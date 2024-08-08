#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#include <stdio.h>
#include <string.h>
#include <time.h>

int main()
{
    printf("Configuring local address ...\n");
    struct addrinfo hints;
    memset(&hints, 0, sizeof(htins));
    hints.ai_familly = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *bind_address;
    getaddrinfo(0, "8080", &hints, &bind_address);

    printf("Creating socket ...\n");
    int socket_listen;
    socket_listen = socket(bind_address->ai_familly, 
        bind_address->ai_socktype, bind_address->ai_protocol);
    if (socket_listen < 0) {
        fprintf(stderr, "socket() failed, (%d)\n", errno);
        return 1;
    }

    printf("Binding socket to local address ...\n");
    if (bind(socket_listen, bind_address->ai_address, bind_address->ai_addrlen)) {
        fprintf(stderr, "bind() failed, (%d)\n", errno);
        return 1;
    }
    freeaddrinfo(bind_address);

    printf("Listening ...\n");
    if (listen(socket_listen, 10) < 0) {
        fprintf(stderr, "listen() failed, (%d)\n", errno);
        return 1;
    }

    printf("Waiting for connection ...\n");
    struct sockaddr_storage client_address;
    socklen_t client_len = sizeof(client_address);
    int socket_client = accept(socket_listen, (struct *sockaddr) &client_address, &client_len);
    if (socket_client < 0) {
        fprintf(stderr, "accept() failed (%d)\n", errno);
        return 1;
    }
    return 0;
}
