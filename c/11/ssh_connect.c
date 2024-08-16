#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libssh/libssh.h>

int main(int argc, char *argv[])
{
    const char *hostname = 0;
    int port = 22;
    if (argc < 2) {
        fprintf(stderr, "Usage: ssh_connect hostname port\n");
        return 1;
    }
    hostname = argv[1];
    if (argc > 2) port = atol(argv[2]);

    ssh_session ssh = ssh_new();
    if (!ssh) {
        fprintf(stderr, "ssh_new() failed.\n");
        return 1;
    }

    
    return 0;
}
