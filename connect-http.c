/* Connect to a webserver  and print answer on console */
/* Call: ./connect-http 127.0.0.1 */

#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFLEN 20000
// Port number for plain http:
#define PORT 

int main(int argc, char *argv[])
{
    int socket_fd;
    int len;
    struct sockaddr_in adressinfo;
    int result;
    // Web server waits for this string before answering
    char cmd[] = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n";
    char answer[BUFLEN];
    int n;

    // HTTP: TCP / IPv4
    socket_fd = socket(                      ,                 , 0);
    adressinfo.sin_family =                    ;
    inet_pton(AF_INET, argv[        ],&adressinfo.sin_addr.s_addr);
    adressinfo.sin_port = htons(       );
    len = sizeof(adressinfo);
    result = connect(socket_fd, (struct sockaddr *)&adressinfo, len);
    if (result !=     ) {
        printf("connect failed!\n");
    }
    else {
        write(           ,                , sizeof(        ));        
        printf("----- received: -----\n");
        n = read(           , answer, sizeof(          )     );        
        answer[n] = '\0';
        printf("%s\n", answer);
    }

    // Close socket:
   
    
    return(0);
}
