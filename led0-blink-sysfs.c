// blink-led0-sysfs.c
// steuert GPIO via sysfs
// Aufruf sudo ./blink-led0-sysfs

// See https://elinux.org/RPi_GPIO_Code_Samples#sysfs

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define TBLINK 500 // ms
#define LED0_TRIGGER "/sys/class/leds/led0/trigger" // led0 for blink instead of status
#define LED0_BRIGHTNESS "/sys/class/leds/led0/brightness" // on / off


int led0_init(void);
int led0_blink(int ms);
int led0_cleanup(void);
void getout(int sig);

// Signal handler for interruption of program from keyboard
void getout(int sig)
{
                                    // LED off
    fprintf(stderr, "Programm beendet!\n");
    exit(EXIT_SUCCESS);
}


int led0_init(void)
{
	FILE *fh;
	// Funktion der LED0 einstellen
	// open LED0_TRIGGER




    
	fprintf(fh, "none");
	fclose(fh);
    return EXIT_SUCCESS;
}


int led0_cleanup(void)
{
	FILE *fh;
    fh =           (LED0_BRIGHTNESS,          ); // open file with write access
	if (      ==        ) {
		fprintf(stderr, "Fehler beim Oeffnen von Brightness \n");
		return EXIT_FAILURE;
	}
	fprintf(        ,     ); // Off
	fclose(fh);
    return EXIT_SUCCESS;
}

int led0_blink(int ms)
{
	FILE *fh;
    fh =         (LED0_BRIGHTNESS, );// open file with write access
	if (        ==             ) {
		fprintf(stderr, "Fehler beim Oeffnen von Brightness \n");
		return EXIT_FAILURE;
	}
	while(1)
	{
		fprintf(          ); // On
		fflush(   );
		usleep(          ); // TBLINK ms

		fprintf(      );   // Off
		fflush(   );
		usleep(      );    // TBLINK ms
	}

    return EXIT_SUCCESS;
}

int main(){
                             // catch CTRL-C
                             // catch kill
    if (led0_init() == EXIT_SUCCESS)
        led0_blink(TBLINK);
}
