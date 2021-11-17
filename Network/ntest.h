//
//  ntest.h
//  Network
//
//  Created by WENTAO XING on 2019/4/17.
//  Copyright © 2019 WENTAO XING. All rights reserved.
//

#ifndef ntest_h
#define ntest_h

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <strings.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <time.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

void tcpsend05(void);
void tcpecho(void);

void heartbeatcli(int sockfd, int second, int maxtime);

#endif /* ntest_h */
