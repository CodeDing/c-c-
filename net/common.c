#include <sys/socket.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <syslog.h>

#define MAXSLEEP 128

int
connect_retry(int sockfd, const struct sockaddr *addr, socklen_t alen)
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

int
initserver(int type, const struct sockaddr *addr, socklen_t alen, int qlen)
{
    int fd;
    int err = 0;
    int reuse = 1;

    if ((fd = socket(addr->sa_family, type, 0)) < 0)
            return(-1);
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) < 0) {
        err = errno;
        goto errout;
    }
    if (bind(fd, addr, alen) < 0) {
        err = errno;
        goto errout;
    }
    if ((type == SOCK_STREAM) || (type == SOCK_SEQPACKET)) {
        if (listen(fd, qlen) < 0) {
            err = errno;
            goto errout;
        }
    }
    return(fd);
errout:
    close(fd);
    errno = err;
    return(-1);
}

void
daemonize(const char *cmd)
{
    int i, fd0, fd1, fd2;
    pid_t pid;
    struct rlimit rl;
    struct sigaction sa;

    umask(0);

    if (getrlimit(RLIMIT_NOFILE, &rl) < 0) {
        printf("getrlimit failed");
        exit(1);
    }

    if ((pid = fork()) < 0) {
        printf("first fork failed");
        exit(1);
    } else if (pid > 0) {
        exit(0);
    }

    setsid();

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0) {
        printf("sigaction failed");
        exit(1);
    }
    if ((pid = fork()) < 0) {
        printf("second fork failed");
        exit(1);
    } else if (pid > 0) {
        exit(0);
    }

    if (chdir("/") < 0) {
        printf("chdir failed");
        exit(1);
    }

    if (rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for (i = 0; i < rl.rlim_max; i++)
        close(i);

    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
        syslog(LOG_ERR, "unexpected file descriptor %d %d %d", fd0, fd1, fd2);
        exit(1);
    }
}
