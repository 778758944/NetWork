//
//  tcpcli01.c
//  Network
//
//  Created by WENTAO XING on 2019/5/14.
//  Copyright © 2019 WENTAO XING. All rights reserved.
//

#include "tcpcli01.h"

void tcproutecli(char * dest, char * host) {
    struct addrinfo dint, * res;
    u_char * ptr;
    bzero(&dint, sizeof(dint));
    int sockfd, len = 0;
    ssize_t nread;
    
    dint.ai_family = AF_INET;
    dint.ai_socktype = SOCK_STREAM;
    
    if (getaddrinfo(dest, "9877", &dint, &res) == -1) {
        exit(-1);
    }
    
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    
    ptr = inet_srcrt_init(1);
    len = inet_srcrt_add(host);
    if (ptr) {
        len = inet_srcrt_add(dest);
        setsockopt(sockfd, IPPROTO_IP, IP_OPTIONS, ptr, len);
        free(ptr);
    }
    
    if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
        perror("err: ");
        exit(1);
    }
    
    char buf[10];
    send(sockfd, "abcd", 4, 0);
    
    if ((nread = read(sockfd, buf, sizeof(buf))) > 0) {
        buf[nread] = 0;
        printf("%s\n", buf);
    }
    
}
