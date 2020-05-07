/* Einfacher Portscanner */
/* Aufruf: ./portscanner <IP-Adresse> <Portnummer> ... */
/* beliebig viele Portnummern, aber zumindest eine */

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

// Scanner-Funktion
// Parameter: IP-Adresse, Portnummer
// Rueckgabe: 0 -> erfolgreich, 1 -> nicht erfolgreich
int scan(          ,             )
{
    int socket_fd;
    int len;
    struct sockaddr_in addressinfo;
    int result;

    // Initialisierung der Variablen fuers Netzwerk:
    socket_fd = socket(           ,           , 0); // IPv4, TCP
    addressinfo.sin_family = AF_INET;
    // Umwandlung z.B. 127.0.0.1 ins interne Format:
    inet_pton(AF_INET, ip, &addressinfo.sin_addr.s_addr);
    // atoi: Portnummer (String) -> int
    // htons: Umwandlung int ins interne Format
    addressinfo.sin_port = htons(atoi(      ));
    len = sizeof(addressinfo);

    // Verbindung des Sockets mit dem Host(ip, port)
    result =                 (socket_fd, (struct sockaddr *)&addressinfo, len);

    // Socket schliessen:


    return result;
}

int main(int argc, char *argv[])
{
    if (argc <  ) { // Fehlerbehandlung bei falscher Kommandozeile
        printf("Usage: %s <ip> <port> ...\n", argv[0]);
        return 1;
    }

    int n = ;
    while (argv[n]) {
        printf("Scanne %s %s => ", argv[      ], argv[           ]); // IP PORT
        if (scan(argv[  ], argv[   ]) ==  )
            printf("offen\n");
        else
            printf("geschlossen\n");
        n++;
    // eigentlicher Portscanner
    }

   return 0;
}
