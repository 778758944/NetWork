//
//  sourceroute.c
//  Network
//
//  Created by WENTAO XING on 2019/5/14.
//  Copyright © 2019 WENTAO XING. All rights reserved.
//

#include "sourceroute.h"

u_char * inet_srcrt_init(int type) {
    optr = malloc(44);
    bzero(optr, 44);
    ocnt = 0;
    *optr++ = IPOPT_NOP;
    *optr++ = type ? IPOPT_SSRR : IPOPT_LSRR;
    lenptr = optr++;
    *optr++ = 4;
    return optr - 4;
}

int inet_srcrt_add(char * hostptr) {
    int len;
    struct addrinfo * ai, dint;
    struct sockaddr_in * sin;
    int err;
    
    bzero(&dint, sizeof(struct addrinfo));
    dint.ai_family = AF_INET;
    dint.ai_socktype = SOCK_STREAM;
    dint.ai_flags = AI_CANONNAME;
    
    if ((err = getaddrinfo(hostptr, NULL, &dint, &ai)) == -1) {
        exit(err);
    }
    
    sin = (struct sockaddr_in *) ai->ai_addr;
    memcpy(optr, &sin->sin_addr, sizeof(struct in_addr));
    optr += sizeof(struct in_addr);
    ocnt++;
    len = 3 + (ocnt * sizeof(struct in_addr));
    *lenptr = len;
    return len + 1;
}

void inet_srcrt_print(u_char *ptr, int len) {
    u_char c;
    char str[INET_ADDRSTRLEN];
    struct in_addr hop1;
    
    memcpy(&hop1, ptr, sizeof(struct in_addr));
    ptr += sizeof(struct in_addr);
    
    while ((c = *ptr++) == IPOPT_NOP);
    
    if (c == IPOPT_LSRR) {
        printf("received LSRR: ");
    } else if (c == IPOPT_SSRR) {
        printf("received SSRR: ");
    } else {
        printf("received option type %d\n", c);
        return;
    }
    
    printf("%s ", inet_ntop(AF_INET, ptr, str, sizeof(str)));
    ptr++;
    
    while (len > 0) {
        printf("%s ", inet_ntop(AF_INET, ptr, str, sizeof(str)));
        ptr += sizeof(struct in_addr);
        len -= sizeof(struct in_addr);
    }
    
    printf("\n");
}




