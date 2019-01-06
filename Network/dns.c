//
//  dns.c
//  Network
//
//  Created by Tom Xing on 1/4/19.
//  Copyright © 2019 WENTAO XING. All rights reserved.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dns.h"
#include "./udp.h"
#define DNS_CONTENT 12

static int id_0 = 0;
static int id_1 = 0;

char * DnsDecode(const char * domain);

char * DnsSearch(const char * domain) {
    uint8_t * p = (uint8_t *) calloc(1024 * 10, 1);
    size_t len = strlen(domain);
    int i, next, lastdot = 0;
    // search id
    if (id_0 == id_1) {
        id_0++;
    } else {
        id_1++;
    }
    p[0] = id_0;
    p[1] = id_1;
    // specific search dns and the search should recursion
    p[2] = 0x01;
    // Question
    p[5] = 0x01;
    
    for (i = 0; i < len; i++) {
        if (domain[i] == '.') {
            // specific the length before the first .
            if (p[12] == 0) p[12] = i;
            if (lastdot) p[lastdot + 13] = i - lastdot - 1;
            lastdot = i;
        } else {
            p[13 + i] = domain[i];
        }
    }
    
    if (lastdot) p[lastdot + 13] = i -lastdot - 1;
    
    next = 13 + i;
    
    p[next] = 0;
    p[next + 2] = 0x1;
    p[next + 4] = 0x1;
    sendUdpMsg(p, next + 5, "192.168.123.1", "53");
    free(p);
    return DnsDecode(domain);
}

char * DnsDecode(const char * domain) {
    uint8_t * dnsData;
    socklen_t t;
    size_t dnsSize = recvUdpMsg(&dnsData, NULL, &t);
    char * ipaddress = calloc(20, 1);
    printf("dnsSize: %lu\n", dnsSize);
    if (dnsSize) {
        if (dnsData[0] == id_0 && dnsData[1] == id_1) {
            // anwsers
            uint16_t anwsers = dnsData[6] << 8 | dnsData[7];
            size_t queryBytes = strlen(domain) + 2 + 4;
            size_t answerStart = DNS_CONTENT + queryBytes;
            if (anwsers == 1) {
                size_t ipstart = answerStart + 12;
                sprintf(ipaddress, "%u.%u.%u.%u", dnsData[ipstart], dnsData[ipstart + 1], dnsData[ipstart + 2], dnsData[ipstart + 3]);
                free(dnsData);
                return ipaddress;
            }
        }
    }
    return NULL;
}
