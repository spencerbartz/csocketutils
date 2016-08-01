/* ------------------------------------------------------------------------
 * BSD Socket Utility Interface
 * Author: Spencer Bartz
 * Comment: Converted from original POSIX implementation. I stole 
 * most of the POSIX implementation from the book used for 
 * CS 176b at UCSB circa 2005. Unfortunately I lost the book 
 * and cannot recall its title!
 *---------------------------------------------------------------------*/

#include "loggerutils.h"
#include "socketutils.h"

unsigned short	portbase = 0;	/* port base, for non-root servers	*/

/* ------------------------------------------------------------------------
 * connectTCP - connect to a specified TCP service on a specified host
 * Arguments:
 * host - name of host to which connection is desired
 * service - service associated with the desired port
 *----------------------------------------------------------------------*/
int connectTCP(const char *host, const char *service)
{
	return connectsock( host, service, "tcp");
}

/*-----------------------------------------------------------------------
 * connectUDP - connect to a specified UDP service on a specified host
 * Arguments:
 * host    - name of host to which connection is desired
 * service - service associated with the desired port 
 *----------------------------------------------------------------------*/
int connectUDP(const char *host, const char *service)
{
	return connectsock(host, service, "udp");
}

/*------------------------------------------------------------------------
 * passiveTCP - create a passive socket for use in a TCP server
 * Arguments:
 * service - service associated with the desired port
 * qlen    - maximum server request queue length
 *-----------------------------------------------------------------------*/
int passiveTCP(const char *service, int qlen)
{
	return passivesock(service, "tcp", qlen);
}

/*------------------------------------------------------------------------
 * passiveUDP - create a passive socket for use in a UDP server
 * Arguments:
 * service - service associated with the desired port
 *-----------------------------------------------------------------------*/
int passiveUDP(const char *service)
{
    return passivesock(service, "udp", 0);
}

//experimental
char * port_to_proto(int port)
{
    int known_ports[5] =        { 80,     443,     23,    21,       220 };
    char * known_protocols[5] = { "HTTP", "HTTPS", "FTP", "TELNET", "IMAP" };

    int i;
    for(i = 0; i < 5; i++) {
        if(known_ports[i] == port) { 
            return known_protocols[i];
        }
    }

    return "";
}

/*------------------------------------------------------------------------
 * connectsock - allocate & connect a CLIENT socket using TCP or UDP
 * Arguments:
 * host      - name of host to which connection is desired
 * service   - service associated with the desired port
 * transport - name of transport protocol to use ("tcp" or "udp")
 *-----------------------------------------------------------------------*/
int connectsock(const char *host, const char *service, const char *transport )
{
    struct sockaddr_in client;      /* an Internet endpoint address */
    struct hostent* hostent_ptr;    /* pointer to host information entry */
    struct servent* servent_ptr;    /* pointer to service information entry */
    struct protoent* protoent_ptr;  /* pointer to protocol information entry*/
    int sock_desc;                  /* The socket descriptor (actually a file descriptor) */
    int protocol_type;              /* socket type: TCP or UDP */

    /* Zero out client struct and load with IP / Port data */  
    memset(&client, 0, sizeof(client));
    client.sin_family = AF_INET;  
   
    /* Map service name to port number */
    if ((servent_ptr = getservbyname(service, transport))) {
        client.sin_port = servent_ptr->s_port;
    }
    else if ((client.sin_port=htons((unsigned short)atoi(service))) == 0) {
        log_error(__FILE__, __LINE__, "Cannot get \"%s\" service entry\n", service);
        exit(EXIT_FAILURE);
    }

    /* Map host name to IP address, allowing for dotted decimal */
    if ((hostent_ptr = gethostbyname(host))) {
        memcpy(&client.sin_addr, hostent_ptr->h_addr, hostent_ptr->h_length);
    }
    else if ( (client.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE ) {
        log_error(__FILE__, __LINE__, "Cannot get \"%s\" host entry\n", host);
        exit(EXIT_FAILURE);
    }

    /* Map port to protocol number */
    if (((protoent_ptr = getprotobyname(transport))) == 0) {
        log_error(__FILE__, __LINE__, "Cannot get \"%s\" protocol entry\n", transport);
        exit(EXIT_FAILURE);
    }

    /* Choose  socket type */
    if (strcmp(transport, "udp") == 0) {
        protocol_type = SOCK_DGRAM;
    }
    else {
        protocol_type = SOCK_STREAM;
    }

    /* Create the socket */ 
    sock_desc = socket(AF_INET, protocol_type, protoent_ptr->p_proto); 
    
    if (sock_desc == -1) {
        log_error(__FILE__, __LINE__, "Cannot create socket.\n");
        exit(EXIT_FAILURE);
    }

    /* Connect the socket to the server */
    if (connect(sock_desc, (struct sockaddr*)&client, sizeof(client)) != 0) {
        log_error(__FILE__, __LINE__, "Connection to server failed.\n");
        close(sock_desc);
        exit(EXIT_FAILURE);
    }

    return sock_desc;
}

/*------------------------------------------------------------------------
 * passivesock - allocate & bind a SERVER socket using TCP or UDP
 * Arguments:
 * service   - service associated with the desired port
 * transport - transport protocol to use ("tcp" or "udp")
 * qlen      - maximum server request queue length
 *------------------------------------------------------------------------*/
int passivesock(const char *service, const char *transport, int qlen)
{
    struct sockaddr_in server;      /* an Internet endpoint address */
    struct servent* servent_ptr;    /* pointer to service information entry */
    struct protoent* protoent_ptr;  /* pointer to protocol information entry*/
    int sock_desc;                  /* socket descriptor  */
    int protocol_type;              /* udp or tcp type socket */ 
    const int on = 1;

    /* load server struct with incoming IP / local Port data */ 
    memset(&server, 0, sizeof(server));  
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;  
    
    /* Map service name to port number */
    if ((servent_ptr = getservbyname(service, transport))) {
        server.sin_port = htons(ntohs((unsigned short)servent_ptr->s_port) + portbase);
    }
    else if ((server.sin_port=htons((unsigned short)atoi(service))) == 0) {
        log_error(__FILE__, __LINE__, "Cannot get \"%s\" service entry\n", service);
        exit(EXIT_FAILURE);
    }

    /* Map protocol name to protocol number */
    if ( (protoent_ptr = getprotobyname(transport)) == 0) {
        log_error(__FILE__, __LINE__, "Cannot get \"%s\" protocol entry\n", transport);
        exit(EXIT_FAILURE);
    }
   
    /* Choose udp or tcp based on transport */
    if (strcmp(transport, "udp") == 0) {
        protocol_type = SOCK_DGRAM;
    }
    else {
        protocol_type = SOCK_STREAM;
    }

    /* create the socket */ 
    sock_desc = socket(AF_INET, protocol_type, protoent_ptr->p_proto);
    
    if (sock_desc == -1) {
        log_error(__FILE__, __LINE__, "Cannot create socket!\n");
        exit(EXIT_FAILURE);
    }

    setsockopt(sock_desc, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  
    /* Bind the socket */
    if (bind(sock_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        log_error(__FILE__, __LINE__, "Cannot bind socket on port: %s\n", service);
        exit(EXIT_FAILURE);
    }
    
    /* begin listening */
    if (protocol_type == SOCK_STREAM && listen(sock_desc, qlen) < 0) {
        log_error(__FILE__, __LINE__, "Cannot listen on %s port: %s\n", service, strerror(errno)); 
        exit(EXIT_FAILURE);
    }

    return sock_desc;
}

