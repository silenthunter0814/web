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
#include <ctype.h>
#include <stdarg.h>

#define MAXINPUT 512
#define MAXRESPONSE 1024

int main(int argc, char *argv[])
{
    return 0;
}

void get_input(const char *prompt, char *buffer)
{
    printf("%s", prompt);

    buffer[0] = 0;
    fgets(buffer, MAXINPUT, stdin);
    const int read = strlen(buffer);
    if (read > 0)
        buffer[read - 1] = 0;
}
