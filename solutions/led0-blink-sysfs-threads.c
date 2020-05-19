// led0-blink-sysfs-threads.c
// steuert GPIO via sysfs thread version
// Change blink frequency on comman prompt

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#define LED0_TRIGGER "/sys/class/leds/led0/trigger"
#define LED0_BRIGHTNESS "/sys/class/leds/led0/brightness"

int led0_init(void);
void *led0_blink(void *p);
void getout(int sig);

int tblink; // blink period in ms
int run = 1; // Semaphore
pthread_t pt;

// Signal handler
void getout(int sig)
{
    run = 0;
    pthread_join(pt, NULL);
    printf("Programm beendet!\n");
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


void *led0_blink(void* p)
{
    	FILE *fh;
    	fh = fopen(LED0_BRIGHTNESS, "w");
	if (NULL == fh) {
		fprintf(stderr, "Fehler beim Oeffnen von Brightness \n");
		return NULL;
	}
	while(run)
	{
		fprintf(fh, "1");
		fflush(fh);
		usleep(1000*tblink);

		fprintf(fh, "0");
		fflush(fh);
		usleep(1000*tblink);
	}

	fclose(fh);
    	printf("blink beendet!\n");
    	return NULL;
}


int main(){
    signal(SIGINT,  getout);  // catch CTRL-C
    signal(SIGTERM, getout); // catch kill
    tblink = 500;

    if (led0_init() != EXIT_SUCCESS)
        return EXIT_FAILURE;

    pthread_create(&pt, NULL, led0_blink, NULL);

    while(1) {
        printf("Blink time in ms [ %5d ]> ", tblink);
        scanf("%d", &tblink);
    }
}
