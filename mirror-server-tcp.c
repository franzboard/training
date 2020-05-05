/* Simple TCP server listening on port given by command line option */
/* connect with telnet or nc, send string */
/* Server answers with string with characters in reverse order */

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFSIZE 1000


int main(int argc, char* argv[])
{
    int server_socket, rec_socket;
    unsigned int len, count;
    struct sockaddr_in serverinfo, clientinfo;
    char rec_buf[BUFSIZE];
    char send_buf[BUFSIZE];

    // call program_name port
    if (  < 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    unsigned int port = atoi(argv[1]);
    server_socket = socket(AF_INET,             , 0); // TCP Socket
    serverinfo.sin_family = AF_INET;
    serverinfo.sin_addr.s_addr = htonl(          ); // Listen only on localhost interface
    serverinfo.sin_port = htons(port);

    if (bind(server_socket,                              ) != 0) {
        perror("Error ");
        return 1;
    }
    listen(server_socket, 3);

    while(1) {
        printf("Server waiting...\n");
        len = sizeof(clientinfo);
        rec_socket = accept(server_socket, (struct sockaddr *)&clientinfo, &len);
        printf("Connected from %s:%d\n", inet_ntoa(clientinfo.sin_addr), ntohs(clientinfo.sin_port));

        count = read(                     , rec_buf, sizeof(rec_buf));


        // Reverse order of characters in rec_buf and write to send_buf

        write(rec_socket, send_buf, count);
        close(rec_socket);
    }

}
