#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <clock.h>

void parse_url(char *url, char **hostname, char **port, char **path);
void send_request(int s, char *hostname, char *port, char *path);
int connect_to_host(char *hostname, char *port);

#define TIMEOUT 5.0

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "usage: web_get url\n");
        return 1;
    }
    char *url = argv[1];

    char *hostname, *port, *path;
    parse_url(url, &hostname, &port, &path);

    int server = connect_to_host(hostname, port);
    send_request(server, hostname, port, path);

    const clock_t start_time = clock();
    return 0;
}

int connect_to_host(char *hostname, char *port) {
    printf("Configuring remote address...\n");
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    struct addrinfo *peer_address;
    if (getaddrinfo(hostname, port, &hints, &peer_address)) {
        fprintf(stderr, "getaddrinfo() failed. (%d)\n", errno);
        exit(1);
    }

    printf("Remote address is: ");
    char address_buffer[100];
    char service_buffer[100];
    getnameinfo(peer_address->ai_addr, peer_address->ai_addrlen,
            address_buffer, sizeof(address_buffer),
            service_buffer, sizeof(service_buffer),
            NI_NUMERICHOST);
    printf("%s %s\n", address_buffer, service_buffer);

    printf("Creating socket...\n");
    int server;
    server = socket(peer_address->ai_family,
            peer_address->ai_socktype, peer_address->ai_protocol);
    if (server < 0) {
        fprintf(stderr, "socket() failed. (%d)\n", errno);
        exit(1);
    }

    printf("Connecting...\n");
    if (connect(server,
            peer_address->ai_addr, peer_address->ai_addrlen)) {
        fprintf(stderr, "connect() failed. (%d)\n", errno);
        exit(1);
    }
    freeaddrinfo(peer_address);

    printf("Connected.\n\n");

    return server;
}

void send_request(int s, char *hostname, char *port, char *path) {
    char buffer[2048];

    sprintf(buffer, "GET /%s HTTP/1.1\r\n", path);
    sprintf(buffer + strlen(buffer), "Host: %s:%s\r\n", hostname, port);
    sprintf(buffer + strlen(buffer), "Connection: close\r\n");
    sprintf(buffer + strlen(buffer), "User-Agent: honpwc web_get 1.0\r\n");
    sprintf(buffer + strlen(buffer), "\r\n");

    send(s, buffer, strlen(buffer), 0);

    printf("Sent Headers:\n%s", buffer);
}

void parse_url(char *url, char **hostname, char **port, char **path) {
    printf("URL: %s\n", url);

    char *p;
    p = strstr(url, "://");

    char *protocol = 0;
    if (p) {
        protocol = url;
        *p = 0;
        p += 3;
    } else {
        p = url;
    }

    if (protocol) {
        if (strcmp(protocol, "http")) {
            fprintf(stderr, "Unknown protocol '%s'. Only 'http' is supported.\n", protocol);
            exit(1);
        }
    }

    *hostname = p;
    while (*p && *p != ':' && *p != '/' && *p != '#')
        ++p;

    *port = "80";
    if (*p = ':') {
        *p++ = 0;
        *port = p;
    }
    while (*p && *p != '/' && *p != '#')
        ++p;

    *path = p;
    if (*p == '/')
        *path = p + 1;
    *p = 0;

    ++p;
    while (*p && *p != '#')
        ++p;
    if (*p == '#')
        *p = 0;

    printf("hostname: %s\n", *hostname);
    printf("port: %s\n", *port);
    printf("path: %s\n", *path);
}
