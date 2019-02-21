#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFLEN 128

#define MAXSLEEP 128

int connect_retry(int sockfd, const struct sockaddr *addr, socklen_t alen)
{
    int nsec;
    
    for (nsec = 1; nsec <= MAXSLEEP; nsec <<= 1) {
        if (connect(sockfd, addr, alen) == 0)
            return(0);
        if (nsec <= MAXSLEEP/2)
            sleep(nsec);
    }
    return(-1);
}

//extern connect_retry(int sockfd, const struct sockaddr *addr, socklen_t alen);

int print_uptime(int sockfd)
{
    int n;
    char buf[BUFLEN];
    
    while ((n= recv(sockfd, buf, BUFLEN, 0)) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n)
            return(-1);
    }
    if (n < 0)
        return(-1);
    if (n == 0)
        printf("nothing received\n");
    return 0;
}


int main(int argc, char *argv[])
{
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;
    struct sockaddr_in *sinp;
    int sockfd;
    int err;
    char seraddr[INET_ADDRSTRLEN];
    short serport;
    
    if (argc != 2) {
        printf("usage: %s <hostname>\n", argv[0]);
        exit(-1);
    }
    
    hint.ai_family = 0;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = AI_CANONNAME;
    hint.ai_protocol = 0;
    hint.ai_addrlen = 0;
    hint.ai_addr = NULL;
    hint.ai_canonname = NULL;
    hint.ai_next = NULL;
    if ((err = getaddrinfo(argv[1], "bacnet", &hint, &ailist)) != 0) {
        printf("getaddrinfo error: %s\n", gai_strerror(err));
        exit(-1);
    }
        printf("getaddrinfo ok\n");
    for (aip = ailist; aip != NULL; aip = aip->ai_next) {
        sinp = (struct sockaddr_in *)aip->ai_addr;
        if (inet_ntop(sinp->sin_family, &sinp->sin_addr, seraddr, INET_ADDRSTRLEN) != NULL)
        {
            printf("server address is %s\n", seraddr);
        }
            serport = ntohs(sinp->sin_port);
            printf("server port is %d\n", serport);
        
        if ((sockfd = socket(aip->ai_family, SOCK_STREAM, 0)) < 0) {
            printf("create socket failed: %s\n", strerror(errno));
            exit(-1);
        }
        printf("create socket ok\n");
        if (connect_retry(sockfd, aip->ai_addr, aip->ai_addrlen) < 0) {
            printf("can't connect to %s: %s\n", argv[1], strerror(errno));
            exit(-1);
        } else {
            printf("connect ok\n");
            if (print_uptime(sockfd) < 0) {
                printf("print_uptime error: %s\n", strerror(errno));
                exit(-1);
            }
        }
    }
        exit(0);
}
