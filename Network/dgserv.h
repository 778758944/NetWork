//
//  dgserv.h
//  Network
//
//  Created by WENTAO XING on 2019/4/10.
//  Copyright © 2019 WENTAO XING. All rights reserved.
//

#ifndef dgserv_h
#define dgserv_h

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

void dgServ(void);
void dgServMCast(void);
void dgSend(void);

#endif /* dgserv_h */
