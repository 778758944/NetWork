//
//  ntest.c
//  Network
//
//  Created by WENTAO XING on 2019/4/17.
//  Copyright © 2019 WENTAO XING. All rights reserved.
//

#include "ntest.h"

static int servfd;
static int nsec;
static int maxtime;
static int nprobe = 0;

void tcpsend05() {
    int sockfd;
    int size;
    char buf[163840];
    struct sockaddr_in addr;

    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    inet_pton(AF_INET, "10.100.122.176", &addr.sin_addr.s_addr);
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    size = 327680;
    setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &size, sizeof(size));
    connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
    
    
    write(sockfd, buf, 163840);
    printf("wrote 16384 bytes of normal data\n");
    sleep(5);
    
    send(sockfd, "a", 1, MSG_OOB);
    printf("wrote 1 byte of OBB data\n");
    
    write(sockfd, buf, 1024);
    printf("wrote 1024 bytes of normal data");
}

void str_cli(int sockfd) {
    char send[100], recvbuf[BUFSIZ];
    ssize_t n;
    heartbeatcli(sockfd, 10, 5);
    
    for (;;) {
        strncpy(send, "hello", 100);
        write(sockfd, send, strlen(send));
        n = read(sockfd, recvbuf, BUFSIZ - 1);
        recvbuf[n] = 0;
        printf("recv: %s\n", recvbuf);
        
        sleep(20);
    }
}

void tcpecho() {
    int sockfd;
    struct sockaddr_in addr;
    
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5556);
    inet_pton(AF_INET, "10.100.122.176", &addr.sin_addr.s_addr);
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
    
    str_cli(sockfd);
}

void sig_urg(int signo) {
    nprobe = 0;
    return;
}

void sig_alarm(int signo) {
    nprobe++;
    if (nprobe > maxtime) {
        printf("the server is not connected");
        exit(0);
    }
    
    send(servfd, "b", 1, MSG_OOB);
    alarm(nsec);
    return;
}


void heartbeatcli(int sockfd_arg, int second_arg, int maxtime_arg) {
    servfd = sockfd_arg;
    nsec = second_arg;
    maxtime = maxtime_arg;
    
    signal(SIGURG, sig_urg);
    fcntl(servfd, F_SETOWN, getpid());
    signal(SIGALRM, sig_alarm);
    alarm(nsec);
}
