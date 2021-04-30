/************************************************************
 * Project: Szoftverrendszerek, signal kezeles
 * File name: $HOME/cs/alarm_ado.c
 * Abstract: Pelda signal kezelesre.

 * Usage:    >cc -o alarm_ado alarm_ado.c -lc_s
 *	     ># pid = az alarmra_var pid-je
 *           >alarm_ado pid
 * Athor: Dr. Vadasz Denes
 * Internals: atoi(), perror(), exit(), kill()
 *
 * Bugs, problems: none
 * History:
 *   Created: 1993. oct. 11
 *   Modified:
*************************************************************/


#include <sys/types.h>
#include <signal.h>

main(int argc, char **argv)
{
	int pid;

	if (argc < 1)
	{
		perror(" Nincs kinek"); /*Kiír egy leíró hibaüzenetet a stderr-re */
		exit(1);
	}

	pid = atoi(argv[1]);

	kill(pid, SIGALRM); /* Küld egy SIGALRM jelet a konkrét ID-vel ellátott processznek és*/
                        /* ennek hatására a program futtatás megszakad*/
}
