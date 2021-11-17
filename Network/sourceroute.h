//
//  sourceroute.h
//  Network
//
//  Created by WENTAO XING on 2019/5/14.
//  Copyright © 2019 WENTAO XING. All rights reserved.
//

#ifndef sourceroute_h
#define sourceroute_h

#include <stdio.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

static u_char * optr;
static u_char * lenptr;
static int ocnt;

u_char * inet_srcrt_init(int type);
int inet_srcrt_add(char * hostptr);
void inet_srcrt_print(u_char * ptr, int len);


#endif /* sourceroute_h */
