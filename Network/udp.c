//
//  udp.c
//  Network
//
//  Created by WENTAO XING on 2019/1/3.
//  Copyright © 2019 WENTAO XING. All rights reserved.
//

#include "udp.h"

int initUdp(void) {
    socket_id = socket(PF_INET, SOCK_DGRAM, 0);
    return socket_id;
}

ssize_t sendUdpMsg(const void * data, size_t len, char * host, char * port) {
    struct addrinfo * result, dint;
    memset(&dint, 0, sizeof(dint));
    dint.ai_family = PF_INET;
    dint.ai_socktype = SOCK_DGRAM;
    int rc;
    
    rc = getaddrinfo(host, port, &dint, &result);
    if (rc == -1) {
        return rc;
    }
    
    return sendUdpMsgWithSockaddr(data, len, result->ai_addr, result->ai_addrlen);
}

ssize_t recvUdpMsg(void * data, size_t size, struct sockaddr * addr, socklen_t * addrlen, int type) {
    ssize_t t = recvfrom(socket_id, data, size, type, addr, addrlen);
    return t;
}

ssize_t sendUdpMsgWithSockaddr(const void * data, size_t len, struct sockaddr * addr, socklen_t addrlen) {
     return sendto(socket_id, data, len, 0, addr, addrlen);
}


