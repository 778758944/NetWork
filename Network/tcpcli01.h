//
//  tcpcli01.h
//  Network
//
//  Created by WENTAO XING on 2019/5/14.
//  Copyright © 2019 WENTAO XING. All rights reserved.
//

#ifndef tcpcli01_h
#define tcpcli01_h

#include "./sourceroute.h"
#include <unistd.h>
#include <errno.h>

void tcproutecli(char * dest, char * host);

#endif /* tcpcli01_h */
