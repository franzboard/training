// blink-led0-threads
// steuert GPIO via sysfs thread version

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#define LED0_TRIGGER "/sys/class/leds/led0/trigger"
#define LED0_BRIGHTNESS "/sys/class/leds/led0/brightness"

#define TDOT 100000

#define BUFSIZE 1024
#define PORT 8000

const char *code[] = {
    "-----", ".----", "..---", "...--", "....-", ".....",
    "-....", "--...", "---..", "----."
};

int led0_init(void);
int send_morse(char *pmessage);
void getout(int sig);
void error(const char *msg);

int led0_init(void)
{
	FILE *fh;
	// Funktion der LED0 einstellen
	fh = fopen(LED0_TRIGGER, "w");
	if (NULL == fh)
        error("Fehler beim Oeffnen von Trigger");

	fprintf(fh, "none");
	fclose(fh);
    return EXIT_SUCCESS;
}

int send_morse(char* pmessage)
{
    FILE *fh;
    fh = fopen(LED0_BRIGHTNESS, "w");
    if (NULL == fh)
        error("Fehler beim Oeffnen von Brightness");

    int character;
    char symbol;

    while ((character = *pmessage++)) {
        if ((character < '0') || (character > '9'))
            break;
        int i = 0;
        while ((symbol = code[character - '0'][i++])) {
            int tdash =  (symbol == '.') ? 1 : 3;

            fprintf(fh, "1");
      		fflush(fh);
      		usleep(TDOT * tdash);

            fprintf(fh, "0");
      		fflush(fh);
      		usleep(TDOT);
        }
        usleep(TDOT * 3);
    }


    fclose(fh);
    return EXIT_SUCCESS;
}

// error - wrapper for perror
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(void)
{
    if (led0_init() != EXIT_SUCCESS)
        error("Cannot init led0");

    int server_socket, rec_socket;
    unsigned int len 0;
    struct sockaddr_in serverinfo, clientinfo;
    char rec_buf[BUFSIZE];

    unsigned short int port = PORT;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    serverinfo.sin_family = AF_INET;
    serverinfo.sin_addr.s_addr = htonl(INADDR_ANY);
    serverinfo.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr *)&serverinfo, sizeof(serverinfo)) != 0)
        perror("Error ");

    listen(server_socket, 3);

    while(1) {
        len = sizeof(clientinfo);
        printf("Server waiting...\n");
        rec_socket = accept(server_socket, (struct sockaddr *)&clientinfo, &len);
        printf("Connected from %s:%d\n", inet_ntoa(clientinfo.sin_addr), ntohs(clientinfo.sin_port));
        read(rec_socket, rec_buf, sizeof(rec_buf));
        send_morse(rec_buf);
        write(rec_socket, "fertig!\n", sizeof"fertig\n");
        close(rec_socket);
    }
}
