// led0-pwm nr@bulme.at 2019
// steuert GPIO via sysfs thread version
// kompilieren mit
// gcc led0-pwm.c -o led0-pwm -lpthread -lncurses -Wall

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
    pthread_join(pt, NULL);
    endwin();
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
		usleep(TBLINK*duty/100);

		fprintf(fh, "0");
		fflush(fh);
		usleep(TBLINK - TBLINK*duty/100);
	}

	fclose(fh);
    	printf("blink beendet!\n");
    	return NULL;
}


int main(){
    int dimvals[] = {0, 2, 4, 6, 10, 16, 25, 40, 63, 100}; // physiolog. eye sensitivity
    int pos = 5; // mid range
    duty = dimvals[pos];

    signal(SIGINT,  getout);  // catch CTRL-C
    signal(SIGTERM, getout); // catch kill

    if (led0_init() != EXIT_SUCCESS)
        return EXIT_FAILURE;

    pthread_create(&pt, NULL, led0_blink, NULL);
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
            pos = (pos == 9) ? 9 : pos+1;
        else if (key == KEY_DOWN)
            pos = (pos == 0) ? 0 : pos-1;
        else
            continue;

    }
    endwin ();
}
