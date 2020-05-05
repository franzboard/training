// led0-blink-sysfs-threads.c
// steuert GPIO via sysfs thread version
// Change blink frequency on comman prompt

// Aufruf sudo ./blink-led0-sysfs-threads

// See https://elinux.org/RPi_GPIO_Code_Samples#sysfs

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#define LED0_TRIGGER "/sys/class/leds/led0/trigger"   // trigger file
#define LED0_BRIGHTNESS "/sys/class/leds/led0/brightness"  // brightness file

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
                          (pt, NULL);   // join threads
    printf("Programm beendet!\n");
    exit(EXIT_SUCCESS);

}

int led0_init(void)
{
	FILE *fh;
	// Funktion der LED0 einstellen
    // open LED0_TRIGGER for writing




	fprintf(fh, "none");
	fclose(fh);
    return EXIT_SUCCESS;
}


void *led0_blink(void* p)
{
    	FILE *fh;
    	fh =                                       // open brightness file / write
	    if (NULL == fh) {
		fprintf(stderr, "Fehler beim Oeffnen von Brightness \n");
		return NULL;
	}
	while(run)
	{
		fprintf(           ); // on
		fflush(      );
		usleep(1000*tblink);

		fprintf(     );   // off
		fflush(      );
		usleep(1000*tblink);
	}

	fclose(       );
    	printf("blink beendet!\n");
    	return NULL;
}


int main(){
    signal(                             );  // catch CTRL-C
    signal(                             ); // catch kill
    tblink = 500;

    if (led0_init() != EXIT_SUCCESS)
        return EXIT_FAILURE;

    pthread_create(                                  );

    while(1) {
        printf("Blink time in ms [ %5d ]> ", tblink);
        scanf(            ,                 );
    }
}
