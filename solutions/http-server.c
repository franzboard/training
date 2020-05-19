/* Connect to a webserver on port 80 and print answer on console */
/* Call: ./connect-http 127.0.0.1 */
/* My first HTTP-Server */
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
    server_socket = socket(AF_INET, SOCK_STREAM, 0); // ipv4, TCP
    serverinfo.sin_family = AF_INET;
    serverinfo.sin_addr.s_addr = htonl(INADDR_ANY); // alle konfigurierten Adressen
    serverinfo.sin_port = htons(PORT);
    
    // Socket an Adresse binden 
    if (bind(server_socket, (struct sockaddr *)&serverinfo, sizeof(serverinfo)) != 0) {
		perror("Error ");
		return 1;
    }
    
    // Server lauscht:
    listen(server_socket, 3);
    
    while (1) {
		printf("Server waiting...\n");
		// Verbindung vom Client kommt herein:
		rec_socket = accept(server_socket, (struct sockaddr *)&clientinfo, &len);
		printf("Connect from: %s Port: %d\n", inet_ntoa(clientinfo.sin_addr), ntohs(clientinfo.sin_port));
		
		// Lese Begruessung vom Client: GET / HTTP/1.1.... ohne weitere Ueberpruefung
		read(rec_socket, rec_buf, sizeof(rec_buf));
		
		// Sende Website an den Client:
		write(rec_socket, send_buf, sizeof(send_buf));
		
		// Schliesse Clientsocket:
		close(rec_socket);
		
	}
    
    return(0);
}
