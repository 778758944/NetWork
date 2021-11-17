//
//  dgserv.c
//  Network
//
//  Created by WENTAO XING on 2019/4/10.
//  Copyright © 2019 WENTAO XING. All rights reserved.
//

#include "dgserv.h"


void dgServ() {
    int sockfd;
    struct sockaddr_in addr;
    struct sockaddr cliaddr;
    bzero(&addr, sizeof(addr));
    ssize_t n;
    socklen_t len;
    char buf[BUFSIZ];
    time_t t;
    
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(13);
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
    
    for(;;) {
        printf("waiting\n");
        len = sizeof(cliaddr);
        n = recvfrom(sockfd, buf, BUFSIZ, 0, &cliaddr, &len);
        t = time(NULL);
        snprintf(buf, BUFSIZ, "%.24s\r\n", ctime(&t));
        sendto(sockfd, buf, strlen(buf), 0, &cliaddr, len);
    }
    
}

void dgServMCast() {
    int sockfd;
    struct sockaddr_in addr, grpaddr, cliaddr;
    socklen_t len;
    char buf[BUFSIZ];
    ssize_t n;
    
    bzero(&addr, sizeof(addr));
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9877);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
    
    grpaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "224.0.0.1", &grpaddr.sin_addr);
    
    struct group_req req;
    req.gr_interface = 0;
    memcpy(&req.gr_group, &grpaddr, sizeof(grpaddr));
    
    setsockopt(sockfd, IPPROTO_IP, MCAST_JOIN_GROUP, &req, sizeof(req));
    
    for(;;) {
        printf("start read");
        len = sizeof(addr);
        n = recvfrom(sockfd, buf, BUFSIZ, 0, (struct sockaddr *) &cliaddr, &len);
        
        buf[n] = 0;
        
        printf("recv: %s\n", buf);
        
        sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *) &cliaddr, len);
    }
}

void dgSend() {
    int sockfd;
    struct sockaddr_in addr;
    char recv[BUFSIZ];
    ssize_t n;
    
    bzero(&addr, sizeof(addr));
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9877);
    inet_pton(AF_INET, "224.0.0.1", &addr.sin_addr);
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    sendto(sockfd, "abc", 4, 0, (struct sockaddr *) &addr, sizeof(addr));
    
    n = recvfrom(sockfd, recv, BUFSIZ, 0, NULL, NULL);
    recv[n] = 0;
    
    printf("recv: %s\n", recv);
    
}
