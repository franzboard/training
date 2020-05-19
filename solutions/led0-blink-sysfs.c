// blink-led0-sysfs.c
// steuert GPIO via sysfs
// Aufruf sudo ./blink-led0-sysfs

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define TBLINK 500 // ms
#define LED0_TRIGGER "/sys/class/leds/led0/trigger"
#define LED0_BRIGHTNESS "/sys/class/leds/led0/brightness"

int led0_init(void);
int led0_blink(int ms);
int led0_cleanup(void);
void getout(int sig);

// Signal handler
void getout(int sig)
{
    led0_cleanup();
    fprintf(stderr, "Programm beendet!\n");
    exit(EXIT_SUCCESS);
}


int led0_init(void)
{
	FILE *fh;
	// Funktion der LED0 einstellen
	fh = fopen(LED0_TRIGGER, "w");
	if (NULL == fh) {
		fprintf(stderr, "Fehler beim Oeffnen von Trigger \n");
		return EXIT_FAILURE;
	}
	fprintf(fh, "none");
	fclose(fh);
    return EXIT_SUCCESS;
}


int led0_cleanup(void)
{
	FILE *fh;
    fh = fopen(LED0_BRIGHTNESS, "w");
	if (NULL == fh) {
		fprintf(stderr, "Fehler beim Oeffnen von Brightness \n");
		return EXIT_FAILURE;
	}
	fprintf(fh, "0");
	fclose(fh);
    return EXIT_SUCCESS;
}

int led0_blink(int ms)
{
	FILE *fh;
    fh = fopen(LED0_BRIGHTNESS, "w");
	if (NULL == fh) {
		fprintf(stderr, "Fehler beim Oeffnen von Brightness \n");
		return EXIT_FAILURE;
	}
	while(1)
	{
		fprintf(fh, "1");
		fflush(fh);
		usleep(ms*1000);

		fprintf(fh, "0");
		fflush(fh);
		usleep(ms*1000);
	}

    return EXIT_SUCCESS;
}

int main(){
    signal(SIGINT, getout);  // catch CTRL-C
    signal(SIGTERM, getout); // catch kill
    if (led0_init() == EXIT_SUCCESS)
        led0_blink(TBLINK);
}
