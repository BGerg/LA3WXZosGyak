/************************************************************
 * Project: Szoftverrendszerek, signal kezeles
 * File name: $HOME/cs/alarmra_var.c
 * Abstract: Pelda signal kezelesre.
 *           Az alarm signal handler-e a do_nothing.
 * Usage:    >cc -o alarmra_var alarmra_var.c-lc_s
 *
 *           >alarmra_var &
 *            # es jegyezd meg a pid-jet
 * Athor: Dr. Vadasz Denes
 * Internals: signal (), pause()
 *
 * Bugs, problems: none
 * History:
 *   Created: 1993. oct. 11
 *   Modified:
*************************************************************/

#include <unistd.h>
#include <signal.h>


void do_nothing();


main ()
{


	signal(SIGALRM, do_nothing); /* Jel hat�s�ra megh�v�dik a signal handler ami /*
                                 /* itt a do_nothing �s nem csin�l semmit*/
	printf("  %d varok de meddig?\n");
	pause();
    	printf("  Vegre, itt az alarm \n");/* Jel eset�n k�rja ezt az �zenetet �s a program futtat�s megszakad*/
}
void do_nothing(){ ;}
