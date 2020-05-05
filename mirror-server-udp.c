/* Simple UDP server listening on port given by command line option */
/* connect with telnet or nc, send string */
/* Server answers with string with characters in reverse order */

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFSIZE 1000

int main(int argc, char* argv[])
{
    int socketfd;
    unsigned int len, count;
    struct sockaddr_in serverinfo, clientinfo;
    char rec_buf[BUFSIZE];
    char send_buf[BUFSIZE];

    // call program_name port
    if (argc < 2) {
        printf("Usage: %s <port>\n",      );
        return 1;
    }

    unsigned int port =             ; // from command line
    socketfd = socket(AF_INET,           , 0);  // UDP Socket
    serverinfo.sin_family = AF_INET;
    serverinfo.sin_addr.s_addr = htonl(          ); // all available addresses
    serverinfo.sin_port = htons(port);

    if (bind(socketfd, (struct sockaddr *)&serverinfo, sizeof(serverinfo)) != 0) {
        perror("Error ");
        return 1;
    }

    while (1) {
        len = sizeof(clientinfo);
        count = recvfrom(             , rec_buf, BUFSIZE, 0, (struct sockaddr *) &clientinfo, &len);
        if (count < 0)  {
           perror("ERROR in recvfrom");
           return 1;
        }

        printf("Connected from %s:%d\n", inet_ntoa(clientinfo.sin_addr), ntohs(clientinfo.sin_port));
        printf("server received %u/%d bytes: %s\n",                                   );

        // Reverse order of letters in string and write into send_buf




        n = sendto(socketfd, send_buf, strlen(send_buf), 0, (struct sockaddr *) &clientinfo, len);
        if (n < 0) {
            perror("ERROR in sendto");
            return 1;
        }
    }
}
