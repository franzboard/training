// led0-pwm nr@bulme.at 2019
// control GPIO led0 via sysfs,  thread version
// compile: 
// gcc led0-pwm.c -o led0-pwm -lpthread -lncurses -Wall
// execute: sudo ./led0.pwm (sys file system needs this)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <curses.h>

#define LED0_TRIGGER "/sys/class/leds/led0/trigger"
#define LED0_BRIGHTNESS "/sys/class/leds/led0/brightness"

// blink period in us
#define TBLINK 20000L

int led0_init(void);
void *led0_blink(void *p);
void getout(int sig);

int duty; // duty cycle
int run = 1; // Semaphore
pthread_t pt;

// Signal handler
void getout(int sig)
{
    run = 0;
    // Join threads:
   

    endwin();
    printf("Programm beendet!\n");
    exit(EXIT_SUCCESS);
}

int led0_init(void)
{
	FILE *fh;
	// Funktion der LED0 einstellen
	fh = fopen(          ,                );
	if (NULL == fh) {
		fprintf(stderr, "Fehler beim Oeffnen von Trigger \n");
		return EXIT_FAILURE;
	}
	fprintf(          , "none");
    // close file:
   

    return EXIT_SUCCESS;
}


void *led0_blink(void* p)
{
    FILE *fh;
    fh = fopen(LED0_BRIGHTNESS,             );
	if (    ==           ) {
		fprintf(stderr, "Fehler beim Oeffnen von Brightness \n");
		return NULL;
	}
	while(run)
	{
        // calculate on and off due to duty cycle
		fprintf(fh, "1");
        // flush  memory to file:

        // sleep for .... useconds:

		fprintf(fh, "0");
        // flush  memory to file:

        // sleep for .... useconds:

	}

	fclose(fh);
   	printf("blink beendet!\n");
    return NULL;
}


int main(){
    // Lookup table for brightness due to human eye sensitivity
    // Duty cycle 0...100 %
    int dimvals[] = {0, 2, 4, 6, 10, 16, 25, 40, 63, 100}; 
    int pos = 5; // mid range

    duty = dimvals[pos];

    signal(SIGINT,      );  // catch CTRL-C
    signal(SIGTERM,  ); // catch kill

    if (led0_init() != EXIT_SUCCESS)
        return EXIT_FAILURE;

    // create blink thread
    pthread_create(   ,   ,  , );
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    int key;
    while(run) {
        duty = dimvals[pos];
        move(0,0);
        printw("Duty cycle %5d %%\n", duty);
        key = getch();
        if (key == KEY_UP)
            // increment position by 1, maximum 9:
            
        else if (key == KEY_DOWN)
           // decrement postition by 1, minimum 0:
           
        else
            continue;

    }
    endwin ();
}
