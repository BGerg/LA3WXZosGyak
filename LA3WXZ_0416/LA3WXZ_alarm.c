/************************************************************
 * Project: Szoftverrendszerek, signal kezeles
 * File name: $HOME/cs/alarm.c
 * Abstract: Pelda signal kezelesre.
 *           ctrl/break signal hatasara a do_int handler mukodik
 *           eloszor, majd ignoralodik ez a signal.
 *           A ciklusban masodpercenkent alarm generalodik,
 *           az alarm signal handler-e a do_nothing.
 *           A pause felfuggeszti a process-t, amig kap egy signalt.
 * Usage:    cc -o alarm alarm.c -lc_s
 *
 *           alarm
 * Athor: Dr. Vadasz Denes
 * Internals: signal (), alarm(), pause()
 *
 * Bugs, problems: none
 * History:
 *   Created: 1993. oct. 7
 *   Modified:
*************************************************************/

#include <unistd.h>
#include <signal.h>
#define SECOND 1

void do_nothing();
void do_int();

main ()
{
	int i;
	unsigned sec=1;

	signal(SIGINT, do_int); /*Jel esetén pl Keyboadinterrupt-nál a do_int függvény hívódik fel */

for (i=1;i<8;i++) {
	alarm(sec); /* megadott idõközönként (1mp) SIGALARM jelet ad ki*/
	signal(SIGALRM, do_nothing); /* A elõ sor hatására meghívódik a signal handler ami /*
                                 /* itt a do_nothing és nem csinál semmit*/
	printf("  %d varok de meddig?\n",i);
	pause(); /* Felfüggeszti a hívó folyamatot a legelsõ jel érkezéséig*/
    }
}
void do_nothing(){ ;}

void do_int() {
	printf(" int jott ");
	signal(SIGINT,SIG_IGN); /* A SIG_IGN felhivásával a kapott jelet figyelmen kívül hagyja, */
                            /* így Keyboardinterruptal sem szakad meg a futás */
}
