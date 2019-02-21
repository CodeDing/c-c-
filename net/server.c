#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <fcntl.h>

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 64
#endif

#define BUFLEN 128
#define QLEN 10

extern int initserver(int, const struct sockaddr *, socklen_t, int);
extern void daemonize(const char *);

void
serve(int sockfd)
{
    int clfd, status;
    pid_t pid;

    for (;;) {
        if ((clfd = accept(sockfd, NULL, NULL)) < 0) {
            syslog(LOG_ERR, "accept error: %m/n");
            exit(-1);
        }

        if ((pid = fork()) < 0) {
            syslog(LOG_ERR, "fork error: %m/n");
            exit(-1);
        } else if (pid == 0) {
            if (dup2(clfd, STDOUT_FILENO) != STDOUT_FILENO ||
                        dup2(clfd, STDERR_FILENO) != STDERR_FILENO) {
                syslog(LOG_ERR, "dup2 error: %m/n");
                exit(-1);
            }
            close(clfd);
            execl("/usr/bin/uptime", "uptime", (char *)0);
            syslog(LOG_ERR, "unexpected return from execl: %m");
        } else {
            close(clfd);
            waitpid(pid, &status, 0);
        }
    }
}

int
main(void)
{
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;
    struct sockaddr_in *sinp;
    int sockfd;
    int err, n;
    char *host;
    char buf[INET_ADDRSTRLEN];

#ifdef _SC_HOST_NAME_MAX
    n = sysconf(_SC_HOST_NAME_MAX);
    if (n < 0)
#endif
        n = HOST_NAME_MAX;

    if ((host = malloc(n)) == NULL) {
        printf("malloc error: %s/n", strerror(errno));
        exit(-1);
    }
    if (gethostname(host, n) < 0) {
        printf("gethostname error: %s/n", strerror(errno));
        exit(-1);
    }
    syslog(LOG_ERR, "hostname is %s", host);
    daemonize("ruptimed");

    hint.ai_flags = AI_PASSIVE;
    hint.ai_family = 0;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = 0;
    hint.ai_addrlen = 0;
    hint.ai_addr = NULL;
    hint.ai_canonname = NULL;
    hint.ai_next = NULL;
    if ((err = getaddrinfo(NULL, "47808", &hint, &ailist)) != 0) {
        syslog(LOG_ERR, "getaddrinfo error: %s", gai_strerror(err));
        exit(-1);
    }
    for (aip = ailist; aip != NULL; aip = aip->ai_next) {
        sinp = (struct sockaddr_in *)aip->ai_addr;
        short port = ntohs(sinp->sin_port);
        syslog(LOG_ERR, "port is %d/n", port);
        if (inet_ntop(aip->ai_family, &sinp->sin_addr, buf, INET_ADDRSTRLEN) != NULL)
            syslog(LOG_ERR, "addr is %s/n", buf);
        if ((sockfd = initserver(aip->ai_socktype, aip->ai_addr,
                             aip->ai_addrlen, QLEN)) >= 0) {
            serve(sockfd);
            exit(0);
        }
    }
    exit(-1);
}
