//
//  udp.h
//  Network
//
//  Created by WENTAO XING on 2019/1/3.
//  Copyright © 2019 WENTAO XING. All rights reserved.
//

#ifndef udp_h
#define udp_h

static int socket_id;

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

int initUdp(void);
ssize_t sendUdpMsg(const void * data, size_t len, char * host, char * port);
ssize_t recvUdpMsg(void ** data, struct sockaddr * addr, socklen_t * addrlen);
ssize_t sendUdpMsgWithSockaddr(const void * data, size_t len, struct sockaddr * addr, socklen_t addrlen);

#endif /* udp_h */
