#ifndef SOCKETUTILS_H
#define SOCKETUTILS_H

// define INADDR_NONE if not already defined by system
#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff
#endif 

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/errno.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>
#include <string.h>
#include <stdlib.h>

#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_MSG 2048

// Function prototypes
int connectTCP(const char *host, const char *service);
int connectUDP(const char *host, const char *service);
int passiveTCP(const char *service, int qlen);
int passiveUDP(const char *service);
int connectsock(const char *host, const char *service, const char *transport);
int passivesock(const char *service, const char *transport, int qlen);
char * port_to_proto(int port);

#endif

