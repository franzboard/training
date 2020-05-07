/* My first HTTP-Server */
/* Listens on Port 5000 */

#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFLEN 1000
#define PORT 5000

int main(int argc, char *argv[])
{
    int server_socket, rec_socket;
    unsigned int len;
    struct sockaddr_in serverinfo, clientinfo;
    // Antwort des Servers:
    char send_buf[] = "HTTP/1.1 200 OK\r\n\r\n<html><body><h1>Hi BULME</h1></body></html>";
    char rec_buf[BUFLEN];

	// Konfiguration Server:
    server_socket = socket(            ,         , 0); // ipv4, TCP
    serverinfo.sin_family =                ; // ipv4
    serverinfo.sin_addr.s_addr = htonl(INADDR_ANY); // alle konfigurierten Adressen (localhost und externe)
    serverinfo.sin_port = htons(      );
    
    // Socket an Adresse binden 
    if (                                                    != 0) {
		perror("Error ");
		return 1;
    }
    
    // Server lauscht:
    
    while (1) {
		printf("Server waiting...\n");
		// Verbindung vom Client kommt herein:
		rec_socket =               (server_socket, (struct sockaddr *)&clientinfo, &len);
		printf("Connect from: %s Port: %d\n", inet_ntoa(clientinfo.sin_        ), ntohs(clientinfo.sin_  ));
		
		// Lese Begruessung vom Client: GET / HTTP/1.1.... ohne weitere Ueberpruefung
		read(                                    );
		
		// Sende Website an den Client:
		write(                                   );
		
		// Schliesse Clientsocket:
		close(                  );
		
	}
    
    return(0);
}
