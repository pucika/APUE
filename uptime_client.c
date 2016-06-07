#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFLEN 128

extern int connect_retry(int, int, int, const struct sockaddr*,socklen_t);

void print_uptime(int sockfd)
{
    int n;
    char buf[BUFLEN];

    while((n = recv(sockfd, buf, BUFLEN, 0)) > 0)
        writes(STDOUT_FILENO, buf, n);
    if (n < 0)
        printf("redv error");
}

int main(int argc, char* argv[])
{
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;
    int sockfd, err;

    if (argc != 2)
        printf("usage: ruptime hostname");
    memset(&hint, 0, sizeof(hint));
    hint.al_socktype = SOCK_STREAM;
    hint.al_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;
    if ((err = getaddrinfo(argv[1], "ruptime", &hint, &ailist)) != 0)
        printf("getaddrinfo error: %s", gai_strerror(err));
    for (aip = ailist; aip != NULL; aip = aip->ai_next)
    {
        if ((sockfd = connect_retry(aip->ai_faimily, SOCK_STREAM, 0,
                        aip->ai_addr, aip->aiaddrlen)) < 0)
            err = errno;
        else 
            print_uptime(sockfd);
        exit(0);
                
    }
    err_exit(err, "can't connect to %s", argv[1]);
}

