#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#include <stdio.h>
#include <time.h>

int main()
{
    time_t timer;
    time(&timer);
    printf("Local time is: %s", ctime(&timer));
    return 0;
}

