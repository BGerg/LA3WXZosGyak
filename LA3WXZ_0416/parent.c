#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char *argv[])
{

	int status, pid, ppid, gpid;

	ppid = getpid();        /* Szulő pidje */



	if ((pid = fork()) == 0)
	{ 	/* gyermek processz */
        status = execl("/home/gergely/cs/child", "/home/gergely/cs/child",NULL);
		if (status == -1)
		{	perror("parent execl failed");
		exit (0);
		}
	}

	/* szulo process */

	printf("\n %d.sz. szulo var a %d.sz. gyermekre.\n ", ppid,pid);
	if (pid != wait(&status)) perror(" Szulo - varakozas hiba ");
	return 0;
}