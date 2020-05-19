/* Einfacher Portscanner */
/* Aufruf: ./portscanner <IP-Adresse> <Portnummer1> <Portnummer 2>... */

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

// Scanner-Funktion
// Parameter: IP-Adresse, Portnummer
// Rueckgabe: 0 -> erfolgreich, 1 -> nicht erfolgreich
int scan(char* ip, char* port)
{
    int socket_fd;
    int len;
    struct sockaddr_in addressinfo;
    int result;

    // Initialisierung der Variablen fuers Netzwerk:
    socket_fd = socket(AF_INET, SOCK_STREAM, 0); // IPv4, TCP
    addressinfo.sin_family = AF_INET;
    // Umwandlung z.B. 127.0.0.1 ins interne Format
    inet_pton(AF_INET, ip, &addressinfo.sin_addr.s_addr);
    // atoi: Portnummer (String) -> int
    // htons: Umwandlung int ins interne Format
    addressinfo.sin_port = htons(atoi(port));
    len = sizeof(addressinfo);

    // Verbindung des Sockets mit dem Host(ip, port)
    result = connect(socket_fd, (struct sockaddr *)&addressinfo, len);

    // Socket schliessen
    close(socket_fd);
    return result;
}

int main(int argc, char *argv[])
{
    if (argc < 3) { // Fehlerbehandlung bei falscher Kommandozeile
        printf("Usage: %s <ip> <port> <port> ...\n", argv[0]);
        return 1;
    }

    int n = 2;
    while (argv[n]) {
        printf("Scanne %s %s => ", argv[1], argv[n]); // IP PORT
        if (scan(argv[1], argv[n]) == 0)
            printf("offen\n");
        else
            printf("geschlossen\n");
        n++;
    // eigentlicher Portscanner
    }

   return 0;
}
