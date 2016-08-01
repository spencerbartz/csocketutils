#include "socketutils.h"    
#include "loggerutils.h"

int main(int argc, char ** argv)
{

    if(strncmp(argv[1], "httpclient", strlen(argv[1])) == 0)
    {
        int my_sock = connectTCP("yahoo.com", "80"); 
   
        char* request = "GET / HTTP/1.1\r\nHost: https://www.yahoo.com/\r\n\r\n";

        int bytes_to_send = (strlen(request) * (sizeof(char)));
    
        log_debug(__FILE__, __LINE__, "bytes to send: %d\n", bytes_to_send);
        log_debug(__FILE__, __LINE__, "Request:\n%s", request);

        char * response = (char *) calloc(16, sizeof(char));
        char * read_buffer = (char *) calloc(MAX_MSG, sizeof(char));
        int bytes_read = 0;
        int bytes_sent = 0;
        int response_code = 0;

        while (bytes_to_send > 0) {
            response_code = send(my_sock, request, bytes_to_send, 0);
        
            if (response_code < 0) {
                log_error(__FILE__, __LINE__, "Sending data failed");
                exit(EXIT_FAILURE);
            }

            bytes_sent += response_code;
            bytes_to_send -= response_code;
        }    
        int x = 10;
        while((bytes_read = recv(my_sock, read_buffer, MAX_MSG, 0)) > 0) {
            log_debug(__FILE__, __LINE__, "bytes read %d\n", bytes_read);
            log_debug(__FILE__, __LINE__, "CONTENTS OF read_buffer: %s\n\n ", read_buffer);
            char * temp = (char *) calloc((strlen(response) + bytes_read + 1),  sizeof(char));
            strncpy(temp, response, strlen(response)); 
            response = strncat(temp, read_buffer, bytes_read); 
        }

        if(bytes_read < 0) {
                log_error(__FILE__, __LINE__, "FAILED TO READ RESPONSE");
        }
        
        if(strlen(response) > 0) {
            log_debug(__FILE__, __LINE__, "RECEIVED RESPONSE: %s", response);
        }
        
        return 0;
    }
    else if (strncmp(argv[1], "server", strlen(argv[1])) == 0)
    { 
        unsigned int addrLength; 
        struct sockaddr_in clientAddr; 
        int server_sock = passiveTCP("9090", 500);
        int client_sock = accept(server_sock, (struct sockaddr *)&clientAddr, &addrLength);
        char * buf = (char *) calloc(128, sizeof(char));
        recv(client_sock, buf, 127, 0);
        log_debug(__FILE__, __LINE__, "RECEIVED BUFFER: %s", buf);
    
    }  
    else if (strncmp(argv[1], "client", strlen(argv[1])) == 0)
    {
        int client_sock = connectTCP("127.0.0.1", "9090");
        int bytes_sent = send(client_sock, "HIYA BUDDY", 10, 0);
        log_debug(__FILE__, __LINE__, "Bytes Sent: %d", bytes_sent);
    }

}

